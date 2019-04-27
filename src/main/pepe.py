#!/usr/bin/python
import serial
import syslog
import time
import threading
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

setTempCar1 = ''
playingID = ''
finished = True
termin = False

def kbdListener():
    global setTempCar1, finished
    setTempCar1 = raw_input("\t\t\t\t")
    ser.flush()
    serTemp1 = str(setTempCar1)
    #print("Escribiendo envio en fichero...")
    ser.write(serTemp1)
    new_line = "\t\t\t\t" + serTemp1 + "\n\n"
    chats_file.write(new_line)
    #print "maybe updating...the kbdInput variable is: {}".format(new_line)
    finished = True

while (1):

    # Serial read section
    serial_content = ser.readline() # read all characters in buffer
    serial_content = serial_content[:-2]

    if serial_content == "phone_number":
        setTempCar1 = raw_input("phoneNumber: ")
        ser.flush()
        serTemp1 = str(setTempCar1)
        ser.write(serTemp1)
        setTempCar1 = ''
        time.sleep(5)
    elif serial_content == "messages_1":
        while(1):
            #print "kbdInput: {}".format(setTempCar1)
            #print "playingID: {}".format(playingID)
            if playingID != setTempCar1:
                #print "Received new keyboard Input. Setting playing ID to keyboard input value"
                playingID = setTempCar1
            elif setTempCar1 == "exit":
                # Kill thread
                break
            else:
                #print "No input from keyboard detected. Sleeping 5 seconds"
                if termin:
                    serial_content = ser.readline() # read all characters in buffer
                    serial_content = serial_content[:-2]
                    #print ("Ole mi pepe")
                    if serial_content == "recv_on":
                        new_line = ""
                        phone_number = ser.readline() # Reads the phone number first
                        print (phone_number)
                        #print("Escribiendo numero en fichero...")
                        phone_number = phone_number + "\n"
                        chats_file.write(phone_number)

                        while (1): # Reads the message of the receiver
                            chr_rcv = ser.readline()
                            chr_rcv = chr_rcv[:-2]
                            if chr_rcv == "recv_off":
                                #print("Me salgo")
                                break
                            print(chr_rcv)
                            msg_rcv = msg_rcv + chr_rcv
                            #print("Escribiendo mensaje en fichero...")
                        
                        msg_rcv = msg_rcv + "\n"
                        chats_file.write(msg_rcv)
                
            if finished:
                finished = False
                termin = True
                listener = threading.Thread(target=kbdListener)
                listener.start()
            time.sleep(2)

        #setTempCar1 = raw_input("\t\t\t\t")
        #ser.flush()
        #serTemp1 = str(setTempCar1)
        #print("Escribiendo envio en fichero...")
        #ser.write(serTemp1)
        #new_line = "\t\t\t\t" + serTemp1 + "\n\n"
        #chats_file.write(new_line)
        #time.sleep(5)
    elif serial_content == "recv_on":
        new_line = ""
        phone_number = ser.readline() # Reads the phone number first
        print (phone_number)
        #print("Escribiendo numero en fichero...")
        phone_number = phone_number + "\n"
        chats_file.write(phone_number)

        while (1): # Reads the message of the receiver
            chr_rcv = ser.readline()
            chr_rcv = chr_rcv[:-2]
            if chr_rcv == "recv_off":
                print("Me salgo")
                break
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