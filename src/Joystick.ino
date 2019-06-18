/* Devuelve una letra W, A, S, D u O dependiendo de la dirección de movimiento leida del joystick 
 * OJO --> Las lecturas han de ser calibradas ya que para cada joystick son diferentes los valores leidos
 * correspondientes a cada dirección (arriba, abajo, izquierda y derecha)
*/
 char getJoystickDirection()
 {
  bool pulsador = false;
  int sensorX = analogRead(pinEjeX); // Lee del pin A0, conectado al eje de las X del joystick
  int sensorY = analogRead(pinEjeY); // Lee del pin A0, conectado al eje de las Y del joystick
  pulsador = digitalRead(pinPulsador); // Lee del pin digital 9, conectado al pulsador del joystick

  if(sensorX == 2 && sensorY == 0) { // Arriba
    return 'W';
  } else if(sensorX >= 5 && sensorX <= 7 && sensorY >= 300) { // Abajo
    return 'S';
  } else if(sensorX == 0 && sensorY == 2) { // Izquierda
    return 'A';
  } else if (sensorX >= 300 && sensorY == 5){ // Derecha
    return 'D';
  } 

  if(!pulsador) { // Centro del joystick presionado
    pulsador = false;
    return 'O';
  } 

  return 'T'; // En caso de que no se pulse ninguna tecla, para mantener la lógica del código

}


/* Función que imprime un menú distinto en el LCD atendiendo a los textos que se incluyan en el 
 * array 'menus' y a la posición actual de la flecha en el LCD
*/
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
    limit2 = 5;
   } else if (pos_actual == 5) {
    // Sin flecha
    lcd.setCursor(0, 0);
    lcd.print(menus[3]);

    // Con flecha
    lcd.setCursor(0, 1);
    lcd.write (byte (5));
    lcd.setCursor(1, 1);
    lcd.print(menus[4]);
   }

}

/* Función que mueve la linea del LCD si el texto es demasiado grande
 * y no se puede leer
*/
void move_line_lcd(int pos_actual, String menus[])
{
  int string_length = menus[pos_actual].length();
  int i = 0;
  int stringStart, stringStop = 0;
  int scrollCursor = 1;
  
  while(i < string_length) {
      if (pos_actual%2 == 0)
        lcd.setCursor(0, 0);
        lcd.print(menus[pos_actual-1]);
      
      lcd.setCursor(scrollCursor, 1);
      lcd.print(menus[pos_actual].substring(stringStart,stringStop));
      
      delay(400);
      
      lcd.clear();
      
      if(stringStart == 0 && scrollCursor > 0){
        scrollCursor--;
        stringStop++;
      } else if (stringStart == stringStop){
        stringStart = stringStop = 0;
        scrollCursor = 16;
      } else if (stringStop == menus[pos_actual].length() && scrollCursor == 0) {
        stringStart++;
      } else {
        stringStart++;
        stringStop++;
      }
      
    }
}
