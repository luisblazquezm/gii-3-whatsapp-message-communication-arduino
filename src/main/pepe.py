#!/usr/bin/python
import serial
import syslog
import time

#The following line is for serial over GPIO
serial_port = '/dev/cu.usbmodem14201';
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)

ser = serial.Serial(serial_port, baud_rate)
time.sleep(2) # wait for Arduino

i = 0
msg = ""

while (1):
    # Serial write section
    if msg.find(":") != -1:
        setTempCar1 = raw_input("Content ")
        ser.flush()
        serTemp1 = str(setTempCar1)
        print ("Python value sent: ")
        print (serTemp1)
        ser.write(serTemp1)
        time.sleep(5)

    # Serial read section
    msg = ser.readline() # read all characters in buffer
    print (msg)
    i = i + 1
else:
    print "Exiting"
exit()