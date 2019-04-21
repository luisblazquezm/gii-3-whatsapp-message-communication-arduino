void setup() {
  // put your setup code here, to run once:

}

void loop() {
  Serial.println("Se borra pantalla despues de 2s");
  delay(2000);
  Serial.print("[2J");
  delay(2000);
}
