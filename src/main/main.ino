#include "main.h"

void setup() {

  GSM gsmAccess;
  boolean notConnected = true;     // GSM Connection state
  char pin[] = "5056";             // PIN number of the SIM Card of the GSM Shield we are using
  
  // Initialize serial communications and wait for port to open
  Serial.begin(9600);
    
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }

  pinMode(pinBuzzer, OUTPUT);

  // Initalice the pins for the KeyPad 
  for(byte i=0;i<rows;i++) {
    pinMode(Output[i],OUTPUT);
  }
  
  for(byte s=0;s<columns;s++) {
    pinMode(Input[s],INPUT_PULLUP);
  }

  /* Unlock the phone using the Keypad */
  unlockPhone();

  Serial.println("  =======================================================================================");
  Serial.println("                              Accessing Whatsapp application                             ");
  Serial.println("  =======================================================================================");
  
  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    Serial.println("Aqui");
    if(gsmAccess.begin("5056", true)==GSM_READY) {
      Serial.println("Connected");
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  //lcd.setCursor(0,0); /* LCD */
  //lcd.print('>' + remoteNum1); // From 12 -> 15 /* LCD */
  //print_msg_LCD(4);/* LCD */

  Serial.println("Introduzca el numero de telefono:");
  Serial.println("phone_number");
  int i = 0;
  while (1) {
    while (!Serial.available()) {}
    while (Serial.available()) 
    {
      delay(300);  //delay to allow buffer to fill VERY IMPORTANT, it worked beacuse of this
      if (Serial.available() >0)
      {
        char c = Serial.read();  //gets one byte from serial buffer
        receiver_phoneNumber[i] = c; //makes the string readString
        i++;
      }
      if (i == 12) break;
    }
    if (i == 12) break;
  }
  
  receiver_phoneNumber[i] = '\0';
  Serial.println("El numero introducido es " + String(receiver_phoneNumber));

  whatsapp_serial_limpiar_pantalla_menus();

  // Pins for LEDs
  pinMode(A0, OUTPUT); // LED verde (cuando se envia el mensaje)
  pinMode(A1, OUTPUT); // LED verde (cuando aparece nuestro mensaje en la pantalla) . Simboliza que el el recptero lo ha recibido 
  pinMode(A2, OUTPUT); // LED azul (parpadeante). Cuando llega el whatsapp

}

// Main code of the program. Bidirecctional communication
void loop() {    

  whatsapp_serial_menu();
 
}
