# OpenLSA
Open Large Scale Attraction Emulation - An emulator for the ride boards in Let's Go Jungle Special, The House Of The Dead 4 Special, and Jurassic Park Special

![LGJS Logo](https://vignette.wikia.nocookie.net/logopedia/images/1/1e/Lets_Go_Jungle_Special_Logo_1_a.gif/revision/latest?cb=20140213234611)

## Protocol Information

- Baud Rate: 115200
- Recive's 7 bytes a go
  - 1st byte is always 0xC0
  - 2nd byte is checksum which is the exclusive bitwise or (^) operation over the next 5 payload bytes
  - 3rd to 7th byte is payload
