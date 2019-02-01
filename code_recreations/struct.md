The LGJCbord struct memory layout:

      005: serial port object


32 -> 037: CLASS SEND BUFFER
      038: some checksum variable
39 -> 045: SERIAL SEND BUFFER
46 -> 067: CLASS RECEIVE BUFFER
68 -> 195: SERIAL RECIEVE BUFFER
