// vLS1 0.1.0a

int LS1_V1=-1; 

int LSAvg=-1;
int LSPerc=-1;

float readLS1(){
  
 LS1_V1=analogSample(LS1_P1,3,10); 
 
 LSAvg=LS1_V1;
 
 LSPerc=map(LSAvg,0,1023,0,100);
 
 return LSPerc;
 
}

void initLS1(){
 return; 
}



// Serial Commands
// ----------------------

void cmdGetLight(){
  float light=readLS1();
  logCommand("LS1","LIGHT",String(light,2),"%", String(LS1_P1) );
}

void cmdGetRawLight(){
  float light=readLS1();
  logCommand("LS1","#RAW_LIGHT",String(LS1_V1) ,"%", String(LS1_P1) );
}
void cmdDumpRaw(){
  while(!Serial.available()){
     cmdGetRawLight(); 
     delay(LOOP_DELAY);
  }
}

void serialLS1(){
  sCmd.addCommand("GET_LIGHT",    cmdGetLight);  
  sCmd.addCommand("GET_RAW",    cmdGetRawLight);    
  sCmd.addCommand("DUMP_RAW",    cmdDumpRaw);       
}
