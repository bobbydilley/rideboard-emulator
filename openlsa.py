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

    if len(bytes) < 7:
        checksum_total = checksum_total ^ ord(byte)

    if ord(byte) == 0xC0:
        bytes = [0xC0]
        checksum_total = 0x00


    if len(bytes) == 7:
        if checksum_total == byte[6]:
            print "[OK]",

            print "C0",
            ser.write(0xC0)
            checksum_send = 0x00
            for i in range(0, 20):
                send_byte = 0x00
                print str(send_byte),
                checksum_send = checksum_send ^ send_byte
                ser.write(send_byte)

            print str(checksum_send),
            ser.write(checksum_send)
            ser.flush()
            print "[SENT] "
