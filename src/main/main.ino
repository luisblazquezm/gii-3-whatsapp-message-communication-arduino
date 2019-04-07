
#include <GSM.h>

#define PINNUMBER ""
#define PHONENUMBER ""

char var1, var2;
String msg = "";         // variable to receive data from the serial port
String phoneNumber = ""; // phoneNumber
char buf[200];

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
  delay("10000");

  Serial.println("GSM initialized");
}

void loop() {
    // Primero lee el numero de telefono 
    if (Serial.available())  { // if data is available to read
      //var1 = Serial.read();
      //if ( var1 == 's') 
      phoneNumber = Serial.readString();     // read it and store it in 'val'
    }

    Serial.println("El numero es: " + phoneNumber);
    
    if( phoneNumber.equals("+34651550473") ) {         // if 'redOn' was received
      phoneNumber.toCharArray(buf, 200);
      sms.beginSMS(buf);         // send the message

      if (Serial.available())  {      // if data is available to read
        //var2 = Serial.read();
        //if ( var2 == 'm') 
        msg = Serial.readString();     // read the message
      }

      Serial.println("El mensaje es: " + msg);
      
      if ( msg.equals(phoneNumber) ) {
        Serial.println("Error, el mensaje es igual que el numero de telfoeno");
        return;
      } else {
        Serial.println("Mensaje enviado!");
        sms.print(msg);
        sms.endSMS();
      }
      
    } else {
      Serial.println("Error, el numero introducido es:" + phoneNumber);
    }
    
    delay(10000);
}
