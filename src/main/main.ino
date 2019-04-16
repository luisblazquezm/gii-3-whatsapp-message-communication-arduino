#include "main.h"

void setup() {
  // Initialize serial communications and wait for port to open:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }

  // Initalice the pins for the KeyPad 
  for(byte i=0;i<rows;i++) {
    pinMode(Output[i],OUTPUT);
  }
  
  for(byte s=0;s<columns;s++) {
    pinMode(Input[s],INPUT_PULLUP);
  }

  // Initialice the LCD screen 
  lcd.begin(16,2);

  /* Unlock the phone using the Keypad */
  unlockPhone();

  Serial.println("SMS Messages Sender");

  // Connection state
  boolean notConnected = true;

  Serial.println("Antes");
  
  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    Serial.println("Aqui");
    if(gsmAccess.begin(pin)==GSM_READY) {
      Serial.println("Connected");
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  Serial.println("Despues");
  Serial.println("GSM initialized");

  // Get SIM number and print it 
  sms.remoteNumber(remoteNum2, 20);
  lcd.setCursor(0,0);
  lcd.print('>' + remoteNum1); // From 12 -> 15

  // Get remote number and print it
  // phoneNumber.equals("+34651550473")
  Serial.println("Introduzca el numero de telefono:");
  readSerial(remoteNum1);
  Serial.println("El numero introducido es " + String(remoteNum1));
  print_msg_LCD('n');

  // Pins for LEDs
  pinMode(A0, OUTPUT); // LED verde (cuando se envia el mensaje)
  pinMode(A1, OUTPUT); // LED verde (cuando aparece nuestro mensaje en la pantalla) . Simboliza que el el recptero lo ha recibido 
  pinMode(A2, OUTPUT); // LED azul (parpadeante). Cuando llega el whatsapp
}

void loop() {    

  while (1) {
    if (sms.available()) {
      recvMessage();
    } else {
      sendMessage();
    }
  }

}
