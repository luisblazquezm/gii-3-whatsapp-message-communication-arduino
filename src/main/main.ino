#include "main.h"

void setup() {

  GSM gsmAccess;
  boolean notConnected = true;     // GSM Connection state
  char pin[] = "5056";             // PIN number of the SIM Card of the GSM Shield we are using
  
  // Initialize serial communications and wait for port to open
  Serial.begin(9600);
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  lcd.createChar(5, flechaD);
  
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }

  pinMode(pinBuzzer, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(kPin, INPUT_PULLUP);

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
    if(gsmAccess.begin("5056", true)==GSM_READY) {
      Serial.println("Connected");
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  lcd.clear();
  lcd.setCursor(0,0); /* LCD */

  whatsapp_serial_limpiar_pantalla_menus();

  play_tone("startup");

  // Pins for LEDs
  pinMode(A0, OUTPUT); // LED verde (cuando se envia el mensaje)
  pinMode(A1, OUTPUT); // LED verde (cuando aparece nuestro mensaje en la pantalla) . Simboliza que el el recptero lo ha recibido 
  pinMode(A2, OUTPUT); // LED azul (parpadeante). Cuando llega el whatsapp

}

// Main code of the program. Bidirecctional communication
void loop() {    

  whatsapp_serial_menu();
 
}
