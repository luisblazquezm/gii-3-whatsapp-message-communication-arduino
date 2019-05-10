#!/usr/bin/python
import serial
import syslog
import time
import threading
import time
import re
import fileinput

#######################################
#                                     #
#             VARIABLES               #
#                                     #
#######################################


#The following line is for serial over GPIO
serial_port = '/dev/cu.usbmodem14201';
baud_rate = 9600; #In arduino, Serial.begin(baud_rate)

contacts_file_path = "contacts.txt"
chats_file = ""
user_chats_file_path = ""
unknown_chats_file_path = ""
chat_new_file = ""

ser = serial.Serial(serial_port, baud_rate)
time.sleep(2) # wait for Arduino

serial_content = ""
new_line = ""
phone_number = ""
msg_rcv = ""
phone_number_contact = ""

setTempCar1 = ''
contact_var = ''
playingID = ''
finished = True
termin = False
flag_found = 0
flag_found_2 = 0


#######################################
#                                     #
#             FUNCTIONS               #
#                                     #
#######################################


def kbdListener():
    global setTempCar1, finished
    setTempCar1 = raw_input("\t\t\t\t::")
    ser.flush()
    serTemp1 = str(setTempCar1)
    #print("Escribiendo envio en fichero...") # -- DEBUG -- 
    ser.write(serTemp1)
    new_line = "\t\t\t\t" + serTemp1 + "\n\n"
    chats_file.write(new_line)
    #print "maybe updating...the kbdInput variable is: {}".format(new_line) # -- DEBUG -- 
    finished = True

def whattsapp_recv(phoneNumb):
    global chat_new_file
    if phoneNumb != phone_number_contact:
        with open(contacts_file_path) as search:
            for line in search:
                line = line.rstrip()  # remove '\n' at end of line
                if phoneNumb in line:
                    print("Este amor no se toca")
                    start = 0;
                    end = line.find('+', start)
                    contact = line[start:end]
                    contact = contact.rstrip()
                    print_msg = "**Nuevo whattsapp de " + contact + "**"
                    flag_found = 1
                    break

            if flag_found == 0:
                print_msg = "**Nuevo whattsapp del numero " + phoneNumb + "**"
                contact = phoneNumb
            else:
                flag_found = 0

        search.close()

        print(print_msg)
        unknown_chats_file_path = "chats_" + contact + ".txt";
        print(unknown_chats_file_path)
        chat_new_file = open(unknown_chats_file_path, "a+");
    else:
        #print("Escribiendo numero en fichero...") # -- DEBUG -- 
        phoneNumb = phoneNumb + "\n"
        chats_file.write(phoneNumb)


#######################################
#                                     #
#                MAIN                 #
#                                     #
#######################################

while (1):

    # Serial read section
    serial_content = ser.readline() # read all characters in buffer
    serial_content = serial_content[:-2]

    if serial_content == "phone_number": # Introduce the phone number of the receiver -- DEBUG --

        setTempCar1 = raw_input("Telefono: ")
        ser.flush()
        serTemp1 = str(setTempCar1)
        ser.write(serTemp1)

        setTempCar1 = ''
        time.sleep(5)

    elif serial_content == "messages_1":

        with open(user_chats_file_path) as search:
            for line in search:
                line = line.rstrip()  # remove '\n' at end of line
                print(line)

        while(1):
            #print "kbdInput: {}".format(setTempCar1) # -- DEBUG -- 
            #print "playingID: {}".format(playingID) # -- DEBUG -- 
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
                    #print ("Ole mi pepe") # -- DEBUG -- 
                    if serial_content == "recv_on":
                        new_line = ""
                        phone_number = ser.readline() # Reads the phone number first
                        phone_number = phone_number[:-3]
                        msg_to_print = "El num es " + phone_number # -- DEBUG -- 
                        print (msg_to_print) # -- DEBUG -- 
                        print (phone_number_contact) # -- DEBUG -- 

                        whattsapp_recv(phone_number)

                        while (1): # Reads the message of the receiver
                            chr_rcv = ser.readline()
                            chr_rcv = chr_rcv[:-2]
                            if chr_rcv == "recv_off":
                                #print("Me salgo")
                                break
                            if phone_number == phone_number_contact:
                                print(chr_rcv)
                            msg_rcv = msg_rcv + chr_rcv
                            #print("Escribiendo mensaje en fichero...")
                        
                        msg_rcv = msg_rcv + "\n"

                        if phone_number == phone_number_contact:
                            chats_file.write(msg_rcv)
                        else:
                            print(chat_new_file)
                            chat_new_file.write(msg_rcv);
                            chat_new_file.close()

            if finished:
                finished = False
                termin = True
                listener = threading.Thread(target=kbdListener)
                listener.start()

            time.sleep(2)

    elif serial_content == "recv_on":

        new_line = ""
        phone_number = ser.readline() # Reads the phone number first
        print (phone_number)
        phone_number = phone_number[:-3]
        msg_to_print = "El num es " + phone_number # -- DEBUG -- 
        print (msg_to_print) # -- DEBUG -- 
        print (phone_number_contact) # -- DEBUG -- 
        
        whattsapp_recv(phone_number)

        while (1): # Reads the message of the receiver
            chr_rcv = ser.readline()
            chr_rcv = chr_rcv[:-2]
            if chr_rcv == "recv_off":
                break
            if phone_number == phone_number_contact:
                print(chr_rcv)
            
            msg_rcv = msg_rcv + chr_rcv
            #print("Escribiendo mensaje en fichero...")
        
        msg_rcv = msg_rcv + "\n"
        if phone_number == phone_number_contact:
            chats_file.write(msg_rcv)
        else:
            chat_new_file.write(msg_rcv);
            chat_new_file.close()
        
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
                    phone_number_contact = line[start:end]
                    print (phone_number_contact)
                    ser.write(line[start:end])
                    flag_found_2 = 1
                    break
        
        if flag_found_2 == 0:
            print("El contacto introducido no existe")
        else:
            flag_found_2 = 0

        setTempCar1 = ''
        search.close()

        user_chats_file_path = "chats_" + contact_var + ".txt";
        chats_file = open(user_chats_file_path, "a+");

    elif serial_content == "contacts_add":

        contacts_file = open(contacts_file_path, "a+");

        print("Introduzca el nombre y telefono movil del nuevo contacto")
        name_contact = raw_input("Nombre: ")
        phone_contact = raw_input("Telefono: ")
        row = name_contact + " " + phone_contact + "*\n"
        contacts_file.write(row)

        contacts_file.close()

    elif serial_content == "contacts_delete":

        print("Introduzca el nombre del contacto a eliminar")
        name_contact = raw_input("Nombre: ")

        with open(contacts_file_path, "r") as f:
            lines = f.readlines()

        with open(contacts_file_path, "w") as f:
            for line in lines:
                if name_contact not in line.strip("\n"):
                    f.write(line)

        f.close()

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

        search.close()
        file.close()

    elif serial_content == "terminate":
        print "Exiting"
        exit()
    else:
        print (serial_content)
