void playNote(int noteInt, double noteFreqArr[], int noteDurationArr[], long breath = 20) 
{
  noteDurationArr[0] = noteDurationArr[0] - breath;
  buzz(pinBuzzer, noteFreqArr[noteInt], noteDurationArr[0]);
  if(breath > 0) { //take a short pause or 'breath' if specified
    delay(breath);
  }
}

void play_tone(String mode)
{
  Serial.println("Playing tone in mode " + mode);
  int i;

  if (mode.equals("send")) {
    Serial.println("Sonido de enviar");
    for (i = 0 ; i < countTonesSend ; i++)
      playNote(i, noteFreqArrSend, noteDurationArrSend);
  } else if (mode.equals("recv")) {
    for (i = 0 ; i < countTonesRecv ; i++)
      playNote(i, noteFreqArrRecv, noteDurationArrRecv);
  }
  
  
}

void buzz(int targetPin, long frequency, long length) 
{
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // Calculate the number of cycles for proper timing
  
  //// Multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // For the calculated length of time...
    digitalWrite(targetPin,HIGH);     // Write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue);    // Wait for the calculated delay value
    digitalWrite(targetPin,LOW);      // Write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue);    // Wait again for the calculated delay value
  }
}
