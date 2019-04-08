
#include <GSM.h>

#define PINNUMBER ""
#define PHONENUMBER "+34651550473"

String msg = "";         // variable to receive data from the serial port
String phoneNumber = "";
String pN = "";
char remoteNum1[20];
char remoteNum2[20];

// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("SMS Messages Sender");

  // connection state
  boolean notConnected = true;

  Serial.println("Antes");
  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    Serial.println("Aqui");
    if(gsmAccess.begin("5056")==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  Serial.println("Despues");
  Serial.println("GSM initialized");
  
  // phoneNumber.equals("+34651550473")
  Serial.println("Introduzca el numero de telefono:");
  readSerial(remoteNum1);
  Serial.println("El numero introducido es " + String(remoteNum1));
  
}

void loop() {    

  while (1) {
    if (sms.available()) {
      recvMessage();
    } else {
      sendMessage();
    }
  }

  Serial.println("Saliendo...");
  while (1){}

}

void sendMessage()
{ 
        //Serial.println("Retorno es " + String(num));// send the messag
        
        do { // if data is available to read
            msg = Serial.readString();     // read the message
            Serial.println("Esperando...");
            if (sms.available()){
              Serial.println("Ha recibido algo");
              recvMessage();
            }
        } while (msg.equals(""));
        Serial.println("Luis: " + msg);

        int num = sms.beginSMS(remoteNum1);
        num = sms.print(msg);
        //Serial.println("Devuelve " + String(num) + " bytes");
        sms.endSMS();
        //Serial.println("Mensaje enviado!");
}

void recvMessage()
{
  char c;
  
      //Serial.println("Message received from:");
  
      // Get remote number
      sms.remoteNumber(remoteNum2, 20);
      //Serial.println(remoteNum2);
  
      // This is just an example of message disposal    
      // Messages starting with # should be discarded
      if(sms.peek()=='#')
      {
        Serial.println("Discarded SMS");
        sms.flush();
      }
  
      // Read message bytes and print them
      Serial.println(String(remoteNum2) + ":");
      while(c=sms.read())
        Serial.print(c);
  
      //Serial.println("\nEND OF MESSAGE");
  
      // delete message from modem memory
      sms.flush();
      //Serial.println("MESSAGE DELETED");
  
}

int readSerial(char result[]) {
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
