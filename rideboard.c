#include <fcntl.h>
#include <linux/serial.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

/* Buffer packet sizes */
#define OUTPUT_PACKET_SIZE 22
#define INPUT_PACKET_SIZE 7

/* How long to wait for data before timing out */
#define READ_TIMEOUT 200

/* Enums to represent the different states of the MotionSelectSwitch */
#define MOTION_OFF 0
#define MOTION_MILD 1
#define MOTION_NORMAL 2

/* The default file path of the serial interface */
#define DEFAULT_SERIAL_INTERFACE_PATH "/dev/ttyUSB0"

/* Variable to signify the state of the emulator */
static volatile int running = 0;

/* Struct to hold the internal state of the ride */
typedef struct
{
	char PlayerOneBlowFront;
	char PlayerOneBlowBack;
	char PlayerTwoBlowFront;
	char PlayerTwoBlowBack;
	char PlayerOneGunReaction;
	char PlayerTwoGunReaction;
	char ResetLamp;
	char ErrorLamp;
	char SafetyLamp;
	char GameStopLamp;
	char FloorLamp;
	char SpotLamp;
	char BillboardLamp;
	char InitButton;
	char ResetButton;
	char MotionSelectSwitch; // 0 Motion Off, 1 Motion Gentle, 2 Motion Normal
	char TowerGameStopButton;
	char RideGameStopButton;
	char RearFootSensor;
	char LeftFootSensor;
	char FrontFootSensor;
	char RightDoorSensor;
	char LeftDoorSensor;
	char ArmrestSensor;
	char PlayerOneSeatbeltSensor;
	char PlayerTwoSeatbeltSensor;
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

	return read(serialPort, packet, INPUT_PACKET_SIZE) == INPUT_PACKET_SIZE;
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
	return write(serialPort, packet, OUTPUT_PACKET_SIZE) == OUTPUT_PACKET_SIZE;
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

	/* Feedback outputs */
	state->PlayerOneBlowFront   = (packet[3] & 0b00000001) > 0;
	state->PlayerTwoBlowFront   = (packet[3] & 0b00000010) > 0;
	state->PlayerOneBlowBack    = (packet[3] & 0b00000100) > 0;
	state->PlayerTwoBlowBack    = (packet[3] & 0b00001000) > 0;
	state->PlayerOneGunReaction = (packet[3] & 0b00010000) > 0;
	state->PlayerTwoGunReaction = (packet[3] & 0b00100000) > 0;

	/* Lamp outputs */
	state->ResetLamp            = (packet[5] & 0b00000001) > 0;
	state->ErrorLamp            = (packet[5] & 0b00000010) > 0;
	state->SafetyLamp           = (packet[5] & 0b00000100) > 0;
	state->GameStopLamp         = (packet[5] & 0b00001000) > 0;
	state->FloorLamp            = (packet[5] & 0b00010000) > 0;
	state->SpotLamp             = (packet[5] & 0b00100000) > 0;

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

	/* Fill the other packets */
	packet[1]  = 0x00;
	packet[2]  = 0x01; // Needs to be 0x01
	packet[3]  = 0x00; // Needs to be 0x01
	packet[4]  = 0x7f; // Needs to be 0x01
	packet[5]  = 0xbf; // Needs to be 0x01
	packet[6]  = 0x80; // Needs to be 0x01
	packet[7]  = 0x00; // Needs to be 0x01
	packet[8]  = 0x00; // Needs to be 0x01
	packet[9]  = 0x00; // Needs to be 0x01
	packet[10] = 0x00; // Needs to be 0x01
	packet[11] = 0x02; // Needs to be 0x01
	packet[12] = 0x03; // Needs to be 0x01
	packet[13] = 0x04; // Needs to be 0x01
	packet[14] = 0x01; // Needs to be 0x01
	packet[15] = 0x00; // Needs to be 0x01
	packet[16] = 0x01; // Needs to be 0x01
	packet[17] = 0x00; // Needs to be 0x01
	packet[18] = 0x01; // Needs to be 0x01
	packet[19] = 0x00; // Needs to be 0x01
	packet[20] = 0x00; // Needs to be 0x01

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
int processEmulation(RideState* state) {
	/* If the error lamp is on, spam the reset button */
	if(state->ErrorLamp) {
		state->ResetButton = !state->ResetButton;
	} else {
		state->ResetButton = 0;
	}

	return 1;
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
			printf("usage: %s [SERIAL_PORT_PATH]\n", argv[0]);
			return EXIT_SUCCESS;
		}

		serialInterfacePath = argv[1];
	}

	printf("Opening Serial Port %s\n", serialInterfacePath);
	if ((fd = open(serialInterfacePath, O_RDWR | O_NOCTTY)) < 0)
	{
		printf("Failed to open serial port, exiting.\n");
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
		if (!readPacket(fd, inputPacket))
		{
			printf("Critical: Failed to read input packet\n");
			running = -1;
			break;
		}

		/* Step 2, process the input packet */
		if (!processInputPacket(inputPacket, &rideState))
		{
			printf("Critical: Failed to process the input packet\n");
			running = -1;
			break;
		}

		/* Step 3, process any emulation logic such as setting buttons */
		if(!processEmulation(&rideState)) {
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
	}

	printf("Closing serial port\n");

	if (running < 0)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
