void test_LCD() /* DEBUG */
{
  

  // set cursor position to start of first line on the LCD
  lcd.setCursor(0,0);
  //text to print
  lcd.print("   16x2 LCD");
  // set cusor position to start of next line
  lcd.setCursor(0,1);
  lcd.print("   DISPLAY");
}

void print_msg_LCD(char mode)
{
  if ('s' == mode) { // Sender
    lcd.setCursor(0,12);
    lcd.print(remoteNum1); // From 12 -> 15
    
    lcd.setCursor(1,0);
    lcd.print(msg_send);
    
    delay(1000);
    lcd.clear();
    
  } else if ('r' == mode) { // Receiver
    lcd.setCursor(0,0);
    lcd.print(remoteNum2); 

    lcd.setCursor(1,0);
    lcd.print(msg_recv);

    delay(1000);
    lcd.clear();
    
  } else if ('k' == mode) { // Keypad
    lcd.setCursor(0,0);
    lcd.print("Introducir clave"); 

    lcd.setCursor(1,9);
    
  } else if ('n' == mode) { // Telephone Numbers
    lcd.setCursor(1,15);
    lcd.print("<");
    lcd.setCursor(1,4);
    lcd.print(remoteNum2); 
    
  } else if ('i' == mode) { // Introduce message
    lcd.setCursor(0,0);
    lcd.print("Introduzca el");

    lcd.setCursor(1,0);
    lcd.print("mensaje a enviar");
    
  } else if ('m' == mode) {
    lcd.setCursor(0,0);
    lcd.print("Mensaje recibido");

    delay(500);
    lcd.clear();
  }
}
