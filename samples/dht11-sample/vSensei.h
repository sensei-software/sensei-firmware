// vSensei 0.5.0a

int reset_counter = 0;


void welcomeMsg(){
  serialPrint("# Sensei ready. Welcome!", "Init N: " + String(reset_counter));
  serialPrint("# ROM: " + String(FIRMWARE_NAME), "VER: " + String(FIRMWARE_VERSION));
  serialPrint("# DEV: " + String(DEVICE_MODEL), "SID: " + String(DEVICE_NAME));
  Serial.flush();  
}

void resetCount() {
  EEPROM_readAnything(RESET_COUNTER_EEPROM_ADDRESS, reset_counter);  
  reset_counter++;
  EEPROM_writeAnything(RESET_COUNTER_EEPROM_ADDRESS, reset_counter);
}

void serialSensei() {
   sCmd.addCommand("WLC_MSG",    welcomeMsg);     
}
