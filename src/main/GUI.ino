
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
  Serial.println("#   3 -  Configuracion de los tonos de notificacion                                  #");
  Serial.println("#   4 -  Salir                                                                       #");
  Serial.println("#                                                                                    #");
  Serial.println("######################################################################################");

  do{
    do{
      key = getKeyT();
    }while(flag == false);
  
    switch(key) {
      case '1':
        whatsapp_serial_enviar_mensaje();
        break;
      case '2':
        whatsapp_serial_contactos();
        break;
      case '3':
        whatsapp_configurar_tono();
        break;
      case '4':
        terminar_programa();
        break;
      default:
        break;
    }
  }while(key != '1' || key != '2' || key != '3' || key != '4');
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
  Serial.println("#   2 -  Enviar mensaje por un grupo                                                            #");
  Serial.println("#   3 -  Enviar mensaje de difusion                                                             #");
  Serial.println("#   4 -  Volver                                                                                 #");
  Serial.println("#                                                                                               #");
  Serial.println("#################################################################################################");

  do{
    do{
      key = getKeyT();
    }while(flag == false);
    
    switch(key) {
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
  }while(key != '1' || key != '2' || key != '3' || key != '4');
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

  Serial.println("Cargando contactos. Espere por favor...");
  Serial.println("contacts_transfer");
  delay(3000);
  while (Serial.available())
  {
    delay(300);  //delay to allow buffer to fill 
    if (Serial.available() >0)
    {
      while (c = Serial.read())  
        contact += c; 
    }
    
  }
  
  Serial.println(contact);   
  
  do{
    do{
      key = getKeyT();
    }while(flag == false);
    
    switch(key) {
      case '1':
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
  }while(key != '1' || key != '2' || key != '3' || key != '4');
}

void whatsapp_configurar_tono()
{
  char key = 'p';                 // Variable to control the key pressed
  
  whatsapp_serial_limpiar_pantalla_menus();

  Serial.println("=====================================================");
  Serial.println("#  ########  #######  ##    ##  #######   ######    #");
  Serial.println("#     ##    ##     ## ###   ## ##     ## ##    ##   #");
  Serial.println("#     ##    ##     ## ####  ## ##     ## ##         #");
  Serial.println("#     ##    ##     ## ## ## ## ##     ##  ######    #");
  Serial.println("#     ##    ##     ## ##  #### ##     ##       ##   #");
  Serial.println("#     ##    ##     ## ##   ### ##     ## ##    ##   #");
  Serial.println("#     ##     #######  ##    ##  #######   ######    #");
  Serial.println("=====================================================");                                                                 
  Serial.println("#                                                   #");
  Serial.println("#             Lista de tonos dipsonibles            #");
  Serial.println("#                                                   #");
  Serial.println("#####################################################");
  Serial.println("#                                                   #");
  Serial.println("#  Seleccione una opcion por favor                  #");
  Serial.println("#                                                   #");
  Serial.println("#   1 -  Tonos de envio                             #");
  Serial.println("#   2 -  Tonos de recepcion                         #");
  Serial.println("#   3 -  Volver                                     #");
  Serial.println("#                                                   #");
  Serial.println("#####################################################");

  do{
    do{
      key = getKeyT();
    }while(flag == false);
    
    switch(key) {
      case '1':
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
  }while(key != '1' || key != '2' || key != '3' || key != '4');
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
  delay(5000);
  whatsapp_serial_limpiar_pantalla_fin();
  exit(0);
}

// phoneNumber.equals("+34651550473")
//Serial.println("Introduzca el numero de telefono:");
//readSerial(receiver_phoneNumber);
//Serial.println("El numero introducido es " + String(remoteNum1));
