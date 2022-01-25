# Sega Lindbergh Rideboard Emulator

This project is an emulator for the following large scale attraction arcade games:

- Let's Go Jungle Special
- The House Of The Dead 4 Special

It's possible that this would also work for The Lost World Special, however I've never seen a real machine to test it with.

## Building & Running

To build and run on Ubuntu, use the following commands:

```
sudo apt install build-essential git
git clone https://github.com/bobbydilley/rideboard-emulator
cd rideboard-emulator
gcc rideboard.c -o rideboard
sudo ./rideboard
```

You can pass the path of your serial device in when running using the following:

```
sudo ./rideboard /dev/ttyUSB1
```

## Running on Lindbergh

The source and executable for a version of this software that runs on the Lindbergh has also been included.

You should run the software before starting the executable for the game, by adding this line before the game is called in the `disk0/hotd4-sp/elf/game` file.

```
$(pwd)/rideboard-emulator &
```

## Protocol Information

The board communicates with the Sega Lindbergh motherboard through one of the serial ports on the front of the device.

- Baud Rate: 115200

- Receives 7 bytes a go
  - 1st byte is always 0xC0
  - 2nd to 6th byte is payload
  - 7th byte is checksum which is the exclusive bitwise or (^) operation over the last 5 payload bytes
  
- Responds with 22 bytes a go
  - 1st byte is always 0xC0
  - 2nd to 21st byte is payload
  - 22nd byte is checksum which is the exclusive bitwise or (^) operation over the previous 20 bytes.
