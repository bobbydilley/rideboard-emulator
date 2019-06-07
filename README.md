# OpenLSA
Open Large Scale Attraction Emulator (OpenLSA) is an emulator for the ride boards in Let's Go Jungle Special, The House Of The Dead 4 Special, and possibly Jurassic Park Special. The project aims to document the protocol so that large attraction games using these boards, can be played at home.

# Reverse Engineer

All of the reverse engineering info is stored here:

https://raw.githubusercontent.com/bobbydilley/OpenLSA/master/code_recreations/struct.md

## Game Information

### Let's Go Jungle Special

Let's go jungle special sends its serial commands to `/dev/ttyS0`. If this isn't populated on your Lindbergh you may need to symlink it using this command:

```
ln -s /dev/tts/0 /dev/ttyS0
```

## Other bits of information

### Attendants Tower

The attendants tower swithches are not run via JVS.

## Protocol Information

- Baud Rate: 115200
- Recive: 7 bytes a go
  - 1st byte is always 0xC0
  - 2nd to 6th byte is payload
  - 7th byte is checksum which is the exclusive bitwise or (^) operation over the last 5 payload bytes
  
- Send: 22 bytes a go
  - 1st byte is always 0xC0
  - 2nd to 21st byte is payload
  - 22nd byte is checksum which is the exclusive bitwise or (^) operation over the previous 20 bytes.

## Dumps

When the machine is starting up this is repeated:

```
C0 01 00 00 01 00 00
```

When the machine is erroring this is repeated indefinately: 

```
C0 16 00 00 04 00 12
```

When the machine is in test mode this is repeated indefinately:

```
C0 13 00 00 00 00 13
```

When dummy serial is turned on, and its waiting for the INITIALIZE button:

```
C0 02 00 00 01 00 03
```

What I think the things are now

C0 - SYNC BYTE
02 - COMMAND
00 - CHAIR POSITION
00 - LIGHT/BLOWER
01 - LIGHT/BLOWER?
00 - LIGHT/BLOWER
03 - CHECK SUM

Buttons are not connected to JVS, but I think possibly they keyboard was used to simluate the button!? There is a link to /dev/input/js0.

## Emulator Information

The emulation is written in _python 2.7_ which you must have installed.

To run the emulator, open the openlsa.py file and change the file path to the RS232 device you are using. You can then type `python openlsa.py` and will start to see output from the Lindbergh device.
