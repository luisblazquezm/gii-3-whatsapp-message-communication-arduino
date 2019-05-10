void start_communication() 
{
  get_contact_number();
  
  while(1) {
    if (sms.available()) {
      // Get SIM number and print it 
      recvMessage();
    } else {
      value = sendMessage();
      if (value == 0){
        digitalWrite(pinLED_2, LOW);
        break;
      }
    }
  }
  
  whatsapp_serial_enviar_mensaje();
}


int sendMessage()
{ 
    String msg_send = "";                 // Message to send through the serial port to the mobile number
    Serial.println("messages_1");
    print_msg_LCD("Introduce_message", "");/* LCD */
    delay(3000);
    
    do { // If data is available to read
        while(!Serial.available()) { 
          //Serial.println("Aqui !serial");
          if (sms.available()) 
            break;
        }
        
        while (Serial.available())
        {
          //Serial.println("Aqui serial");
          delay(300);  //delay to allow buffer to fill 
          if (Serial.available() >0)
          {
            char c = Serial.read();  //gets one byte from serial buffer
            msg_send += c; //makes the string readString
          }
        }
        
        if (sms.available()){
            //Serial.println("***1 message received***");
            print_msg_LCD("Received", "");/* LCD */
            recvMessage();
          }
         //Serial.println("Aqui fuera");
        // msg_send = Serial.readString();     // Read the message
        //Serial.println("Esperando...");
    } while (msg_send.equals(""));

    if (msg_send.equals("exit")) {
      digitalWrite(pinLED_2, HIGH);
      return 0;
    }
    
    // Turns on second green LED
    lcd.clear();/* LCD */
    digitalWrite(pinLED_1, HIGH);

    delay(5000);
    print_msg_LCD("msg_send", msg_send);/* LCD */
    //Serial.println("\t\t\t\t" + msg_send);

    // Turns on second green LED
    digitalWrite(pinLED_2, HIGH);

    int num = sms.beginSMS(receiver_phoneNumber);
    num = sms.print(msg_send);
    sms.endSMS();
    //Serial.println("Mensaje enviado!");
    delay(2000);

    digitalWrite(pinLED_1, LOW);
    digitalWrite(pinLED_2, LOW);

    return 1;
}

void recvMessage()
{
  char c;
  int i = 0;
  String msg_recv = "";                 // Message to receive from the serial port from another phone number

  sms.remoteNumber(unk_receiver_phoneNumber, 20);
  
  // This is just an example of message disposal    
  // Messages starting with # should be discarded
  if(sms.peek()=='#')
  {
    //Serial.println("Discarded SMS");
    sms.flush();
  }

  // Read message bytes and print them
  Serial.println("recv_on");
  
  if(strcmp(unk_receiver_phoneNumber, receiver_phoneNumber) == 0) {
    Serial.println(String(receiver_phoneNumber) + ":");
  } else {
    Serial.println(String(unk_receiver_phoneNumber) + ":");
  }
  
  while(c=sms.read()) {
    msg_recv = msg_recv + c;
    //Serial.println(c);
  }
  
  Serial.println(msg_recv);
  Serial.println("recv_off");

  play_tone("recv");

  // Turns on blue LED
  while (i < 5) {
    digitalWrite(pinLED_3, HIGH);
    delay(200);
    digitalWrite(pinLED_3, LOW);
    delay(200);
    i++;
  }
  digitalWrite(pinLED_3, LOW);

  print_msg_LCD("msg_recv", msg_recv);/* LCD */
  
  // delete message from modem memory
  sms.flush();
  //Serial.println("MESSAGE DELETED");
  
}

int readSerial(char result[]) 
{
  int i = 0;
  //Serial.println("Introduzca el numero receptor");
  
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}

void introduce_number_serial()
{
  Serial.println("Introduzca el numero de telefono:");
  Serial.println("phone_number");
  int i = 0;
  while (1) {
    while (!Serial.available()) {}
    while (Serial.available()) 
    {
      delay(300);  //delay to allow buffer to fill VERY IMPORTANT, it worked beacuse of this
      if (Serial.available() >0)
      {
        char c = Serial.read();  //gets one byte from serial buffer
        receiver_phoneNumber[i] = c; //makes the string readString
        i++;
      }
      if (i == 12) break;
    }
    if (i == 12) break;
  }
  
  receiver_phoneNumber[i] = '\0';
  Serial.println("El numero introducido es " + String(receiver_phoneNumber));
  
}

void get_contact_number()
{
  Serial.println("Introduzca el contacto:");
  Serial.println("contacts_msg");
  int i = 0;
  while (1) {
    while (!Serial.available()) {}
    while (Serial.available()) 
    {
      delay(300);  //delay to allow buffer to fill VERY IMPORTANT, it worked beacuse of this
      if (Serial.available() >0)
      {
        char c = Serial.read();  //gets one byte from serial buffer
        receiver_phoneNumber[i] = c; //makes the string readString
        i++;
        //Serial.println(c);
      }
      if (i == 12) break;
    }
    if (i == 12) break;
  }
  
  receiver_phoneNumber[i] = '\0';
  //lcd.print('>' + sender_phoneNumber); // From 12 -> 15 /* LCD */
  print_msg_LCD("Telephone numbers", "");/* LCD */
  //Serial.println("El numero del contacto es " + String(receiver_phoneNumber));

}
