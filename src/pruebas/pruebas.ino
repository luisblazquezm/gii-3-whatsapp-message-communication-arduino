void setup() {
  Serial.begin(9600);
}

void loop() {
  whatsapp_serial_menu();

}

void whatsapp_serial_menu()
{
  Serial.println("=========================================================================");
  Serial.println("  db   d8b   db db   db  .d8b.  d888888b .d8888.  .d8b.  d8888b. d8888b. ");
  Serial.println("  88   I8I   88 88   88 d8' `8b `~~88~~' 88'  YP d8' `8b 88  `8D 88  `8D ");
  Serial.println("  88   I8I   88 88ooo88 88ooo88    88    `8bo.   88ooo88 88oodD' 88oodD' ");
  Serial.println("  Y8   I8I   88 88~~~88 88~~~88    88      `Y8b. 88~~~88 88~~~   88~~~   ");
  Serial.println("`  8b d8'8b d8' 88   88 88   88    88    db   8D 88   88 88      88      ");
  Serial.println(" `  8b8' `8d8'  YP   YP YP   YP    YP    `8888Y' YP   YP 88      88      ");
  Serial.println("=========================================================================");                                                                 
  Serial.println("#                                                                       #");
  Serial.println("#                     Whattsapp  GSM  Service App                       #");
  Serial.println("#                                                                       #");
  Serial.println("#########################################################################");
  Serial.println("#                                                                       #");
  Serial.println("#  Seleccione una opcion por favor:                                     #");
  Serial.println("#                                                                       #");
  Serial.println("#   1 -  Enviar mensaje                                                 #");
  Serial.println("#   2 -  Lista de contactos                                             #");
  Serial.println("#   3 -  Llamda de Whatsapp                                             #");
  Serial.println("#   4 -  Salir                                                          #");
  Serial.println("#                                                                       #");
  Serial.println("#########################################################################");


  char key = getKeyT();
  switch(key) {
    case '1':
      break;
    case '2':
      break;
    case '3':
      break;
    case '4':
      break;
    default:
      break;
  }
}

  // phoneNumber.equals("+34651550473")
  //Serial.println("Introduzca el numero de telefono:");
  //readSerial(receiver_phoneNumber);
  //Serial.println("El numero introducido es " + String(remoteNum1));
