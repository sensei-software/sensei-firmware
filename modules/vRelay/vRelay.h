// vRelay 0.5.0a

int _nRelay=0;

void relaySaveStatus(){
  //serialPrint("EEPROM","SAVING");
  EEPROM_writeAnything(RELAY_EEPROM_ADDRESS, RELAY_STATUS);
}

void initRelayStatus(){
  serialPrint("EEPROM","RESETTING");
  _nRelay=sizeof(RELAY_PINS)/sizeof(int);
  for(int i=0; i<_nRelay; i++){    
    RELAY_STATUS[i]=0;
  }  
  relaySaveStatus();
}

void relayOn(int relayN){
  int relayPin=RELAY_PINS[relayN-1];
  digitalWrite(relayPin,LOW);
  //analogWrite(relayPin,0);
  RELAY_STATUS[relayN-1]=1;
  relaySaveStatus();
}
void relayOff(int relayN){
  int relayPin=RELAY_PINS[relayN-1];  
  digitalWrite(relayPin,HIGH);
  //analogWrite(relayPin,1023);
  RELAY_STATUS[relayN-1]=0;
  relaySaveStatus();
}
int relayStatus(int relayN){
  return RELAY_STATUS[relayN-1];
}
void relaySwitch(int relayN){
  if(RELAY_STATUS[relayN-1]){
     relayOn(relayN);
  }else{
     relayOff(relayN);
  }
}

void refreshRelay(){
  for(int i=0; i<_nRelay; i++){    
    int relPin=RELAY_PINS[i];
    int relStatus=RELAY_STATUS[i];
    digitalWrite(relPin,!relStatus);    
  }
}
// Init
// ----------------------
void initRelay(){
  serialPrint("EEPROM LOADING","ADDR: "+ String(RELAY_EEPROM_ADDRESS));
  EEPROM_readAnything(RELAY_EEPROM_ADDRESS, RELAY_STATUS);
  
  if(RELAY_STATUS[0] > 1){
    initRelayStatus();
  }

  _nRelay=sizeof(RELAY_PINS)/sizeof(int);
  for(int i=0; i<_nRelay; i++){    
    int relPin=RELAY_PINS[i];
    pinMode(relPin,OUTPUT);
  }
  refreshRelay();
  
}


// Serial Commands
// ----------------------
void cmdRel(String cmd, int relayN){
  if(!relayN){
    for(int i=0; i<sizeof(RELAY_PINS)/sizeof(int); i++){
      relayN=i+1;
      cmdRel(cmd,relayN);
    }
    return;
  }
  if (relayN>sizeof(RELAY_PINS)/sizeof(int)){
    logCommand("R"+ String(relayN),"REL_"+cmd, "-1", "!" , String(RELAY_PINS[relayN-1])); 
  } 
  else {
    if(cmd=="ON")
      relayOn(relayN);        

    if(cmd=="OFF")
      relayOff(relayN);        
      logCommand("R"+ String(relayN),"REL_"+cmd, String(relayStatus(relayN)), "/", String(RELAY_PINS[relayN-1])); 
  }
}
void cmdRelOn(){
  int relayN=String(readCmdArg("0")).toInt();
  cmdRel("ON",relayN);
}
void cmdRelOff(){
  int relayN=String(readCmdArg("0")).toInt();
  cmdRel("OFF",relayN);
}
void cmdRelStatus(){
  int relayN=String(readCmdArg("0")).toInt();
  cmdRel("STATUS",relayN);
}
void cmdRelStatusReset(){
  logCommand("REL","REL_RESET","OK");  
  initRelayStatus();
  initRelay();
}

void serialRel(){
  sCmd.addCommand("REL_ON",    cmdRelOn);
  sCmd.addCommand("REL_OFF",    cmdRelOff);
  sCmd.addCommand("REL_STATUS",    cmdRelStatus);  
  sCmd.addCommand("REL_RESET",    cmdRelStatusReset);     
}
