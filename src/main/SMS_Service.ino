void start_communication() 
{
  while(1) {
    if (sms.available()) {
      // Get SIM number and print it 
      sms.remoteNumber(receiver_phoneNumber, 20);
      recvMessage();
    } else {
      sendMessage();
    }
  }
}


void sendMessage()
{ 
    String msg_send = "";                 // Message to send through the serial port to the mobile number
    Serial.println("messages_1");
    //print_msg_LCD(5);/* LCD */
    delay(3000);
    
    do { // If data is available to read
        while(!Serial.available()) { 
          if (sms.available()) 
            break;
        }
        
        while (Serial.available())
        {
          delay(300);  //delay to allow buffer to fill 
          if (Serial.available() >0)
          {
            char c = Serial.read();  //gets one byte from serial buffer
            msg_send += c; //makes the string readString
          }
        }
        
        if (sms.available()){
            Serial.println("***1 message received***");
            //print_msg_LCD(6);/* LCD */
            recvMessage();
          }
        // msg_send = Serial.readString();     // Read the message
        //Serial.println("Esperando...");
    } while (msg_send.equals(""));
    
    // Turns on second green LED
    //lcd.clear();/* LCD */
    digitalWrite(pinLED_1, HIGH);

    delay(5000);
    //print_msg_LCD(1);/* LCD */
    Serial.println("\t\t\t\t" + msg_send);

    // Turns on second green LED
    digitalWrite(pinLED_2, HIGH);

    int num = sms.beginSMS(receiver_phoneNumber);
    num = sms.print(msg_send);
    sms.endSMS();
    //play_tone("send");
    //Serial.println("Mensaje enviado!");
    delay(2000);

    digitalWrite(pinLED_1, LOW);
    digitalWrite(pinLED_2, LOW);
}

void recvMessage()
{
  char c;
  int i = 0;
  String msg_recv = "";                 // Message to receive from the serial port from another phone number
  
  // This is just an example of message disposal    
  // Messages starting with # should be discarded
  if(sms.peek()=='#')
  {
    //Serial.println("Discarded SMS");
    sms.flush();
  }

  // Read message bytes and print them
  Serial.println("recv_on");
  Serial.println(String(receiver_phoneNumber) + ":");
  while(c=sms.read()) {
    msg_recv = msg_recv + c;
    //Serial.println(c);
  }
  Serial.println(msg_recv);
  Serial.println("recv_off");
  //print_msg_LCD(2);/* LCD */

  // Turns on blue LED
  while (i < 5) {
    digitalWrite(pinLED_3, HIGH);
    delay(200);
    digitalWrite(pinLED_3, LOW);
    delay(200);
    i++;
  }
  digitalWrite(pinLED_3, LOW);
  
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
