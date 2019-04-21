/* ============================= TECLADO DE MEMBRANA ============================= */

byte h=0,v=0;    //variables used in for loops
const unsigned long period=50;  //little period used to prevent error
unsigned long kdelay=0;        // variable used in non-blocking delay 
char key = 'p';
bool flag = false;
const byte rows=4;               //number of rows of keypad
const byte columns=4;            //number of columnss of keypad
const byte Output[rows]={25,27,29,31};      //array of pins used as output for rows of keypad
const byte Input[columns]={33,35,37,39}; //array of pins used as input for columnss of keypad



void setup() {
  Serial.begin(9600);
}

void loop() {
  whatsapp_serial_menu();

}

void whatsapp_serial_menu()
{
  Serial.println("=========================================================================");
  Serial.println("  db   d8b   db db   db  .d8b.  d888888b .d8888.  .d8b.  d8888b. d8888b. ");
  Serial.println("  88   I8I   88 88   88 d8' `8b `~~88~~' 88'  YP d8' `8b 88  `8D 88  `8D ");
  Serial.println("  88   I8I   88 88ooo88 88ooo88    88    `8bo.   88ooo88 88oodD' 88oodD' ");
  Serial.println("  Y8   I8I   88 88~~~88 88~~~88    88      `Y8b. 88~~~88 88~~~   88~~~   ");
  Serial.println("`  8b d8'8b d8' 88   88 88   88    88    db   8D 88   88 88      88      ");
  Serial.println(" `  8b8' `8d8'  YP   YP YP   YP    YP    `8888Y' YP   YP 88      88      ");
  Serial.println("=========================================================================");                                                                 
  Serial.println("#                                                                       #");
  Serial.println("#                     Whattsapp  GSM  Service App                       #");
  Serial.println("#                                                                       #");
  Serial.println("#########################################################################");
  Serial.println("#                                                                       #");
  Serial.println("#  Seleccione una opcion por favor:                                     #");
  Serial.println("#                                                                       #");
  Serial.println("#   1 -  Enviar mensaje                                                 #");
  Serial.println("#   2 -  Lista de contactos                                             #");
  Serial.println("#   3 -  Llamda de Whatsapp                                             #");
  Serial.println("#   4 -  Salir                                                          #");
  Serial.println("#                                                                       #");
  Serial.println("#########################################################################");


  char key = getKeyT();
  switch(key) {
    case '1':
      break;
    case '2':
      break;
    case '3':
      break;
    case '4':
      break;
    default:
      break;
  }
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
      //lcd.print(key);
      
      code = code + key;
      Serial.println(code);
      flag = false;
    }

    if (code.length() == 4 && !code.equals("4568")) {
      delay(1000);
      
      Serial.println("Contraseña erronea");
      code = "";
    }
  } while(!code.equals("4568"));

  delay(1000);
  
  Serial.println("BIENVENIDO!!!!!!!");
}

  // phoneNumber.equals("+34651550473")
  //Serial.println("Introduzca el numero de telefono:");
  //readSerial(receiver_phoneNumber);
  //Serial.println("El numero introducido es " + String(remoteNum1));
