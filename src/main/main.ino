
#include <GSM.h>

#define PINNUMBER ""
#define PHONENUMBER "+34651550473"

String msg = "";         // variable to receive data from the serial port
String phoneNumber = "";
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
  Serial.println("GSM initialized");
}

void loop() {
    // Primero lee el numero de telefono 
      //var1 = Serial.read();
      //if ( var1 == 's') 
      //phoneNumber = Serial.readString();     // read it and store it in 'val'
      
      //phoneNumber = '+' + phoneNumber;
      
              // phoneNumber.equals("+34651550473")
        phoneNumber = "+34651550473";     // read it and store it in 'val'
        phoneNumber.toCharArray(buf, 200);
        Serial.println(buf);
        sms.beginSMS(buf);         // send the message
        Serial.println("SMS ya ha begineado");
        delay(7000);
        Serial.println("DENTRO DE MSG");
        //var2 = Serial.read();
        //if ( var2 == 'm') 
        
        while (Serial.available())  { // if data is available to read
          
            Serial.println("Introduzca el mensaje a mandar");
            msg = Serial.readString();     // read the message
            Serial.println("El mensaje es: " + msg);
            
            Serial.println("Mensaje enviado!");
            sms.print(msg);
            sms.endSMS();
            
          
            delay(10000);
            while (1)
            {
            }
        }


}
