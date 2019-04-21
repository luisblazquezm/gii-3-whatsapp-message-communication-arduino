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
  //lcd.begin(16,2); /* LCD */

  /* Unlock the phone using the Keypad */
  unlockPhone();

  Serial.println("Accessing Whatsapp application");
  
  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    Serial.println("Connecting to GSM. Please, keep waiting ...");
    
    if(gsmAccess.begin("5056", true)==GSM_READY) {
      Serial.println("Connected");
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  //Serial.clear();<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  //lcd.setCursor(0,0); /* LCD */
  //lcd.print('>' + remoteNum1); // From 12 -> 15 /* LCD */
  //print_msg_LCD(4);/* LCD */

  // Pins for LEDs
  pinMode(A0, OUTPUT); // LED verde (cuando se envia el mensaje)
  pinMode(A1, OUTPUT); // LED verde (cuando aparece nuestro mensaje en la pantalla) . Simboliza que el el recptero lo ha recibido 
  pinMode(A2, OUTPUT); // LED azul (parpadeante). Cuando llega el whatsapp
}

// Main code of the program. Bidirecctional communication
void loop() {    

  whatsapp_serial_menu();
  
  /* Here comes the menu GUI */

  if (sms.available()) {
    // Get SIM number and print it 
    sms.remoteNumber(receiver_phoneNumber, 20);
    recvMessage();
  } else {
    sendMessage();
  }
  

}
