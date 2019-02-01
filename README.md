# OpenLSA
Open Large Scale Attraction Emulation - An emulator for the ride boards in Let's Go Jungle Special, The House Of The Dead 4 Special, and possibly Jurassic Park Special

![LGJS Logo](https://vignette.wikia.nocookie.net/logopedia/images/1/1e/Lets_Go_Jungle_Special_Logo_1_a.gif/revision/latest?cb=20140213234611) ![HOTD4S Logo](https://vignette.wikia.nocookie.net/houseofthedead/images/4/42/Hotd4sp.png/revision/latest?cb=20170221115159)

## Game Information

### Let's Go Jungle Special

Let's go jungle special sends its serial commands to `/dev/ttyS0`. If this isn't populated on your Lindbergh you may need to symlink it using this command:

```
ln -s /dev/tts/0 /dev/ttyS0
```

## Protocol Information

- Baud Rate: 115200
- Recive's 7 bytes a go
  - 1st byte is always 0xC0
  - 2nd byte is checksum which is the exclusive bitwise or (^) operation over the next 5 payload bytes
  - 3rd to 7th byte is payload

## Emulator Information

The emulation is written in _python 2.7_ which you must have installed.

To run the emulator, open the openlsa.py file and change the file path to the RS232 device you are using. You can then type `python openlsa.py` and will start to see output from the Lindbergh device.
