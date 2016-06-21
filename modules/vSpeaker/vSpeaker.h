// vSpeaker 0.5.0a

void speakerPlay(int note, int duration, int pause){  
    int noteDuration = 1000/duration;
    tone(SPKR_PIN, note,noteDuration);
    int pauseBetweenNotes = noteDuration + pause;
    delay(pauseBetweenNotes);
    noTone(SPKR_PIN);
}

void speakerTest() {
  // MELODY
  // notes in the melody:
  int melody[] = { NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = { 4, 8, 8, 4,4,4,4,4 };
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    speakerPlay(melody[thisNote],noteDurations[thisNote],noteDurations[thisNote]*1.3);
  }
}

void speakerAlarm() {
  for (int i = 0; i < 4; i++) {
    speakerPlay(NOTE_B2,2,0);
     speakerPlay(NOTE_B4,2,0);
  }
  delay(100);
   speakerPlay(NOTE_B4,1,0);
}

void beep(){
  tone(SPKR_PIN, DEFAULT_NOTE, DEFAULT_BEEP_DURATION);
  delay(DEFAULT_BEEP_DURATION);
  noTone(SPKR_PIN);
}

// Init
// ----------------------
void initSpeaker(){
  pinMode(SPKR_PIN,OUTPUT);
  beep();
}

// Serial Commands
// ----------------------
void cmdSpkTst(){
  speakerTest();
  logCommand("SPK_TEST","OK");  
}
void cmdSpkBeep(){
  beep();
  logCommand("SPK_BEEP","OK");  
}
void cmdSpkAlarm(){
  speakerAlarm();
  logCommand("SPK_ALARM","OK");  
}
void cmdSpkPlay(){
  int note=readCmdArg(DEFAULT_NOTE);
  int duration=readCmdArg(1);  
  int pause=readCmdArg(200);
  speakerPlay(note,duration,pause);
  logCommand("SPK","SPK_PLAY","OK","-", String(note) + " " + String(duration) + " " + String(pause) );  
}

void serialSpeaker(){
  sCmd.addCommand("SPK_TEST",    cmdSpkTst);
  sCmd.addCommand("SPK_BEEP",    cmdSpkBeep);
  sCmd.addCommand("SPK_ALARM",    cmdSpkAlarm); 
  sCmd.addCommand("SPK_PLAY",    cmdSpkPlay);   
}
