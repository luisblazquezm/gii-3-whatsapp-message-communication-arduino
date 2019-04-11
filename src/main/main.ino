#include <GSM.h>

#define PINNUMBER ""
#define PHONENUMBER "+34651550473"
char pin[] = "5056";

/* ============================= TECLADO DE MEMBRANA ============================= */

byte h=0,v=0;    //variables used in for loops
const unsigned long period=50;  //little period used to prevent error
unsigned long kdelay=0;        // variable used in non-blocking delay 
const byte rows=4;             //number of rows of keypad
const byte columns=4;            //number of columnss of keypad
const byte Output[rows]={4,5,6,8}; //array of pins used as output for rows of keypad
const byte Input[columns]={9,11,12,13}; //array of pins used as input for columnss of keypad
char key = 'p';
bool flag = false;

/* ============================= SMS ============================= */

// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;

/* ============================= OTRAS VARIABLES ============================= */

String msg = "";         // variable to receive data from the serial port
String phoneNumber = "";
String pN = "";
char remoteNum1[20];
char remoteNum2[20];

void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  for(byte i=0;i<rows;i++) {
    pinMode(Output[i],OUTPUT);
  }
  
  for(byte s=0;s<columns;s++) {
    pinMode(Input[s],INPUT_PULLUP);
  }

  unlockPhone();

  Serial.println("SMS Messages Sender");

  // connection state
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
  
  // phoneNumber.equals("+34651550473")
  Serial.println("Introduzca el numero de telefono:");
  readSerial(remoteNum1);
  Serial.println("El numero introducido es " + String(remoteNum1));

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

  Serial.println("Saliendo...");
  while (1){}

}

void sendMessage()
{ 
    Serial.println("Introduzca el mensaje:");// send the messag
    
    do { // if data is available to read
        msg = Serial.readString();     // read the message
        Serial.println("Esperando...");
        if (sms.available()){
          Serial.println("Ha recibido algo");
          recvMessage();
        }
    } while (msg.equals(""));
    digitalWrite(A0, HIGH);

    delay(5000);
    Serial.println("Luis: " + msg);
    digitalWrite(A1, HIGH);

    int num = sms.beginSMS(remoteNum1);
    num = sms.print(msg);
    //Serial.println("Devuelve " + String(num) + " bytes");
    sms.endSMS();
    //Serial.println("Mensaje enviado!");
}

void recvMessage()
{
  char c;
  
  //Serial.println("Message received from:");

  // Get remote number
  sms.remoteNumber(remoteNum2, 20);
  //Serial.println(remoteNum2);

  // This is just an example of message disposal    
  // Messages starting with # should be discarded
  if(sms.peek()=='#')
  {
    Serial.println("Discarded SMS");
    sms.flush();
  }

  // Read message bytes and print them
  Serial.println(String(remoteNum2) + ":");
  while(c=sms.read())
    Serial.print(c);

  digitalWrite(A2, HIGH);

  //Serial.println("\nEND OF MESSAGE");

  // delete message from modem memory
  sms.flush();
  //Serial.println("MESSAGE DELETED");
  
}

int readSerial(char result[]) 
{
  int i = 0;
  Serial.println("Introduzca el numero receptor");
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}

// Probar con 3 intentos<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void unlockPhone() 
{
  int iteracion = 0;
  String code;
  String phrase;
  
  Serial.println("Introduzca el codigo de desbloqueo");
  
  do {
    key = getKeyT();       // Recogemos la clave pulsada en el teclado
    
    if (flag) {
      code = code + key;
      Serial.println(code);
      flag = false;
    }

    if (code.length() == 4 && !code.equals("4568")) {
      Serial.println("Contraseña erronea");
      code = "";
    }
  } while(!code.equals("4568"));

  Serial.println("BIENVENIDO!!!!!!!");
}

char getKeyT() 
{
  if(millis()-kdelay>period) {
    kdelay=millis();  //capture time from millis function
    switch (keypad()) {
      
            case 0:
            flag = true;
            return '1';
       break;  
            case 1:
            flag = true;
            return '2';
       break;
            case 2:
            flag = true;
            return '3';
       break;
            case 3:
            flag = true;
            return 'A';
       break;
            case 4:
            flag = true;
            return '4';
       break;
            case 5:
            flag = true;
            return '5';
       break;
            case 6:
            flag = true;
            return '6';
       break;
            case 7:
            flag = true;
            return 'B';
       break;
            case 8:
            flag = true;
            return '7';
       break;
            case 9:
            flag = true;
            return '8';
       break;
            case 10:
            flag = true;
            return '9';
       break;
            case 11:
            flag = true;
            return 'C';
       break;
            case 12:
            flag = true;
            return '*';
       break;
            case 13:
            return '0';
       break;
            case 14:
            flag = true;
            return '#';
       break;
            case 15:
            flag = true;
            return 'D';
       break;
            default:
            flag = false;
    }
  }
}

byte keypad() // function used to detect which button is used 
{
 static bool no_press_flag=0;  //static flag used to ensure no button is pressed 
  for(byte x=0;x<columns;x++) {
    
     if (digitalRead(Input[x])==HIGH);   //read evry input if high continue else break;
     else
      break;
      
     if(x==(columns-1)) {
      no_press_flag=1;
      h=0;
      v=0;
     }
  }
  
  if(no_press_flag==1) {
    
    for(byte r=0;r<rows;r++) //for loop used to make all output as low
      digitalWrite(Output[r],LOW);
      
    for(h=0;h<columns;h++) {
      if(digitalRead(Input[h])==HIGH) //if specific input is remain high (no press on it) continue
        continue;
      else {
          for (v=0;v<rows;v++) {
            digitalWrite(Output[v],HIGH);   //make specified output as HIGH
            
            if(digitalRead(Input[h])==HIGH)  //if the input that selected from first sor loop is change to high
            {
              no_press_flag=0;                //reset the no press flag;
              for(byte w=0;w<rows;w++) // make all outputs as low
              digitalWrite(Output[w],LOW);
              return v*4+h;  //return number of button 
            }
          
          }
      }
    }
  }
  
 return 50;
}
