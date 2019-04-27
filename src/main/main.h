#include <GSM.h>
//#include <LiquidCrystal.h>

// Other variables 
const byte rows=4;               // Number of rows of keypad
const byte columns=4;            // Number of columnss of keypad

/* ============================= PINES DE CONEXION ============================= */

// Pins used for the LEDs. Arduino MEGA GSM shield has pins 2,3,7 and 10 reserved.
const int pinLED_1 = 4;                     // LED green when the message is sent
const int pinLED_2 = 5;                     // LED green when the message is received by the receiver
const int pinLED_3 = 6;                     // LED blue when the message has been read by the receiver

// Pin used for the Buzzer
const int pinBuzzer = 8;

// Pins used for the Keypad
const byte Output[rows]={25,27,29,31};      // Array of pins used as output for rows of keypad
const byte Input[columns]={33,35,37,39};    // Array of pins used as input for columnss of keypad

// Pins used for the LCD
//const int lcdPin[6]={51,53,9,11,12,13};

/* ============================= TECLADO DE MEMBRANA ============================= */

unsigned long kdelay=0;         // Variable used in non-blocking delay 
bool flag = false;              // Flag to add a new introduced digit to the complete password

/* ============================= SMS ============================= */

// GSM library instances to send SMS and to access GSM service in the shield
GSM_SMS sms;

char sender_phoneNumber[20];          // Variable used to store the number of the SENDER
char receiver_phoneNumber[13];        // Variable used to store the number of the RECEIVER
int8_t answer;
int value = -1;

/* ============================= PANTALLA LCD ============================= */

// Initialize the library by providing the nuber of pins to it
//LiquidCrystal lcd(lcdPin[0], lcdPin[1], lcdPin[2], lcdPin[3], lcdPin[4], lcdPin[5]);
