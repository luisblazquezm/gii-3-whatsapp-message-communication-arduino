
/*
void moveRight(){
  if (cursorPos == 3){
    lcd.setCursor(6, 1);
    cursorPos = 0;
  } else {
    int a = cursorPos + 7;
    lcd.setCursor(a, 1);
    cursorPos = cursorPos + 1;
  }
}

void moveLeft(){
  if (cursorPos == 0){
    lcd.setCursor(9, 1);
    cursorPos = 3;
  } else {
    int b = cursorPos + 5;
    lcd.setCursor(b, 1);
    cursorPos = cursorPos - 1;
  }
}

void increase(int cursorPos){
  if (dig[cursorPos] == 9){
    dig[cursorPos] = 0;
  } else {
    dig[cursorPos] = dig[cursorPos] + 1;
  }
  int c = cursorPos + 6;
  lcd.setCursor(c, 1);
  lcd.print(dig[cursorPos]);
  lcd.setCursor(c, 1);
}

void decrease(int cursorPos){
  if (dig[cursorPos] == 0){
    dig[cursorPos] = 9;
  } else {
    dig[cursorPos] = dig[cursorPos] - 1;
  }
  int c = cursorPos + 6;
  lcd.setCursor(c, 1);
  lcd.print(dig[cursorPos]);
  lcd.setCursor(c, 1);
}
//change this part for your own passcode
*/

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

void print_msg_LCD(String mode, String msg)
{
  if (mode.equals("msg_send")) { // Sender
    Serial.println("Sender writes LCD");
    lcd.setCursor(15,0);
    lcd.print("<");
    lcd.setCursor(13,0);
    lcd.print("Yo"); 
    
    lcd.setCursor(0,1);
    lcd.print(msg);

    delay(4000);
    lcd.clear();

  } else if (mode.equals("msg_recv")) { // Receiver
    Serial.println("Receiver writes LCD");
    lcd.setCursor(0,0);
    lcd.print(">");
    lcd.setCursor(1,0);
    lcd.print(receiver_phoneNumber); 
    lcd.print(":");
    
    lcd.setCursor(0,1);
    lcd.print(msg);

    delay(4000);
    lcd.clear();

  } else if (mode.equals("keypad")) { // Keypad
    Serial.println("Keypad writes LCD");
    lcd.setCursor(0,0);
    lcd.print("Introducir clave"); 

    lcd.setCursor(1,9);

  } else if (mode.equals("Telephone_numbers")) { // Telephone Numbers
    Serial.println("Telephone Numbers write LCD");
    lcd.setCursor(15,0);
    lcd.print("<");
    lcd.setCursor(1,4);
    lcd.setCursor(4,1);
    lcd.print(receiver_phoneNumber); 

  } else if (mode.equals("Introduce_message")) { // Introduce message
    Serial.println("Message introducing writes LCD");
    lcd.setCursor(0,0);
    lcd.print("Introduzca el");

    lcd.setCursor(0,1);
    lcd.print("mensaje a enviar");

  } else if (mode.equals("Received")) {
    Serial.println("Message received writes LCD");
    
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("**Mensaje recibido**");
    delay(4000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("From:");
    lcd.setCursor(0,1);
    if(strcmp(unk_receiver_phoneNumber, receiver_phoneNumber) == 0) {
      lcd.print(receiver_phoneNumber);
    } else {
      lcd.print(unk_receiver_phoneNumber);
    }
    
    delay(4000);
  }
 }

 char getJoystickDirection()
 {
  //lcd.setCursor(0, 0);
  bool pulsador = false;
  int sensorX = analogRead(A0); //get readings for x,y-axis movement
  int sensorY = analogRead(A1);
  pulsador = digitalRead(kPin);
  Serial.println("Pulsador:" + String(pulsador));
    /*
  float angleX = sensorX * (180.0 / 1023.0); //convert value to angle
  float angleY = sensorY * (180.0 / 1023.0);
  if (angleX > 100) {
  moveRight();
  delay(500);
  } else if ( angleX < 70) {
  moveLeft();
  delay(500);
  } else {
  if (angleY > 105){
  decrease(cursorPos);
  delay(250);
  } else if(angleY < 75) {
  increase(cursorPos);
  delay(250); 
  }
  */
  //Serial.println("SensorX: " + String(sensorX));
  //Serial.println("SensorY: " + String(sensorY));

  if(sensorX == 2 && sensorY == 0){
    //Serial.println("Arriba");
    return 'W';
  } else if(sensorX >= 5 && sensorX <= 7 && sensorY >= 500) {
    //Serial.println("Abajo");
    return 'S';
  } else if(sensorX == 0 && sensorY == 2) {
    //Serial.println("Izquierda");
    return 'A';
  } else if (sensorX >= 300 && sensorY == 5){
    //Serial.println("Derecha");
    return 'D';
  } 

  if(!pulsador) {
    //Serial.println("Centro");
    pulsador = false;
    return 'O';
  } 

  return 'T';

}

void getMenu(int pos_actual, String menus[])
{
   if (pos_actual <= 0)
    return;
    
   lcd.clear();

   // Menu de la primera fila
   if (pos_actual == 1) {
    // Con flecha
    lcd.setCursor(0, 0);
    lcd.write (byte (5));
    lcd.setCursor(1, 0);
    lcd.print(menus[0]);

    // Sin flecha
    lcd.setCursor(0, 1);
    lcd.print(menus[1]); 
   } else if (pos_actual == 2) {
    // Sin flecha
    lcd.setCursor(0, 0);
    lcd.print(menus[0]);

    // Con flecha
    lcd.setCursor(0, 1);
    lcd.write (byte (5));
    lcd.setCursor(1, 1);
    lcd.print(menus[1]);

    limit = 3;
    limit2 = 3;
   } else if (pos_actual == 3) {
    // Sin flecha
    lcd.setCursor(0, 0);
    lcd.print(menus[1]);

    // Con flecha
    lcd.setCursor(0, 1);
    lcd.write (byte (5));
    lcd.setCursor(1, 1);
    lcd.print(menus[2]);
    limit2 = 4;
   } else if (pos_actual == 4) {
    // Sin flecha
    lcd.setCursor(0, 0);
    lcd.print(menus[2]);

    // Con flecha
    lcd.setCursor(0, 1);
    lcd.write (byte (5));
    lcd.setCursor(1, 1);
    lcd.print(menus[3]);
   }

}
