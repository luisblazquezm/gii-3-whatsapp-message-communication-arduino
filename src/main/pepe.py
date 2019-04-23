#!/usr/bin/python
import serial
import syslog
import time

#The following line is for serial over GPIO
serial_port = '/dev/cu.usbmodem14201';
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)

chats_file_path = "chats.txt";
contacts_file_path = "contacts.txt";

contacts_file = open(contacts_file_path, "r")
chats_file = open(chats_file_path, "a+");

ser = serial.Serial(serial_port, baud_rate)
time.sleep(2) # wait for Arduino

serial_content = ""
new_line = ""
phone_number = ""
msg_rcv = ""

while (1):

    # Serial read section
    serial_content = ser.readline() # read all characters in buffer
    serial_content = serial_content[:-2]

    if serial_content == "phone_number":
        print("aqui")
        setTempCar1 = raw_input("phoneNumber: ")
        ser.flush()
        serTemp1 = str(setTempCar1)
        ser.write(serTemp1)
        time.sleep(5)
    elif serial_content == "messages_1": # Everything different from the word content will be printed
        setTempCar1 = raw_input("\t\t\t\t")
        ser.flush()
        serTemp1 = str(setTempCar1)
        #print("Escribiendo envio en fichero...")
        ser.write(serTemp1)
        new_line = "\t\t\t\t" + serTemp1 + "\n\n"
        chats_file.write(new_line)
        time.sleep(5)
    elif serial_content == "recv_on":
        new_line = ""
        phone_number = ser.readline() # Reads the phone number first
        print (phone_number)
        print("Escribiendo numero en fichero...")
        phone_number = phone_number + "\n"
        chats_file.write(phone_number)

        while serial_content != "recv_off": # Reads the message of the receiver
            chr_rcv = ser.readline()
            print(chr_rcv)
            msg_rcv = msg_rcv + chr_rcv
            #print("Escribiendo mensaje en fichero...")
        
        msg_rcv = msg_rcv + "\n"
        chats_file.write(msg_rcv)
    elif serial_content == "contacts_transfer":
        for x in contacts_file:
            print(x)
            ser.write(x)
    else:
        print (serial_content)

else:
    print "Exiting"
exit()