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

output_file = open(write_to_file_path, "w+");
ser = serial.Serial(serial_port, baud_rate)

while True:
    line = ser.readline();
    line = line.decode("ascii") #ser.readline returns a binary, convert to string
    print(line);

    if line.find(":") != -1:
        st = raw_input("Content ")
        print(st);
        ser.flush();
        setTemp1 = str(st)
        ser.write(setTemp1)
        time.sleep(1)
	
    output_file.write(line);