
void play_ringtone_msg_sent() 
{
  int iTono;
  
  for (iTono = 0; iTono < countTonos; iTono++) {
   tone(pinBuzzer, tonos[iTono]);
   delay(1000);
  }
  
  noTone(pinBuzzer);
}

void play_ringtone_msg_rcv() 
{
  int iTono;
  
  for (iTono = 0; iTono < countTonos; iTono++) {
   tone(pinBuzzer, tonos[iTono]);
   delay(1000);
  }
  
  noTone(pinBuzzer);
}
