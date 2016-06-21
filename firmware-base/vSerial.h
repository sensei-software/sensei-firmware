// vSerial 0.7

// Serial functions
// -----------------------------

void serialPrint(String firstLine) {
  Serial.println(firstLine);
  Serial.flush();  
  delay(SERIAL_PRINT_DELAY);
}
void serialPrint(String firstLine, String secondLine) {
  Serial.print(firstLine);
  Serial.print(" - ");
  Serial.println(secondLine);
  Serial.flush();  
  delay(SERIAL_PRINT_DELAY);
}
void serialPrint2(String firstLine, String secondLine) {
  Serial.println(firstLine);
  Serial.println(secondLine);
  Serial.flush();
  delay(SERIAL_PRINT_DELAY);
}
void serialClearScreen(){

}
void serialFlushIn(){
  while(Serial.available() > 0) {
    char t = Serial.read();
    delay(1);
  }
} 
void serialFlushOut(){
  Serial.flush();
  delay(10);
} 
void initSerial() {
  Serial.begin(SERIAL_SETTING_BAUDS);
  serialClearScreen();
}


