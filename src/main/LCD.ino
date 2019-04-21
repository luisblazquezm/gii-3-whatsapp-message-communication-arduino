/*
void test_LCD() 
{
  

  // set cursor position to start of first line on the LCD
  lcd.setCursor(0,0);
  //text to print
  lcd.print("   16x2 LCD");
  // set cusor position to start of next line
  lcd.setCursor(0,1);
  lcd.print("   DISPLAY");
}

void print_msg_LCD(int mode)
{
  Serial.println("LCD message");
  if (1 == mode) { // Sender
    Serial.println("Sender writes LCD");
    lcd.setCursor(12,0);
    lcd.print(remoteNum1); // From 12 -> 15
    
    lcd.setCursor(0,1);
    lcd.print(msg_send);
    
    delay(1000);
    lcd.clear();
    
  } else if (2 == mode) { // Receiver
    Serial.println("Receiver writes LCD");
    lcd.setCursor(0,0);
    lcd.print(remoteNum2); 

    lcd.setCursor(0,1);
    lcd.print(msg_recv);

    delay(1000);
    lcd.clear();
    
  } else if (3 == mode) { // Keypad
    Serial.println("Keypad writes LCD");
    lcd.setCursor(0,0);
    lcd.print("Introducir clave"); 

    lcd.setCursor(1,9);
    
  } else if (4 == mode) { // Telephone Numbers
    Serial.println("Telephone Numbers write LCD");
    lcd.setCursor(15,1);
    lcd.print("<");
    lcd.setCursor(4,1);
    lcd.print(remoteNum2); 
    
  } else if (5 == mode) { // Introduce message
    Serial.println("Message introducing writes LCD");
    lcd.setCursor(0,0);
    lcd.print("Introduzca el");

    lcd.setCursor(0,1);
    lcd.print("mensaje a enviar");
    
  } else if (6 == mode) {
    Serial.println("Message received writes LCD");
    lcd.setCursor(0,0);
    lcd.print("Mensaje recibido");

    delay(500);
    lcd.clear();
  }
}
*/
