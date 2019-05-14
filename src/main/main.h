#include <GSM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Other variables 
const byte rows=4;               // Numero de filas del keypad
const byte columns=4;            // Number de columnas del keypad

/* ============================= PINES DE CONEXION ============================= */

// Pines usados para los LEDs. Arduino MEGA GSM shield tiene los pines 2,3,7 y 10 reservados.
const int pinLED_1 = 4;                     // LED green cuando se envía el mensaje
const int pinLED_2 = 5;                     // LED green cuando el mensaje es recibido por el receptor
const int pinLED_3 = 6;                     // LED blue cuando el mensaje es leido por el receptor

// Pines para el joystick
const int pinEjeX = A0;
const int pinEjeY = A1;
const int pinPulsador = 9;

// Pin usados para el Buzzer
const int pinBuzzer = 8;

// Pines usados para el Keypad
const byte Output[rows]={25,27,29,31};      // Array de pines usados para indicar las filas del keypad
const byte Input[columns]={33,35,37,39};    // Array de pines usados para indicar las columnas del keypad

/* ============================= TECLADO DE MEMBRANA ============================= */

unsigned long kdelay=0;         // Variable used in non-blocking delay 
bool flag = false;              // Flag to add a new introduced digit to the complete password

/* ============================= SMS ============================= */

// GSM library instances to send SMS and to access GSM service in the shield
GSM_SMS sms;

char sender_phoneNumber[20];          // Variable used to store the number of the SENDER
char receiver_phoneNumber[13];        // Variable used to store the number of the RECEIVER
char unk_receiver_phoneNumber[20];
int8_t answer;
int value = -1;
int limit = 2;
int limit2 = 2;

/* ============================= PANTALLA LCD ============================= */

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//Flecha izquierda
byte flechaD[8] = {
  0b00000,
  0b00100,
  0b00110,
  0b11111,
  0b00110,
  0b00100,
  0b00000,
  0b00000
};
