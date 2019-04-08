#include <GSM.h>

#define PINNUMBER ""
#define PHONENUMBER "+34651550473"

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
    if(gsmAccess.begin("5056")==GSM_READY) {
      Serial.println("Connected");
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("Despues");
  delay("10000");

  Serial.println("GSM initialized");
}

void loop() {
  //Establecer el numero 
  Serial.println(PHONENUMBER);

  // send the message
  sms.beginSMS(PHONENUMBER);
  sms.print("Hola");
  sms.endSMS();

  delay(10000);
}
