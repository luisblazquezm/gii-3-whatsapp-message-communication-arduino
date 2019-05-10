
void whatsapp_serial_menu()
{ 
  char key = 'p';                 // Variable to control the key pressed
  
  Serial.println("======================================================================================");
  Serial.println("#   ##      ## ##     ##    ###    ########  ######     ###    ########  ########    #");
  Serial.println("#   ##  ##  ## ##     ##   ## ##      ##    ##    ##   ## ##   ##     ## ##     ##   #");
  Serial.println("#   ##  ##  ## ##     ##  ##   ##     ##    ##        ##   ##  ##     ## ##     ##   #");
  Serial.println("#   ##  ##  ## ######### ##     ##    ##     ######  ##     ## ########  ########    #");
  Serial.println("#   ##  ##  ## ##     ## #########    ##          ## ######### ##        ##          #");
  Serial.println("#   ##  ##  ## ##     ## ##     ##    ##    ##    ## ##     ## ##        ##          #");
  Serial.println("#    ###  ###  ##     ## ##     ##    ##     ######  ##     ## ##        ##          #");               
  Serial.println("======================================================================================");                                                                 
  Serial.println("#                                                                                    #");
  Serial.println("#                               Servicio de Whattsapp                                #");
  Serial.println("#                                                                                    #");
  Serial.println("######################################################################################");
  Serial.println("#                                                                                    #");
  Serial.println("#  Seleccione una opcion por favor                                                   #");
  Serial.println("#                                                                                    #");
  Serial.println("#   1 -  Enviar mensaje                                                              #");
  Serial.println("#   2 -  Lista de contactos                                                          #");
  Serial.println("#   3 -  Salir                                                                       #");
  Serial.println("#                                                                                    #");
  Serial.println("######################################################################################");
 
 int actual = 0;
 int flag_enter = 0;
 char mov;
 String menu1[3] = {"1- Enviar mensaje", "2- Lista de contactos", "3- Salir"};

 lcd.clear();
 
 lcd.setCursor(0, 0); 
 lcd.write (byte (5));
 lcd.setCursor(1, 0);
 lcd.print(menu1[0]);
 
 lcd.setCursor(0, 1); 
 lcd.print(menu1[1]);

 while(!flag_enter){
    delay(100);
    mov = getJoystickDirection();
    //Serial.println(mov); 
   //Serial.println("Actual =>>> "+ String(mov));
   switch(mov){
      case 'W':
        //Serial.println("Actual W: "+ String(actual));
        if (actual >= 1){
          if (actual > 1) actual--; // actual = 2,3
          getMenu(actual, menu1);
        } 
        break;
      case 'S':
        //Serial.println("Actual S: "+ String(actual));
        if (actual <= limit){
          if (actual < limit) actual++; // actual = 1,2
          getMenu(actual, menu1);
        }
        break;
      case 'O':
        flag_enter = 1;
        break;
      default:
        break;
   }
 }

 if (actual == 0) actual = 1;

    switch(actual) {
      case 1:
        whatsapp_serial_enviar_mensaje();
        break;
      case 2:
        whatsapp_serial_contactos();
        break;
      case 3:
        terminar_programa();
        break;
      default:
        break;
    }
  
}

void whatsapp_serial_enviar_mensaje()
{
  char key = 'p';                 // Variable to control the key pressed
  
  whatsapp_serial_limpiar_pantalla_menus();

  Serial.println("=================================================================================================");
  Serial.println("#   ##     ## ######## ##    ##  ######     ###          ## ######## ########  ####    ###      #");
  Serial.println("#   ###   ### ##       ###   ## ##    ##   ## ##         ## ##       ##     ##  ##    ## ##     #");
  Serial.println("#   #### #### ##       ####  ## ##        ##   ##        ## ##       ##     ##  ##   ##   ##    #");
  Serial.println("#   ## ### ## ######   ## ## ##  ######  ##     ##       ## ######   ########   ##  ##     ##   #");
  Serial.println("#   ##     ## ##       ##  ####       ## ######### ##    ## ##       ##   ##    ##  #########   #");
  Serial.println("#   ##     ## ##       ##   ### ##    ## ##     ## ##    ## ##       ##    ##   ##  ##     ##   #");
  Serial.println("#   ##     ## ######## ##    ##  ######  ##     ##  ######  ######## ##     ## #### ##     ##   #");
  Serial.println("=================================================================================================");                                                                 
  Serial.println("#                                                                                               #");
  Serial.println("#                             Servicio de mensajeria de WhatsApp                                #");
  Serial.println("#                                                                                               #");
  Serial.println("#################################################################################################");
  Serial.println("#                                                                                               #");
  Serial.println("#  Seleccione una opcion por favor                                                              #");
  Serial.println("#                                                                                               #");
  Serial.println("#   1 -  Enviar mensaje por privado                                                             #");
  Serial.println("#   2 -  Volver                                                                                 #");
  Serial.println("#                                                                                               #");
  Serial.println("#################################################################################################");

 int actual = 0;
 int flag_enter = 0;
 char mov;
 String menu2[2] = {"1- Enviar mensaje por privado", "2- Volver"};

 limit = 2;

 lcd.clear();
 
 lcd.setCursor(0, 0); 
 lcd.write (byte (5));
 lcd.setCursor(1, 0);
 lcd.print(menu2[0]);
 
 lcd.setCursor(0, 1); 
 lcd.print(menu2[1]);

 while(!flag_enter){
    delay(100);
    mov = getJoystickDirection();
    //Serial.println(mov); 
   //Serial.println("Actual =>>> "+ String(mov));
   switch(mov){
      case 'W':
        //Serial.println("Actual W: "+ String(actual));
        if (actual >= 1){
          if (actual > 1) actual--; // actual = 2,3
          getMenu(actual, menu2);
        } 
        break;
      case 'S':
        //Serial.println("Actual S: "+ String(actual));
        if (actual <= 2){
          if (actual < 2) actual++; // actual = 1,2
          getMenu(actual, menu2);
        }
        break;
      case 'O':
        flag_enter = 1;
        break;
      default:
        break;
   }
 }

 if (actual == 0) actual = 1;
 
    switch(actual) {
      case '1':
        start_communication();
        break;
      case '2':
        break;
      case '3':
        break;
      case '4':
        whatsapp_volver_menu();
        break;
      default:
        break;
    }
  
}

void whatsapp_serial_contactos()
{
  char key = 'p';                 // Variable to control the key pressed
  String contact = "";
  char c;
  
  whatsapp_serial_limpiar_pantalla_menus();

  Serial.println("==========================================================================================");
  Serial.println("#   ######   #######  ##    ## ########    ###     ######  ########  #######   ######    #");
  Serial.println("#  ##    ## ##     ## ###   ##    ##      ## ##   ##    ##    ##    ##     ## ##    ##   #");
  Serial.println("#  ##       ##     ## ####  ##    ##     ##   ##  ##          ##    ##     ## ##         #");
  Serial.println("#  ##       ##     ## ## ## ##    ##    ##     ## ##          ##    ##     ##  ######    #");
  Serial.println("#  ##       ##     ## ##  ####    ##    ######### ##          ##    ##     ##       ##   #");
  Serial.println("#  ##    ## ##     ## ##   ###    ##    ##     ## ##    ##    ##    ##     ## ##    ##   #");
  Serial.println("#   ######   #######  ##    ##    ##    ##     ##  ######     ##     #######   ######    #");
  Serial.println("==========================================================================================");                                                                 
  Serial.println("#                                                                                        #");
  Serial.println("#                                  Lista de contactos                                    #");
  Serial.println("#                                                                                        #");
  Serial.println("##########################################################################################");
  Serial.println("#                                                                                        #");
  Serial.println("#  Seleccione una opcion por favor                                                       #");
  Serial.println("#                                                                                        #");
  Serial.println("#   1 -  Añadir                                                                          #");
  Serial.println("#   2 -  Eliminar                                                                        #");
  Serial.println("#   3 -  Modificar                                                                       #");
  Serial.println("#   4 -  Volver                                                                          #");
  Serial.println("#                                                                                        #");
  Serial.println("##########################################################################################");

  Serial.println("#                    Cargando lista de contactos, espere por favor...                    #");
  Serial.println("#                                                                                        #");
  Serial.println("##########################################################################################");
  Serial.println("#            NOMBRE        TELEFONO                                                      #");
  Serial.println("##########################################################################################");
  Serial.println("contacts_transfer");
  delay(3000);
  while(!Serial.available()) {}
        
  while (Serial.available()) {
    delay(300);  //delay to allow buffer to fill 
    if (Serial.available() >0)
    {
      char c = Serial.read();  //gets one byte from serial buffer
      if (c == '\n') {
        Serial.println("#            " + contact + "                                                     #");
        contact = "";
      } else {
        contact += c; //makes the string readString
      }
    }
  }
  
  
  Serial.println("##########################################################################################");

 int actual = 0;
 int flag_enter = 0;
 char mov;
 String menu3[4] = {"1- Añadir", "2- Eliminar", "3- Modificar", "4- Volver"};

 lcd.clear();
 
 lcd.setCursor(0, 0); 
 lcd.write (byte (5));
 lcd.setCursor(1, 0);
 lcd.print(menu3[0]);
 
 lcd.setCursor(0, 1); 
 lcd.print(menu3[1]);

 while(!flag_enter){
    delay(100);
    mov = getJoystickDirection();
    //Serial.println(mov); 
   //Serial.println("Actual =>>> "+ String(mov));
   switch(mov){
      case 'W':
        //Serial.println("Actual W: "+ String(actual));
        if (actual >= 1){
          if (actual > 1) actual--; // actual = 2,3
          getMenu(actual, menu3);
        } 
        break;
      case 'S':
        //Serial.println("Actual S: "+ String(actual));
        if (actual <= limit2){
          if (actual < limit2) actual++; // actual = 1,2
          getMenu(actual, menu3);
        }
        break;
      case 'O':
        flag_enter = 1;
        break;
      default:
        break;
   }
 }

 if (actual == 0) actual = 1;
    
    switch(actual) {
      case '1':
        Serial.println("contacts_add");
        break;
      case '2':
        Serial.println("contacts_delete");
        break;
      case '3':
        Serial.println("contacts_modify");
        break;
      case '4':
        whatsapp_volver_menu();
        break;
      default:
        break;
    }
  
}

void whatsapp_volver_menu(){
  whatsapp_serial_limpiar_pantalla_menus();

  whatsapp_serial_menu();
}

void whatsapp_serial_limpiar_pantalla_menus(){
  int numLineasEliminar = 0;
  while(numLineasEliminar < 30){
    Serial.println(" ");
    numLineasEliminar++;
  }
}


void whatsapp_serial_limpiar_pantalla_inicio(){
  int numLineasEliminar = 0;
  while(numLineasEliminar < 70){
    Serial.println(" ");
    numLineasEliminar++;
  }
}

void whatsapp_serial_limpiar_pantalla_fin(){
  int numLineasEliminar = 0;
  while(numLineasEliminar < 110){
    Serial.println(" ");
    numLineasEliminar++;
  }
}

void terminar_programa(){
  whatsapp_serial_limpiar_pantalla_inicio();
  Serial.println("  =======================================================================================");
  Serial.println("                                      Terminando...                                      ");
  Serial.println("  =======================================================================================");

  lcd.clear();
  lcd.print("Saliendo...");
  delay(5000);
  
  whatsapp_serial_limpiar_pantalla_fin();
  
  Serial.println("terminate");
  play_tone("shutdown");
  delay(8000);
  exit(0);
}

// phoneNumber.equals("+34651550473")
//Serial.println("Introduzca el numero de telefono:");
//readSerial(receiver_phoneNumber);
//Serial.println("El numero introducido es " + String(remoteNum1));
