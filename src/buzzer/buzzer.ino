
//double noteFreqArrSend[] = {  /* StartUp */
 // 165.4064, 130.813, 261.626, 523.251, 1046.50, 2093.00, 4186.01
//};

//double noteFreqArrSend[] = {  /* ShutDown --> Delay es 100*/
 //523.251, 391.995, 329.628, 261.626
//};

//double noteFreqArrSend[] = {  /* Mario victory */
//   466, 588, 699, 933, 933, 933, 933, 1047
//};

//double noteFreqArrSend[] = {  /* Jingle bells */
//   392, 262, 311, 349, 392, 262/*, 311, 349, 392, 262, 311, 349, 392, 262, 311 */
//};

double noteFreqArrSend[] = {  /* Tetris */
  330, 1, 494, 1, 660, 1, 590, 660, 494, 494, 523, 1, 440, 1, 494, 1, 392, 392, 440, 370, 1, 392
};

double noteFreqArrRecv[] = {  /* Mario victory */
49.4, 52.3, 55.4, 58.7, 62.2, 65.9, 69.9, 74, 78.4, 83.1, 88, 93.2,
98.8, 105, 111, 117, 124, 132, 140, 148, 157, 166, 176, 186,
198, 209, 222, 235, 249, 264, 279, 296, 314, 332, 352, 373,
395, 419, 444, 470, 498, 527, 559, 592, 627, 665, 704, 746,
790, 837, 887, 940, 996, 1050, 1110, 1180, 1250, 1320, 1400, 1490,
1580, 1670, 1770, 1870, 1990, 2100};

//int noteDurationArrSend[] = { /* Startup */
 // 100, 100, 100, 100, 100, 100, 100
//};

//int noteDurationArrSend[] = { /* ShutDown */
 //100, 100, 100, 200
//};

//int noteDurationArrSend[] = { /* Mario Victory */
//   100, 100, 100, 300, 100, 100, 100, 400
//};

//int noteDurationArrSend[] = { /*Jingle bell */
//   500 ,500, 250, 250, 500, 500/*, 250, 250, 500, 500, 250, 250, 500, 500, 250*/
//};

int noteDurationArrSend[] = { /*Tetris */
  150, 40, 159, 40, 150, 49, 150, 150, 100, 100, 150, 40, 150, 40, 150, 40, 100, 100, 150, 150, 40, 150
};

int noteDurationArrRecv[] = { 
  250
};

int countTonesSend = 22;
int countTonesRecv = 0;
const int pinBuzzer = 8;
 
void setup() {
  Serial.begin(9600);
  pinMode(pinBuzzer, OUTPUT); // set a pin for buzzer output
}
 
void loop() {
  //main course
  Serial.println("Tocala otra vez sam");
  /*
  playNote(24,500);
 
  playNote(17,1000);
  playNote(19,250);
  playNote(22,250);
  playNote(21,250);
  playNote(19,250);
  playNote(24,500);
  playNote(24,500);
  playNote(24,250);
  playNote(26,250);
  playNote(21,250);
  playNote(22,250);
  playNote(19,500);
  playNote(19,500);
  playNote(19,250);
  playNote(22,250);
  playNote(21,250);
  playNote(19,250);
  playNote(17,250);
  playNote(29,250);
  playNote(28,250);
  playNote(26,250);
  playNote(24,250);
  playNote(22,250);
  playNote(21,250);
  playNote(19,250);
 
  playNote(17,1000);
  playNote(19,250);
  playNote(22,250);
  playNote(21,250);
  playNote(19,250);
  playNote(24,500);
  playNote(24,500);
  playNote(24,250);
  playNote(26,250);
  playNote(21,250);
  playNote(22,250);
  playNote(19,500);
  playNote(19,500);
  playNote(19,250);
  playNote(22,250);
  playNote(21,250);
  playNote(19,250);
  playNote(17,250);
  playNote(24,250);
  playNote(19,250);
  playNote(21,250);
  playNote(17,250);
  */
  play_tone("send");
  while(1) {}
}
 
void playNote(int noteInt, double noteFreqArr[], int noteDurationArr[], long breath = 20) 
{
  noteDurationArr[noteInt] = noteDurationArr[noteInt] - breath;
  buzz(pinBuzzer, noteFreqArr[noteInt], noteDurationArr[noteInt]);
  if(breath > 0) { //take a short pause or 'breath' if specified
    delay(50);
  }
}

void play_tone(String mode)
{
  Serial.println("Playing tone in mode " + mode);
  int i;

  if (mode.equals("send")) {
    for (i = 0 ; i < countTonesSend ; i++) {
      Serial.println("Sonido de enviar");
      playNote(i, noteFreqArrSend, noteDurationArrSend);
    }
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
