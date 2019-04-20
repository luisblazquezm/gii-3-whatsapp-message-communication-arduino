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
  print_msg_LCD(3);
  
  do {
    key = getKeyT();       // Recogemos la clave pulsada en el teclado
    
    if (flag) {
      //lcd.print(key);
      
      code = code + key;
      Serial.println(code);
      flag = false;
    }

    if (code.length() == 4 && !code.equals("4568")) {
      lcd.clear();
      lcd.print("Clave erronea");
      delay(1000);
      lcd.clear();
      print_msg_LCD(3);
      
      Serial.println("Contraseña erronea");
      code = "";
    }
  } while(!code.equals("4568"));

  lcd.clear();
  lcd.print("Accediendo...");
  delay(1000);
  lcd.clear();
  
  Serial.println("BIENVENIDO!!!!!!!");
}
