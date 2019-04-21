void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Ojala se borre la pantalla despues de 2s");
  delay(2000);
  Serial.print("[2J");
  delay(2000);
}
