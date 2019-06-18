
void whatsapp_serial_menu()
{ 
  lcd.print("Cargando..."); 
  char key = 'p';                 // Variable to control the key pressed

  /* Variables del LCD y Joystick */
  int actual = 0;
  int flag_enter = 0;
  char mov;
  String menu1[3] = {"1- Enviar mensaje", "2- Lista de contactos", "3- Salir"};
  limit = 2;
  
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
 
 lcd.clear();

 // Primer apartado del menú inicialmente con flecha
 lcd.setCursor(0, 0); 
 lcd.write (byte (5));
 lcd.setCursor(1, 0);
 lcd.print(menu1[0]);

 // Segundo apartado inicialmente sin flecha
 lcd.setCursor(0, 1); 
 lcd.print(menu1[1]);

 // Bucle de acción del joystick
 while(!flag_enter){
    delay(100);
    mov = getJoystickDirection();
    
    switch(mov){
      case 'W': // Se ha pulsado hacia arriba el joystick
        if (actual >= 1){
          if (actual > 1) actual--; // actual = 2,3
          getMenu(actual, menu1);
        } 
        break;
      case 'S': // Se ha pulsado hacia abajo el joystick
        if (actual <= limit){
          if (actual < limit) actual++; // actual = 1,2
          getMenu(actual, menu1);
        }
        break;
      case 'O': // Se ha presionado el centro del joystick
        flag_enter = 1;
        break;
      default:
        break;
   }
 }

  // En caso de que el usuario pulse la primera opción
  // el valor de la variable actual se mantendrá a 0 por lo que
  // eso análogo a que hubiera pulsado la opción 2
  if (actual == 0) actual = 1;

  switch(actual) {
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cargando..."); 
      whatsapp_serial_enviar_mensaje();
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cargando..."); 
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

  /* Variables del LCD y Joystick */
  int actual = 0;
  int flag_enter = 0;
  char mov;
  String menu2[2] = {"1- Enviar mensaje por privado", "2- Volver"};
  
  limit = 2;

  // Limpiamos el menú en el prompt
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
    
    switch(mov){
      case 'W':
        if (actual >= 1){
          if (actual > 1) actual--; // actual = 2,3
          getMenu(actual, menu2);
        } 
        break;
      case 'S':
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
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cargando..."); 
      start_communication();
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cargando..."); 
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
  int i = 0;

  int actual = 0;
  int flag_enter = 0;
  char mov;
  String menu3[5] = {"1- Añadir", "2- Eliminar", "3- Modificar", "4- Ver contactos", "5- Volver"};
  String list_contacts[5];
  limit2 = 2;
  
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

  /* Manda la orden al codigo Python a través de puerto serie para cargar los contactos */
  Serial.println("contacts_transfer"); 
  
  // Anadimos un cierto delay tanto fuera como dentro del bucle
  delay(3000); // Para el llenado del buffer
  
  while(!Serial.available()) {}
        
  while (Serial.available()) {
    delay(300);  //delay to allow buffer to fill 
    if (Serial.available() >0)
    {
      char c = Serial.read();  // Lee un byte del puerto serie
      if (c == '\n') {
        Serial.println("#            " + contact + "                                                     #");
        list_contacts[i] = contact;
        i++;
        contact = "";
      } else {
        contact += c; //makes the string readString
      }
    }
  }
  
  Serial.println("##########################################################################################");
 
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
    
   switch(mov){
      case 'W':
        if (actual >= 1){
          if (actual > 1) actual--; // actual = 2,3
          getMenu(actual, menu3);
        } 
        break;
      case 'S':
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
    case 1:
     /* Manda la orden al codigo Python a través de puerto serie para añadir un contacto */
      Serial.println("contacts_add");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Creando contacto ..."); 
      break;
    case 2:
    /* Manda la orden al codigo Python a través de puerto serie para eliminar un contacto */
      Serial.println("contacts_delete");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Eliminando contacto ..."); 
      break;
    case 3:
     /* Manda la orden al codigo Python a través de puerto serie para modificar un contacto */
      Serial.println("contacts_modify");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Modificando contacto ..."); 
      break;
    case 4:
      /* Manda la orden al codigo Python a través de puerto serie para mostrar los contactos */
      whatsapp_mostrar_contactos(list_contacts, i);
      break;
    case 5:
      whatsapp_volver_menu();
      break;
    default:
      break;
  }

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Pulse arriba para volver");

  // Si quiere salir de alguno de las opciones de la lista de contactos tiene que pulsar arriba
  // con el joystick
  mov = 'T';
  while(mov != 'W'){
    delay(100);
    mov = getJoystickDirection();
 }
 
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("Volviendo");
 delay(400);

}

void whatsapp_mostrar_contactos(String list_contacts[], int count)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cargando..."); 
  limit2 = 2;
 int actual = 0;
 int flag_enter = 0;
 char mov;
 list_contacts[count] = "Volver";

 lcd.clear();
 
 lcd.setCursor(0, 0); 
 lcd.write (byte (5));
 lcd.setCursor(1, 0);
 lcd.print(list_contacts[0]);
 
 lcd.setCursor(0, 1); 
 lcd.print(list_contacts[1]);

 while(!flag_enter){
    delay(100);
    mov = getJoystickDirection();
    
   switch(mov){
      case 'W':
        if (actual >= 1){
          if (actual > 1) actual--; 
          getMenu(actual, list_contacts);
        } 
        break;
      case 'S':
        if (actual <= limit2){
          if (actual < limit2) actual++; 
          getMenu(actual, list_contacts);
        }
        break;
      case 'O':
        flag_enter = 1;
        break;
      default:
        break;
   }
 }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cargando...");
 // Cuando se rompa el bucle, se vuelve al menú de contactos al presionar el joystick    
}

/* Funciones que añaden saltos en la pantalla del prompt para limpiar la pantalla
 * del puerto serie y hacer más legibles y claros los distintos menús
*/

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
  lcd.print("Cargando..."); 
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
