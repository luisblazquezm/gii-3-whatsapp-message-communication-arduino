void playNote(int noteInt, double noteFreqArr[], int noteDurationArr[], long breath = 20) 
{
  noteDurationArr[noteInt] = noteDurationArr[noteInt] - breath;
  buzz(pinBuzzer, noteFreqArr[noteInt], noteDurationArr[noteInt]);
  if(breath > 0) { //take a short pause or 'breath' if specified
    delay(breath);
  }
}

void play_tone(String mode)
{
  int i;
  int countTonesSend = 511;
  int countTonesRecv = 0;
  
  double noteFreqArrSendStartup[] = {  /* StartUp */
    165.4064, 130.813, 261.626, 523.251, 1046.50, 2093.00, 4186.01
  };
  
  double noteFreqArrSendMario[] = {  /* Mario victory */
    466, 588, 699, 933, 933, 933, 933, 1047
  };
  
  double noteFreqArrSendShutDown[] = {  /* ShutDown --> Delay es 100*/
   523.251, 391.995, 329.628, 261.626
  };
  
  int noteDurationArrSendStartup[] = { /* Startup */
    100, 100, 100, 100, 100, 100, 100
  };
  
  int noteDurationArrSendShutdown[] = { /* ShutDown */
   100, 100, 100, 200
  };
  
  int noteDurationArrSendMario[] = { /* Mario Victory */
     100, 100, 100, 300, 100, 100, 100, 400
  };
  int countTonesSendStartup = 7;
  int countTonesSendShutDown = 4;
  int countTonesSendMario = 8;
  const int pinBuzzer = 8;

  Serial.println("Playing tone in mode " + mode);

  if (mode.equals("startup")) {
    Serial.println("Sonido de enviar");
    for (i = 0 ; i < countTonesSendStartup ; i++)
      playNote(i, noteFreqArrSendStartup, noteDurationArrSendStartup);
  } else if (mode.equals("recv")) {
    for (i = 0 ; i < countTonesSendMario ; i++)
      playNote(i, noteFreqArrSendMario, noteDurationArrSendMario);
  } else if (mode.equals("shutdown")) {
    for (i = 0 ; i < countTonesSendShutDown ; i++)
      playNote(i, noteFreqArrSendShutDown, noteDurationArrSendShutdown);
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
