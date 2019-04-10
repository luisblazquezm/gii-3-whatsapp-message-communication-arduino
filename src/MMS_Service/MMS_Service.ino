/*
Project: Send MMS from SD Card Lesson
Programmer: Shahrulnizam Mat Rejab
Board: Arduino Mega
Last Modified: 14 December 2014
Website: http://shahrulnizam.com
*/

#include <SD.h>

#define  PWR   31
#define  CS    53

File dataFile;
int i;
unsigned char data=0;

void setup()
{
  pinMode(PWR,OUTPUT);
  pinMode(CS,OUTPUT);
  Serial.begin(9600);
  Serial2.begin(19200);
  digitalWrite(PWR,LOW);
  delay(10);
  digitalWrite(PWR,HIGH);
  delay(10);

  if (!SD.begin(CS)) Serial.println("initialization failed!");
  else Serial.println("initialization done.");  
}

void loop()
{
  if(Serial2.available())
  {
    while(Serial2.available())
    {
      data=Serial2.read();
      Serial.write(data);
    }
    data=0;
  }
  
  if(Serial.available())
  {
    data=Serial.read();
  }  
  
  if(data=='1')
  {
    Serial2.print("AT+CGMI\r"); //Manufacturer identification
  }  
  if(data=='2')
  {
    Serial2.print("AT+CGMM\r"); //Model identification
  }
  
  if(data=='3')
  {
    Serial2.print("AT+CGMR\r"); //Software version
  }
  
  if(data=='4')
  {
    Serial2.print("AT+CGSN\r"); //IMEI number
  }
  
  if(data=='5')
  {
    Serial2.print("ATD+60136289844;\r"); //Calling
  }
  
  if(data=='6')
  {
    Serial2.print("ATH\r"); //Hang Up
  }
  
  if(data=='7')
  {
    Serial2.print("AT+CMGF=1\r"); //Set text mode
    delay(100);
    Serial2.print("AT+CMGS="); //Send message
    Serial2.write((byte)0x22); //"
    Serial2.print("+60136289844"); //Phone no
    Serial2.write((byte)0x22); //"
    Serial2.write((byte)0x0D); //Enter
    Serial2.print("Hai, I'm Arduino");//Text message
    Serial2.write((byte)0x0D); //Enter
    Serial2.print("Reply, if you receive this message");//Text message
    Serial2.write((byte)0x1A); //Ctrl+Z
  }
  
  if(data=='8')
  {
    Serial2.print("AT+CMGR=1\r"); //Read message
  }
  
  if(data=='9')
  {
    Serial2.print("AT+CMGD=1,0\r"); //Delete message
  }  
  
  if(data=='s') sendMMS();
  data=0;
}

void sendMMS()
{
  Serial2.print("AT+CMMSINIT\r");
  delay(100);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }
  Serial2.print("AT+CMMSCURL=\"http://mms.celcom.net.my\"\r");
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
  Serial2.print("AT+CMMSPROTO=\"10.128.1.242\",8080\r");
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
  Serial2.print("AT+SAPBR=3,1,\"APN\",\"mms.celcom.net.my\"\r");
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
  Serial2.print("AT+CMMSDOWN=\"PIC\",19293,2000000,\"test.jpg\"\r");
  delay(1000);
  if(Serial2.available())
  {
    while(Serial2.available()) Serial.write(Serial2.read());
  }

  dataFile=SD.open("test.jpg");
  i=0;
  if(dataFile)
  {
    while(dataFile.available())
    {
      data=dataFile.read();
      if(data<0x10) Serial.print("0");
      Serial.print(data,HEX);
      i++;
      if((i%40)==0) Serial.println();
      Serial2.write(data);
    }
    dataFile.close();
  }  
  else
  {
    Serial.println("error opening test.jpg");
  }

  delay(1000);
  Serial2.print("AT+CMMSRECP=\"0133144409\"\r");
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
