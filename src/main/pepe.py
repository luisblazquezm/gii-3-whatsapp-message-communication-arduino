#!/usr/bin/python
import serial
import syslog
import time
import threading
import time
import re
import fileinput

#The following line is for serial over GPIO
serial_port = '/dev/cu.usbmodem14201';
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)

chats_file_path = "chats.txt";
contacts_file_path = "contacts.txt";

chats_file = open(chats_file_path, "a+");

ser = serial.Serial(serial_port, baud_rate)
time.sleep(2) # wait for Arduino

serial_content = ""
new_line = ""
phone_number = ""
msg_rcv = ""

setTempCar1 = ''
contact_var = ''
playingID = ''
finished = True
termin = False

def kbdListener():
    global setTempCar1, finished
    setTempCar1 = raw_input("\t\t\t\t::")
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
        setTempCar1 = raw_input("Telefono: ")
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
                print("Me salgo")
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
                break
            print(chr_rcv)
            msg_rcv = msg_rcv + chr_rcv
            #print("Escribiendo mensaje en fichero...")
        
        msg_rcv = msg_rcv + "\n"
        chats_file.write(msg_rcv) 
    elif serial_content == "contacts_transfer":
        contacts_file = open(contacts_file_path, "r");

        for x in contacts_file:
            #print(x)
            ser.write(x)
            time.sleep(5)
    elif serial_content == "contacts_msg":
        contact_var = raw_input("Contacto: ")
        ser.flush()
        serTemp1 = str(contact_var)

        with open(contacts_file_path) as search:
            for line in search:
                line = line.rstrip()  # remove '\n' at end of line
                #print(serTemp1)
                #print(line)
                if serTemp1 in line:
                    print("Contacto encontrado")
                    print(line)
                    start = line.find('+')
                    end = line.find('*', start)
                    print (line[start:end])
                    ser.write(line[start:end])
                    break
                else:
                    print("El contacto introducido no existe")

        setTempCar1 = ''
        search.close()
    elif serial_content == "contacts_add":
        contacts_file = open(contacts_file_path, "a+");

        print("Introduzca el nombre y telefono movil del nuevo contacto")
        name_contact = raw_input("Nombre: ")
        phone_contact = raw_input("Telefono: ")
        row = name_contact + " " + phone_contact + "*\n"
        contacts_file.write(row)
    elif serial_content == "contacts_delete":
        print("Introduzca el nombre del contacto a eliminar")
        name_contact = raw_input("Nombre: ")

        with open(contacts_file_path, "r") as f:
            lines = f.readlines()

        with open(contacts_file_path, "w") as f:
            for line in lines:
                if name_contact not in line.strip("\n"):
                    f.write(line)
    elif serial_content == "contacts_modify":
        print("Introduzca el nombre del contacto a eliminar")
        name_contact = raw_input("Nombre: ")
        new_name_contact = raw_input("Nuevo nombre: ")
        new_phone_contact = raw_input("Nuevo telefono: ")

        with open(contacts_file_path) as search:
            for line in search:
                line = line.rstrip()  # remove '\n' at end of line
                if name_contact in line:
                    print(line)
                    start = line.find('+')
                    end = line.find('*', start)
                    phone_contact = line[start:end]

                # Read in the file
        with open(contacts_file_path, 'r') as file :
          filedata = file.read()

        # Replace the target string
        if new_name_contact != '':
            filedata = filedata.replace(name_contact, new_name_contact)

        if new_phone_contact != '':
            filedata = filedata.replace(phone_contact, new_phone_contact)

        # Write the file out again
        with open(contacts_file_path, 'w') as file:
          file.write(filedata)

    elif serial_content == "terminate":
        print "Exiting"
        exit()
    else:
        print (serial_content)

else:
    print "Exiting"
exit()