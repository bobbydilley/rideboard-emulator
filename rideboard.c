#include <fcntl.h>
#include <linux/serial.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/**
 * SEGA Ride Board Emulator,
 * for use with the following Lindbergh games:
 * 
 * Let's Go Jungle Special!
 * The House Of The Dead 4 Special
 * 
 * Author: bobbydilley
 * Thanks to: doozer, ags, harm
 */

/* Buffer packet sizes */
#define OUTPUT_PACKET_SIZE 22
#define INPUT_PACKET_SIZE 7

/* How long to wait for data before timing out */
#define READ_TIMEOUT 500

/* Enums to represent the different states of the MotionSelectSwitch */
#define MOTION_OFF 0
#define MOTION_MILD 1
#define MOTION_NORMAL 2

/* The default file path of the serial interface */
#define DEFAULT_SERIAL_INTERFACE_PATH "/dev/ttyUSB0"

/* Enable Debug Mode */
#define DEBUG_MODE 0

/* Variable to signify the state of the emulator */
static volatile int running = 0;

/* Enum to define the colour of the billboard lamp */
typedef enum
{
	LAMP_OFF = 0,
	LAMP_GREEN,
	LAMP_BLUE,
	LAMP_RED
} LampState;

/* Struct to hold the internal state of the ride */
typedef struct
{
	/* COMMANDS */
	int Command;
	int CommandReply;
	int SeatCommand;
	int SeatCommandReply;
	/* OUTPUTS */
	int PlayerOneBlowFront;
	int PlayerOneBlowBack;
	int PlayerTwoBlowFront;
	int PlayerTwoBlowBack;
	int PlayerOneGunReaction;
	int PlayerTwoGunReaction;
	int ResetLamp;
	int ErrorLamp;
	int SafetyLamp;
	int GameStopLamp;
	int FloorLamp;
	int SpotLamp;
	LampState BillboardLamp;
	/* INPUTS */
	int InitButton;
	int ResetButton;
	int MotionSelectSwitch; // 0 Motion Off, 1 Motion Gentle, 2 Motion Normal
	int TowerGameStopButton;
	int RideGameStopButton;
	int RearFootSensor;
	int LeftFootSensor;
	int FrontFootSensor;
	int RightFootSensor;
	int RightDoorSensor;
	int LeftDoorSensor;
	int ArmrestSensor;
	int PlayerOneSeatbeltSensor;
	int PlayerTwoSeatbeltSensor;
	int RearPositionSensor;
	int FrontPositionSensor;
	int CCWLimitSensor;
	int CWLimitSensor;
	int MotorPower;
} RideState;

/**
 * Set the attributes of the serial port so raw data is sent
 *
 * Change the serial port settings so that it is treated as raw and
 * not any sort of linux terminal emulation.
 *
 * @param fd The file descriptor of the serial port to read from
 * @param myBaud The baud rate to set the serial port to
 * @returns 1 on success and 0 on failure
 */
int setSerialAttributes(int fd, int myBaud)
{
	struct termios options;
	int status;
	tcgetattr(fd, &options);

	cfmakeraw(&options);
	cfsetispeed(&options, myBaud);
	cfsetospeed(&options, myBaud);

	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	options.c_oflag &= ~OPOST;

	options.c_cc[VMIN] = 0;
	options.c_cc[VTIME] = 0; // One seconds (10 deciseconds)

	tcsetattr(fd, TCSANOW, &options);

	ioctl(fd, TIOCMGET, &status);

	status |= TIOCM_DTR;
	status |= TIOCM_RTS;

	ioctl(fd, TIOCMSET, &status);

	usleep(100 * 1000); // 10mS

	struct serial_struct serial_settings;

	ioctl(fd, TIOCGSERIAL, &serial_settings);

	serial_settings.flags |= ASYNC_LOW_LATENCY;
	ioctl(fd, TIOCSSERIAL, &serial_settings);

	return 0;
}

/**
 * Handle the INTERRUPT signal
 *
 * Closes the program down gracefully if the INTTERUPT
 * signal is activated.
 */
void signalIntHandler()
{
	running = 0;
}

/**
 * Read a packet of data from the Lindbergh
 *
 * Read a raw packet of data from the Lindbergh
 *
 * @param serialPort The file descriptor of the serial port to read from
 * @param packet The buffer to store the raw packet in
 * @returns 1 on success and 0 on failure
 */
int readPacket(int serialPort, char *packet)
{
	struct timeval tv;
	fd_set fd_serial;

	FD_ZERO(&fd_serial);
	FD_SET(serialPort, &fd_serial);

	tv.tv_sec = 0;
	tv.tv_usec = READ_TIMEOUT * 1000;

	if (select(serialPort + 1, &fd_serial, NULL, NULL, &tv) < 1)
		return 0;

	if (!FD_ISSET(serialPort, &fd_serial))
		return 0;

	return read(serialPort, packet, INPUT_PACKET_SIZE);
}

/**
 * Write a packet of data to the Lindbergh
 *
 * Take a raw packet of data and write it to the Lindbergh
 *
 * @param serialPort The file descriptor of the serial port to write to
 * @param packet The raw packet data to write
 * @returns 1 on success and 0 on failure
 */
int writePacket(int serialPort, char *packet)
{
	return write(serialPort, packet, OUTPUT_PACKET_SIZE);
}

/**
 * Process the input packet from the lindbergh into usable data
 *
 * Take the information encoded in the input packet, and set the
 * state of the emulators virtual ride accordingly.
 *
 * @param packet The input packet to read from
 * @param state The ride state to write to
 * @returns 1 on success and 0 on failure
 */
int processInputPacket(char *packet, RideState *state)
{
	/* Check the checksum is correct */
	char checksum = 0;
	for (int i = 1; i < INPUT_PACKET_SIZE - 1; i++)
		checksum ^= packet[i];

	if (checksum != packet[INPUT_PACKET_SIZE - 1])
	{
		printf("Error: Input checksum failed\n");
		return 0;
	}

	/* Command Packet */
	state->Command = packet[1];

	/* Seat Command Packet */
	state->SeatCommand = packet[2];

	/* Gun Reaction / Blowers */
	state->PlayerOneBlowFront = (packet[3] & 0b00000001) > 0;
	state->PlayerTwoBlowFront = (packet[3] & 0b00000010) > 0;
	state->PlayerOneBlowBack = (packet[3] & 0b00000100) > 0;
	state->PlayerTwoBlowBack = (packet[3] & 0b00001000) > 0;
	state->PlayerOneGunReaction = (packet[3] & 0b00010000) > 0;
	state->PlayerTwoGunReaction = (packet[3] & 0b00100000) > 0;

	/* Billboard Lamp */
	if (packet[4] & 0b10000000)
	{
		if (packet[4] & 0b00000001)
			state->BillboardLamp = LAMP_GREEN;
		else if (packet[4] & 0b00000010)
			state->BillboardLamp = LAMP_BLUE;
		else
			state->BillboardLamp = LAMP_RED;
	}
	else
	{
		state->BillboardLamp = LAMP_OFF;
	}

	/* Other Lamp outputs */
	state->ResetLamp = (packet[5] & 0b00000001) > 0;
	state->ErrorLamp = (packet[5] & 0b00000010) > 0;
	state->SafetyLamp = (packet[5] & 0b00000100) > 0;
	state->GameStopLamp = (packet[5] & 0b00001000) > 0;
	state->FloorLamp = (packet[5] & 0b00010000) > 0;
	state->SpotLamp = (packet[5] & 0b00100000) > 0;

	return 1;
}

/**
 * Get the output packet ready for sending to the Lindbergh
 *
 * Create the correct output packet from the ride state, taking
 * into account button positions and chair reports.
 *
 * @param packet The output packet to fill up
 * @param state The ride state to read from
 * @returns 1 on success and 0 on failure
 */
int processOutputPacket(char *packet, RideState *state)
{
	/* Put the sync packet in byte 0 */
	packet[0] = 0xC0;

	/* Unknown Packet */
	packet[1] = 0x00;

	/* Unknown Packet */
	packet[2] = state->CommandReply; // Byte 0x30 (0xFF UPDATE MODE) (0x00 SERIAL CHECKING) (0x1A RIDE STOP)

	/* Ride turn Test Enable */
	packet[3] = state->SeatCommandReply; // Byte 0x31

	/* Packet 4 contains some buttons */
	packet[4] = 0x00;
	if (state->TowerGameStopButton)
		packet[4] = packet[4] | 0b00000001;

	if (state->MotionSelectSwitch == MOTION_NORMAL)
		packet[4] = packet[4] | 0b00000010;

	if (state->ResetButton)
		packet[4] = packet[4] | 0b00000100;

	if (state->RideGameStopButton)
		packet[4] = packet[4] | 0b00001000;

	if (state->InitButton)
		packet[4] = packet[4] | 0b00010000;

	if (state->RearFootSensor)
		packet[4] = packet[4] | 0b00100000;

	if (state->LeftFootSensor)
		packet[4] = packet[4] | 0b01000000;

	/* Packet 5 contains some more buttons */
	packet[5] = 0x00;
	if (state->RightFootSensor)
		packet[5] = packet[5] | 0b00000001;

	if (state->FrontFootSensor)
		packet[5] = packet[5] | 0b00000010;

	if (state->RightDoorSensor)
		packet[5] = packet[5] | 0b00000100;

	if (state->ArmrestSensor)
		packet[5] = packet[5] | 0b00001000;

	if (state->PlayerOneSeatbeltSensor)
		packet[5] = packet[5] | 0b00010000;

	if (state->PlayerTwoSeatbeltSensor)
		packet[5] = packet[5] | 0b00100000;

	if (state->FrontPositionSensor)
		packet[5] = packet[5] | 0b01000000;

	if (state->LeftDoorSensor)
		packet[5] = packet[5] | 0b10000000;

	/* Packet 6 contains some more buttons */
	packet[6] = 0x00;
	if (state->RearPositionSensor)
		packet[6] = packet[6] | 0b00000001;

	if (state->CWLimitSensor)
		packet[6] = packet[6] | 0b00000100;

	if (state->CCWLimitSensor)
		packet[6] = packet[6] | 0b00001000;

	if (state->MotorPower)
		packet[6] = packet[6] | 0b00010000;

	if (state->MotionSelectSwitch == MOTION_MILD)
		packet[6] = packet[6] | 0b01000000;

	if (state->MotionSelectSwitch == MOTION_OFF)
		packet[6] = packet[6] | 0b10000000;

	/* Unknown Packet */
	packet[7] = 0x00; // Unknown

	/* Used for the USB Update */
	packet[8] = 0x00;  // 2ND BOOT (0 = Ignore, 1 = Update Success, 2 = Update Failed, 3 = Unknown)
	packet[9] = 0x00;  // USB LOADER (0 = Ignore, 1 = Update Success, 2 = Update Failed, 3 = Unknown)
	packet[10] = 0x00; // Application (0 = Ignore, 1 = Update Success, 2 = Update Failed, 3 = Unknown)

	packet[11] = 0x00; // 2ND BOOT SUM
	packet[12] = 0x00; // USB LOADER SUM
	packet[13] = 0x00; // Application SUM

	packet[14] = 0x00; // 2ND BOOT Major
	packet[15] = 0x00; // 2ND BOOT Minor
	packet[16] = 0x00; // USB LOADER Major
	packet[17] = 0x00; // USB LOADER Minor
	packet[18] = 0x00; // Application Major
	packet[19] = 0x00; // Application Minor

	/* Unknown Packet */
	packet[20] = 0x00; // Unknown

	/* Calculate the checksum and place in the last space */
	char checksum = 0;
	for (int i = 1; i < OUTPUT_PACKET_SIZE - 1; i++)
		checksum ^= packet[i];

	packet[OUTPUT_PACKET_SIZE - 1] = checksum;

	return 1;
}

/**
 * Process any physical emulation that should be done
 *
 * Process the input and output states and decide
 * what should be done on each cycle
 *
 * @param state The ride state to read from and write to
 * @returns 1 on success and 0 on failure
 */
int processEmulation(RideState *state)
{
	// Respond with the correct response command
	switch (state->Command)
	{
	case 0x01: // Boot
		state->CommandReply = 0x01; // 0xFF to show update screen
		break;
	case 0x02: // Init check
		state->CommandReply = 0x03;
		break;
	case 0x03: // Reset to defaults confirmation
		state->RearFootSensor = 0;
		state->LeftFootSensor = 0;
		state->FrontFootSensor = 0;
		state->RightFootSensor = 0;
		state->ArmrestSensor = 0;
		state->PlayerOneSeatbeltSensor = 0;
		state->PlayerTwoSeatbeltSensor = 0;
		break;
	case 0x04: // Reset Success
		state->CommandReply = 0x05;
		break;
	case 0x19: // Work out what ADF means?
		state->CommandReply = 0x06;
	case 0x05: // Coin play, not coined up
	case 0x06: // Ticket play, waiting for init by attendant (Not sure if this is correct)
		state->CommandReply = 0x08;
		break;
	case 0x08: // Kate Green talking about AMS
		state->CommandReply = 0x0A;
		break;
	case 0x0A: // Intro Video Playing (toggle seatbelts)
		state->CommandReply = 0x0A;
		state->PlayerOneSeatbeltSensor = !state->PlayerOneSeatbeltSensor;
		state->PlayerTwoSeatbeltSensor = !state->PlayerTwoSeatbeltSensor;
		break;
	case 0x0D: // Passed attract mode
		state->CommandReply = 0x0D;
		state->PlayerOneSeatbeltSensor = 0;
		state->PlayerTwoSeatbeltSensor = 0;
		break;
	case 0x11: // After game over get out! (Speed up?)
	case 0x13: // Test mode
	case 0x1A: // Emergency Stop
	case 0xFF: // USB Update
	default:
		state->CommandReply = state->Command;
	}

	// Respond with the correct seat response
	switch (state->SeatCommand)
	{
	case 0x01:
		state->SeatCommandReply = 1;
		break;
	case 0x11:
		state->SeatCommandReply = 1;
		break;
	case 0x21:
		state->SeatCommandReply = 3;
		break;
	case 0x31:
		state->SeatCommandReply = 5;
		break;
	case 0x41:
		state->SeatCommandReply = 7;
		break;
	case 0x51:
		state->SeatCommandReply = 9;
		break;
	case 0x61:
		state->SeatCommandReply = 11;
		break;
	default:
		break;
	}

	return 1;
}

void printStatus(RideState *state)
{
	int end = 0;
	if (state->PlayerOneGunReaction && ++end)
		printf("PLAYER_ONE_GUN_REACTION ");
	if (state->PlayerTwoGunReaction && ++end)
		printf("PLAYER_TWO_GUN_REACTION ");
	if (state->PlayerOneBlowBack && ++end)
		printf("PLAYER_ONE_BLOW_BACK ");
	if (state->PlayerTwoBlowBack && ++end)
		printf("PLAYER_TWO_BLOW_BACK ");
	if (state->PlayerOneBlowFront && ++end)
		printf("PLAYER_ONE_BLOW_FRONT ");
	if (state->PlayerTwoBlowFront && ++end)
		printf("PLAYER_TWO_BLOW_FRONT ");
	if (state->GameStopLamp && ++end)
		printf("GAME_STOP_LAMP ");
	if (state->ResetLamp && ++end)
		printf("RESET_LAMP ");
	if (state->ErrorLamp && ++end)
		printf("ERROR_LAMP ");
	if (state->SafetyLamp && ++end)
		printf("SAFETY_LAMP ");
	if (state->FloorLamp && ++end)
		printf("FLOOR_LAMP ");
	if (state->SpotLamp && ++end)
		printf("SPOT_LAMP ");
	if (state->BillboardLamp != LAMP_OFF && ++end)
	{
		switch (state->BillboardLamp)
		{
		case LAMP_RED:
			printf("BILLBOARD_LAMP_RED ");
			break;
		case LAMP_GREEN:
			printf("BILLBOARD_LAMP_GREEN ");
			break;
		case LAMP_BLUE:
			printf("BILLBOARD_LAMP_BLUE ");
			break;
		default:
			break;
		}
	}
	if (end)
		printf("\n");
}

/**
 * Pretend to be the ride from SEGA's Special games.
 *
 * Communicate with a SEGA Lindbergh via serial to
 * emulate the inner working of a Special ride.
 */
int main(int argc, char **argv)
{
	signal(SIGINT, signalIntHandler);

	int fd = -1;
	char *serialInterfacePath = DEFAULT_SERIAL_INTERFACE_PATH;

	if (argc > 1)
	{
		if (strcmp(argv[1], "--help") == 0 | argc > 2)
		{
			printf("usage: %s [serial_path]\n", argv[0]);
			return EXIT_SUCCESS;
		}

		serialInterfacePath = argv[1];
	}

	printf("SEGA Lindbergh Rideboard Emulator\n");

	printf("Info: Opening Serial Port %s\n", serialInterfacePath);
	if ((fd = open(serialInterfacePath, O_RDWR | O_NOCTTY)) < 0)
	{
		printf("Critical: Failed to open serial port, exiting.\n");
		return EXIT_FAILURE;
	}

	/* Setup the serial connection */
	setSerialAttributes(fd, B115200);

	char outputPacket[OUTPUT_PACKET_SIZE];
	char inputPacket[INPUT_PACKET_SIZE];

	RideState rideState = {0};

	running = 1;
	while (running)
	{
		/* Step 1, read a packet in from the Lindbergh */
		int bytesRead = 0;
		while (running && (bytesRead != INPUT_PACKET_SIZE))
		{
			bytesRead += readPacket(fd, inputPacket + bytesRead);
		}

		if (DEBUG_MODE)
		{
			for (int i = 0; i < bytesRead; i++)
			{
				printf("0x%02hhX ", inputPacket[i]);
			}
			printf("\n");
		}

		/* Step 2, process the input packet */
		if (!processInputPacket(inputPacket, &rideState))
		{
			printf("Critical: Failed to process the input packet\n");
			running = -1;
			break;
		}

		printStatus(&rideState);

		/* Step 3, process any emulation logic such as setting buttons */
		if (!processEmulation(&rideState))
		{
			printf("Critical: Failed to process the emulation\n");
			running = -1;
			break;
		}

		/* Step 4, create an output packet for sending back to the Lindbergh */
		if (!processOutputPacket(outputPacket, &rideState))
		{
			printf("Critical: Failed to process the output packet\n");
			running = -1;
			break;
		}

		/* Step 5, write the output packet to the Lindbergh */
		if (!writePacket(fd, outputPacket))
		{
			printf("Critical: Failed to write output packet\n");
			running = -1;
			break;
		}

		if (DEBUG_MODE)
		{
			for (int i = 0; i < OUTPUT_PACKET_SIZE; i++)
			{
				printf("0x%02hhX ", outputPacket[i]);
			}
			printf("\n");
		}
	}

	printf("Info: Closing serial port\n");

	if (running < 0)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
