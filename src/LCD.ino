
/* Imprime un mensaje en el LCD atendiendo al menú desde el que se imprima y el mensaje que se quiera
 * transmitir
*/
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

    delay(1000);
    lcd.clear();

  } else if (mode.equals("keypad")) { // Keypad
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
    lcd.clear();
    Serial.println("Message introducing writes LCD");
    lcd.setCursor(0,0);
    lcd.print("Introduzca el");

    lcd.setCursor(0,1);
    lcd.print("mensaje a enviar");

  } else if (mode.equals("Received")) {
    //Serial.println("Message received writes LCD");
    
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("**Mensaje recibido**");
    delay(4000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("From:");
    lcd.setCursor(0,1);
    lcd.print(unk_receiver_phoneNumber);
    
    delay(1000);
  }
 }
