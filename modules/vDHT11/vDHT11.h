// SenseiFirmware 0.5.0a

dht11 DHT11;

void readDHT(){
  int chk = DHT11.read(DHT11PIN);
  switch (chk)
  {
    case DHTLIB_OK: 
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		serialPrint("DHT11","Checksum ERROR"); 
                delay(1000);return;
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		serialPrint("DHT11","Time out ERROR"); 
                delay(1000);return;
		break;
    default: 
		serialPrint("DHT11","Unknown ERROR"); 
                delay(1000);return;
		break;
  }
  
  logCommand("DHT11","TEMPERATURE",String((float)DHT11.temperature, 2),"C");
  logCommand("DHT11","HUMIDITY",String((float)DHT11.humidity, 1),"%");
  logCommand("DHT11","DEW_POINT",String((float)dewPoint(DHT11.temperature, DHT11.humidity),2),"C");  
  
 }
 
void initDHT(){
  serialPrint("# DHTLIB", "VER: " + String(DHT11LIB_VERSION));
}

void cmdGetDHT(){
   readDHT();
}

void serialDHT(){
  sCmd.addCommand("GET_DHT", cmdGetDHT);
}
