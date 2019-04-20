#include <GSM.h>
#include <LiquidCrystal.h>

const byte rows=4;               //number of rows of keypad
const byte columns=4;            //number of columnss of keypad

/* ============================= PINES DE CONEXION ============================= */
// Reserved pins 2,3,7,10
const int pinLED_1 = 9;
const int pinLED_2 = 8;
const int pinLED_3 = 6;
const int pinBuzzer = 10;
const byte Output[rows]={25,27,29,31};      //array of pins used as output for rows of keypad
const byte Input[columns]={33,35,37,39}; //array of pins used as input for columnss of keypad
const int lcdPin[6]={51,53,9,11,12,13};

/* ============================= TECLADO DE MEMBRANA ============================= */

byte h=0,v=0;    //variables used in for loops
const unsigned long period=50;  //little period used to prevent error
unsigned long kdelay=0;        // variable used in non-blocking delay 
char key = 'p';
bool flag = false;

/* ============================= SMS ============================= */

// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;

char pin[] = "5056";
char* file_data;
String msg_send = "";         // variable to receive data from the serial port
String msg_recv = "";
String phoneNumber = "";
String pN = "";
char remoteNum1[20];
char remoteNum2[20];
int8_t answer;

/* ============================= PANTALLA LCD ============================= */

// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(lcdPin[0], lcdPin[1], lcdPin[2], lcdPin[3], lcdPin[4], lcdPin[5]);

/* ============================= BUZZER ============================= */

const int tonos[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
const int countTonos = 10;
