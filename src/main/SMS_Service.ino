void sendMessage()
{ 
    Serial.println("Introduzca el mensaje:");
    print_msg_LCD('i');
    
    do { // If data is available to read
        msg_send = Serial.readString();     // Read the message
        Serial.println("Esperando...");
        if (sms.available()){
          Serial.println("Ha recibido algo");
          print_msg_LCD('m');
          recvMessage();
        }
    } while (msg_send.equals(""));
    
    // Turns on second green LED
    lcd.clear();
    digitalWrite(A0, HIGH);

    delay(5000);
    print_msg_LCD('s');
    Serial.println("Luis: " + msg_send);

    // Turns on second green LED
    digitalWrite(A1, HIGH);

    int num = sms.beginSMS(remoteNum1);
    //sendMMS();
    num = sms.print(file_data);
    sms.endSMS();
    Serial.println("Mensaje enviado!");
}

void recvMessage()
{
  char c;
  
  // This is just an example of message disposal    
  // Messages starting with # should be discarded
  if(sms.peek()=='#')
  {
    Serial.println("Discarded SMS");
    sms.flush();
  }

  // Read message bytes and print them
  Serial.println(String(remoteNum2) + ":");
  while(c=sms.read()) {
    msg_recv = msg_recv + c;
    Serial.print(c);
  }
  print_msg_LCD('r');

  // Turns on blue LED
  digitalWrite(A2, HIGH);

  // delete message from modem memory
  sms.flush();
  Serial.println("MESSAGE DELETED");
  
}

int readSerial(char result[]) 
{
  int i = 0;
  Serial.println("Introduzca el numero receptor");
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
