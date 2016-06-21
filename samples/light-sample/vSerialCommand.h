// vSerialCommand 0.5.0a

// Serial Command Object
SerialCommand sCmd;

// COMMANDS
// ----------------------------------------------------------------
String lastCommand = "";

void serialEvent(){
  
}

char *readCmdArg(char *defaultValue) {
  char *arg;
  arg = sCmd.next();
  if (arg != NULL) 
    return arg;
  else
    return defaultValue;    
}
int readCmdArg(int defaultValue) {
  char *arg;
  arg = sCmd.next();
  if (arg != NULL) 
    return String(arg).toInt();
  else
    return defaultValue;    
}

void promptForCommand() {
  serialFlushIn();
  serialPrint("WAITING CMD...", "> ");
}
void waitForCommand() {
  do {
    delay(10);
  } while (!Serial.available());
  delay(100);
}
void readCommand() {
    sCmd.readSerial();
}
void commandPrompt() {
  do{
    promptForCommand();
    waitForCommand();
    readCommand();  
  } while (lastCommand != "EXT");
  delay(3000);
}

void logCommand(String command, String out) {
  lastCommand = command;
  serialPrint(command + " | " + out);
}
void logCommand(String module, String command, String out, String unit="-", String debug="" ) {
  //serialPrint(command);
  //serialPrint(debug);  
  lastCommand = command;
  //serialPrint( module + " | " + command + " | " + debug + " | "  + unit + " | " + out);
  serialPrint( command + " (" + module + ") [" + debug + "] {"  + unit + "} = " + out);
}

void cmdUnknown(const char *command) {
  logCommand("UNKNOWN CMD", String(command));
}

void cmdHelp(){
   for(int i=0; i< sCmd.commandCount; i++){
      serialPrint(String(i),String(sCmd.commandList[i].command));
   }   
}

void initSerialCommand(){
  sCmd.addCommand("?",    cmdHelp);    
  sCmd.setDefaultHandler(cmdUnknown);
}
