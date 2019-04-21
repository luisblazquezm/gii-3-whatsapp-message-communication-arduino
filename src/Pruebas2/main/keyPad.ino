
/* Captures the key pressed in the keypad from the pin detected by the code */
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

/* Function used to detect which button is used. No need using Keypad.h */
byte keypad() 
{
    static bool no_press_flag=0;  // Static flag used to ensure no button is pressed 
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
  int iteracion = 0;
  String code;
  String phrase;
  
  Serial.println("Introduzca el codigo de desbloqueo");
  //print_msg_LCD(3);/* LCD */
  
  do {
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
      
      Serial.println("Contraseña erronea");
      code = "";
    }
  } while(!code.equals(mobile_code));

  //lcd.clear();/* LCD */
  //lcd.print("Accediendo...");/* LCD */
  delay(1000);
  //lcd.clear();/* LCD */
  
  Serial.println("BIENVENIDO!!!!!!!");
}
