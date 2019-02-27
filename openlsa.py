import time
import serial
import os

def ssend_byte(send_byte):
    global checksum_send, ser
    print str(send_byte),
    checksum_send = checksum_send ^ send_byte
    ser.write(send_byte)

print "OpenLSA Version 0.1 BETA"

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='/dev/tty.usbserial-FTB7NTX1',
    baudrate=115200
)

ser.isOpen()

print "Serial communication established"

bytes = []
checksum = 0x00
checksum_total = 0x00
while 1:
    byte = ser.read(1)
    bytes.append(ord(byte))
    print byte.encode('hex').upper(),


    if len(bytes) < 7:
        checksum_total = checksum_total ^ ord(byte)

    if ord(byte) == 0xC0:
        bytes = [0xC0]
        checksum_total = 0x00

    if len(bytes) == 7:
        if checksum_total == bytes[6]:
            print "[OK]"

	print "COMMAND: ", str(bytes[1]).encode('hex').upper()
	print "GUN REACTION P1: ", bytes[3] & 0x10 > 0
	print "GUN REACTION P2: ", bytes[3] & 0x20 > 0
	print "BLOW FRONT P1: ", bytes[3] & 0x01 > 0
	print "BLOW FRONT P2: ", bytes[3] & 0x02 > 0
	print "BLOW BACK P1: ", bytes[3] & 0x04 > 0
	print "BLOW BACK P2: ", bytes[3] & 0x08 > 0
	
        print "GAME STOP LAMP: ", bytes[5] & 0x08 > 0
	print "RESET LAMP: ", bytes[5] & 0x01 > 0
	print "ERROR LAMP: ", bytes[5] & 0x02 > 0
	print "SAFETY LAMP: ", bytes[5] & 0x04 > 0
	print "FLOOR LAMP: ", bytes[5] & 0x10 > 0
	print "SPOT LAMP: ", bytes[5] & 0x20 > 0

	print "BILLBOARD: ",
	if (bytes[4] & 0x07) == 0x07:
		print "BLUE"
	elif (bytes[4] & 0x07) == 0x06:
		print "GREEN"
	elif (bytes[4] & 0x07) == 0x05:
		print "RED"
	else:
		print "False"

	print "TURN: ", bytes[2]
