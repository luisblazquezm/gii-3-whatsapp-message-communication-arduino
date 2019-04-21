##############
## Script listens to serial port and writes contents into a file
##############
## requires pySerial to be installed 
import serial
import syslog
import time

serial_port = '/dev/cu.usbmodem14201';
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)
write_to_file_path = "output.txt";

flag = 1
i = 0
output_file = open(write_to_file_path, "w+");
ser = serial.Serial(serial_port, baud_rate)

while True:
	if flag == 1:
		print("Voy a leer");
		line = ser.readline();
		line = line.decode("ascii")
		print(line);

	if i == 2:
		flag = 1

	if line.find(":") != -1:
		st = raw_input("Content ")
		print(st);
		ser.flush();
		i += 1
		flag = 0
		print(i)
		setTemp1 = str(st)
		ser.write(setTemp1)
		time.sleep(1)

	output_file.write(line);