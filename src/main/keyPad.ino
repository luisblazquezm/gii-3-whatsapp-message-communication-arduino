
/* Captures the key pressed in the keypad from the pin detected by the code */
char getKeyT() 
{
  const unsigned long period=50;  // Little period used to prevent error
  if(millis()-kdelay>period) {
    kdelay=millis();  //capture time from millis function
    switch (keypad()) {
      
            case 0:
              flag = true;
              return '1';
 
            case 1:
              flag = true;
              return '2';

            case 2:
              flag = true;
              return '3';

            case 3:
              flag = true;
              return 'A';

            case 4:
              flag = true;
              return '4';

            case 5:
              flag = true;
              return '5';

            case 6:
              flag = true;
              return '6';

            case 7:
              flag = true;
              return 'B';

            case 8:
              flag = true;
              return '7';

            case 9:
              flag = true;
              return '8';

            case 10:
              flag = true;
              return '9';
              
            case 11:
              flag = true;
              return 'C';

            case 12:
              flag = true;
              return '*';

            case 13:
              flag = true;
              return '0';

            case 14:
              flag = true;
              return '#';

            case 15:
              flag = true;
              return 'D';
              
            default:
              flag = false;
    }
  }
}

/* Function used to detect which button is used. No need using Keypad.h */
byte keypad() 
{
    static bool no_press_flag=0;  // Static flag used to ensure no button is pressed 
    byte h=0,v=0;                   // Variables used in for loops
      
    for(byte x=0;x<columns;x++) {
      
       if (digitalRead(Input[x])==HIGH);   // Read evry input if high continue else break;
       else
        break;
        
       if(x==(columns-1)) {
        no_press_flag=1;
        h=0;
        v=0;
       }
    }
    
    if(no_press_flag==1) {
      
      for(byte r=0;r<rows;r++) // For loop used to make all output as low
        digitalWrite(Output[r],LOW);
        
      for(h=0;h<columns;h++) {
        if(digitalRead(Input[h])==HIGH) { // If specific input is remain high (no press on it) continue
          continue;
        } else {
            for (v=0;v<rows;v++) {
              digitalWrite(Output[v],HIGH);   // Make specified output as HIGH
              
              //If the input that selected from first sor loop is change to high
              if(digitalRead(Input[h])==HIGH) {
                no_press_flag=0;                // Reset the no press flag;
                for(byte w=0;w<rows;w++)        // Make all outputs as low
                  digitalWrite(Output[w],LOW);
                  
                return v*4+h;  //return number of button 
              }
            } // End of loop
        }
      } // End of loop
    } // End of if
    
   return 50;
}

// Probar con 3 intentos<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/* Function to make look like we are unlocking a phone to access to Whatsapp service */
void unlockPhone() 
{
  char key = 'p';                 // Variable to control the key pressed
  int iteracion = 0;
  String code;
  String phrase;
  int intentos = 0;
  String mobile_code = "4568";     // Code to unlock the program using the keypad

  Serial.println("Introduzca el codigo de desbloqueo");
  //print_msg_LCD(3);/* LCD */
  
  do {
    if(intentos == 3){
      terminar_programa();
    }
    
    key = getKeyT();       // Recogemos la clave pulsada en el teclado
    
    if (flag) {
      //lcd.print(key);/* LCD */
      
      code = code + key;
      Serial.println(code);
      flag = false;
    }

    if (code.length() == 4 && !code.equals(mobile_code)) {
      //lcd.clear();/* LCD */
      //lcd.print("Clave erronea");/* LCD */
      delay(1000);
      //lcd.clear();/* LCD */
      //print_msg_LCD(3);/* LCD */
      
      Serial.println("Contraseña erronea, introduzcala de nuevo");
      intentos++;
      code = "";
    }
  } while(!code.equals(mobile_code));

  //lcd.clear();/* LCD */
  //lcd.print("Accediendo...");/* LCD */
  delay(1000);
  //lcd.clear();/* LCD */
  
  whatsapp_serial_limpiar_pantalla_inicio();
    
  Serial.println("  ########  #### ######## ##    ## ##     ## ######## ##    ## #### ########   #######   ");
  Serial.println("  ##     ##  ##  ##       ###   ## ##     ## ##       ###   ##  ##  ##     ## ##     ##  ");
  Serial.println("  ##     ##  ##  ##       ####  ## ##     ## ##       ####  ##  ##  ##     ## ##     ##  ");
  Serial.println("  ########   ##  ######   ## ## ## ##     ## ######   ## ## ##  ##  ##     ## ##     ##  ");
  Serial.println("  ##     ##  ##  ##       ##  ####  ##   ##  ##       ##  ####  ##  ##     ## ##     ##  ");
  Serial.println("  ##     ##  ##  ##       ##   ###   ## ##   ##       ##   ###  ##  ##     ## ##     ##  ");
  Serial.println("  ########  #### ######## ##    ##    ###    ######## ##    ## #### ########   #######   ");
  
}
