#include <GSM.h>
//#include <LiquidCrystal.h>

// Other variables 
const byte rows=4;               // Number of rows of keypad
const byte columns=4;            // Number of columnss of keypad
boolean notConnected = true;     // GSM Connection state

/* ============================= PINES DE CONEXION ============================= */

// Pins used for the LEDs. Arduino MEGA GSM shield has pins 2,3,7 and 10 reserved.
const int pinLED_1 = 9;                     // LED green when the message is sent
const int pinLED_2 = 8;                     // LED green when the message is received by the receiver
const int pinLED_3 = 6;                     // LED blue when the message has been read by the receiver

// Pin used for the Buzzer
const int pinBuzzer = 10;

// Pins used for the Keypad
const byte Output[rows]={25,27,29,31};      // Array of pins used as output for rows of keypad
const byte Input[columns]={33,35,37,39};    // Array of pins used as input for columnss of keypad

// Pins used for the LCD
//const int lcdPin[6]={51,53,9,11,12,13};

/* ============================= TECLADO DE MEMBRANA ============================= */

byte h=0,v=0;                   // Variables used in for loops
const unsigned long period=50;  // Little period used to prevent error
unsigned long kdelay=0;         // Variable used in non-blocking delay 
char key = 'p';                 // Variable to control the key pressed
bool flag = false;              // Flag to add a new introduced digit to the complete password
String mobile_code = "4568";     // Code to unlock the program using the keypad

/* ============================= SMS ============================= */

// GSM library instances to send SMS and to access GSM service in the shield
GSM gsmAccess;
GSM_SMS sms;

char pin[] = "5056";                  // PIN number of the SIM Card of the GSM Shield we are using
char* file_data;
String msg_send = "";                 // Message to send through the serial port to the mobile number
String msg_recv = "";                 // Message to receive from the serial port from another phone number
String phoneNumber = "";              // Phone number of the receiver
String pN = "";
char sender_phoneNumber[20];          // Variable used to store the number of the SENDER
char receiver_phoneNumber[20];        // Variable used to store the number of the RECEIVER
int8_t answer;

/* ============================= PANTALLA LCD ============================= */

// Initialize the library by providing the nuber of pins to it
//LiquidCrystal lcd(lcdPin[0], lcdPin[1], lcdPin[2], lcdPin[3], lcdPin[4], lcdPin[5]);

/* ============================= BUZZER ============================= */

double noteFreqArrSend[] = {
49.4, 52.3, 55.4, 58.7, 62.2, 65.9, 69.9, 74, 78.4, 83.1, 88, 93.2,
98.8, 105, 111, 117, 124, 132, 140, 148, 157, 166, 176, 186,
198, 209, 222, 235, 249, 264, 279, 296, 314, 332, 352, 373,
395, 419, 444, 470, 498, 527, 559, 592, 627, 665, 704, 746,
790, 837, 887, 940, 996, 1050, 1110, 1180, 1250, 1320, 1400, 1490,
1580, 1670, 1770, 1870, 1990, 2100};

double noteFreqArrRecv[] = {
49.4, 52.3, 55.4, 58.7, 62.2, 65.9, 69.9, 74, 78.4, 83.1, 88, 93.2,
98.8, 105, 111, 117, 124, 132, 140, 148, 157, 166, 176, 186,
198, 209, 222, 235, 249, 264, 279, 296, 314, 332, 352, 373,
395, 419, 444, 470, 498, 527, 559, 592, 627, 665, 704, 746,
790, 837, 887, 940, 996, 1050, 1110, 1180, 1250, 1320, 1400, 1490,
1580, 1670, 1770, 1870, 1990, 2100};

int noteDurationArrSend[] = {
  1, 3, 5, 6, 7
};

int noteDurationArrRecv[] = {
  1, 3, 5, 6, 7
};

int countTonesSend = 511;
int countTonesRecv = 0;
