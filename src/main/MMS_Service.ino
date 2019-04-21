/*
void sendMMS()
{
  answer = sendATcommand("AT", "OK", 2000); 
  if (answer == 1)
    Serial.println("Exito");
  else
    Serial.println("JAJA");
  while(1) {}//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  Serial.println("AT+CMMSINIT\r");
  delay(100);
  Serial.println(Serial.read());
  Serial.println("Respuesta recibida");
  while(1){}
  Serial2.print("AT+CMMSCURL=\"http://mms.movistar.com\"\r");
  delay(100);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+CMMSCID=1\r");
  delay(100);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+CMMSPROTO=\"10.138.255.5\",8080\r");
  delay(100);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+CMMSSENDCFG=6,3,0,0,2,4\r");
  delay(100);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+SAPBR=3,1,\"CONTYPE\",\"MMS\"\r");
  delay(100);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+SAPBR=3,1,\"APN\",\"mms.movistar.es\"\r");
  delay(100);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+SAPBR=1,1\r");
  delay(4000);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+SAPBR=2,1\r");
  delay(1000);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+CMMSEDIT=1\r");
  delay(100);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+CMMSDOWN=\"PIC\",19293,2000000,\"imagen.jpg\"\r");
  delay(1000);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }

  delay(1000);
  Serial2.print("AT+CMMSRECP=\"+34647829140\"\r");
  delay(100);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+CMMSVIEW\r");
  delay(2000);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+CMMSSEND\r");
  delay(2000);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+CMMSEDIT=0\r");
  delay(2000);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+CMMSTERM\r");
  delay(2000);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
}

int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialize the string
    
    delay(100);
    
    while( Serial.available() > 0) Serial.read();    // Clean the input buffer
    
    Serial.println(ATcommand);    // Send the AT command 


    x = 0;
    previous = millis();

    // this loop waits for the answer
    do{
        // if there are data in the UART input buffer, reads it and checks for the asnwer
        if(Serial.available() != 0){    
            response[x] = Serial.read();
            x++;
            // check if the desired answer is in the response of the module
            if (strstr(response, expected_answer) != NULL)    
            {
                answer = 1;
            }
        }
    // Waits for the asnwer with time out
    }while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;
}
*/
