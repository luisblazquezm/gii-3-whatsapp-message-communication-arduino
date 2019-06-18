#include "main.h"

void setup() {

  GSM gsmAccess;
  boolean notConnected = true;     // GSM Connection state
  char pin[] = "5056";             // PIN number of the SIM Card of the GSM Shield we are using
  
  // Inicializar el puerto serie con los baudios requeridos
  Serial.begin(9600);

  // Definición de las dimensiones del LCD e inicialización de las mismas
  lcd.begin(16,2);                 // 16 columnas y 2 filas
  lcd.backlight();                 // Encender la luz de fondo
  lcd.createChar(5, flechaD);      // Crear el simbolo de la flecha -> a la derecha sobre el byte 5
  
  while (!Serial) {
    ; // Esperar a que se conecte el puerto serie
  }

  pinMode(pinBuzzer, OUTPUT);

  // Inicializacion de pines del joystick
  pinMode(pinEjeX, INPUT);          // Eje X
  pinMode(pinEjeY, INPUT);          // Eje Y
  pinMode(pinPulsador, INPUT_PULLUP); // Boton central - Pulsador

  // Inicialización de los pines del KeyPad 
  for(byte i=0;i<rows;i++) {
    pinMode(Output[i],OUTPUT);
  }
  
  for(byte s=0;s<columns;s++) {
    pinMode(Input[s],INPUT_PULLUP);
  }

  // Pantalla que logra simular el desbloqueo de un móvil como si de ello se tratase
  // nuestra aplicacion
  unlockPhone();

  Serial.println("  =======================================================================================");
  Serial.println("                              Accessing Whatsapp application                             ");
  Serial.println("  =======================================================================================");
  
  // Comienzo y conexión del GSM shield
  // Le pasamos el pin de la tarjeta SIM a través del parámetro begin para que logre acceder a los servicios GSM y GPRS
  
  while(notConnected)
  {
    if(gsmAccess.begin("5056", true)==GSM_READY) {
      lcd.print("Connected");
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0); /* LCD */

  // Limpiamos la pantalla para dejar lugar al menú principal
  whatsapp_serial_limpiar_pantalla_menus();

  // Tono de indicación acceso a la apliación
  play_tone("startup");

  // Iniciación de los pines para los LEDs verdes y azul de notificaciones
  pinMode(A0, OUTPUT); // LED verde (cuando se envia el mensaje)
  pinMode(A1, OUTPUT); // LED verde (cuando aparece nuestro mensaje en la pantalla) . Simboliza que el el recptero lo ha recibido 
  pinMode(A2, OUTPUT); // LED azul (parpadeante). Cuando llega el whatsapp

}

// Codigo principal del programa
void loop() {    

  // Aqui comienza el menú principal
  whatsapp_serial_menu();
 
}
