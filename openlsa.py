import time
import serial

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

	if bytes == [0xC0]:
		checksum = ord(byte)

	if ord(byte) == 0xC0:
		bytes = [0xC0]

	checksum_total = checksum_total ^ ord(byte)

	if len(bytes) is 7:
		if checksum_total == checksum:
			print "[OK]",
		ser.write(0xC0)	
		ser.write(0x01)

		ser.write(0x01)
		for i in range(0, 13):
			ser.write(0x00)
		ser.flush()
		print " "
