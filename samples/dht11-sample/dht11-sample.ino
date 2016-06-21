// SenseiFirmware 0.7

// DEVICE CONFIG
	#define DEVICE_NAME      "WeatherStation"
	#define DEVICE_MODEL     "SenseiGeneric"
	#define FIRMWARE_NAME    "SenseiBase"
	#define FIRMWARE_VERSION "0.7"
	#define LOOP_DELAY       100

// CORE MODULES
	// Serial
    #define SERIAL_PRINT_DELAY 1
    #define SERIAL_SETTING_BAUDS 9600 
  	#include "serialcommand.h"
  	#include <Wire.h>
  	#include "vSerial.h"
  	#include "vSerialCommand.h"
	// EEPROM
  	#include <EEPROM.h>
  	#include <Arduino.h>  // for type definitions
  	#include "EEPROMAnything.h"
	// Reset Counter
  	#define RESET_COUNTER_EEPROM_ADDRESS 100
	// Sensei
  	#include "vSensei.h"
	// Common
  	#include "vCommon.h"

// EXTRA MODULES
  // DHT
    #define DHT11PIN 7  // pin attached to DHT11
    #include "dht11.h"
    #include "vDHT11.h"
  // Speaker
    #include "pitches.h"
    #define DEFAULT_NOTE          NOTE_E5
    #define DEFAULT_BEEP_DURATION 250
    #define SPKR_PIN              12
    #include "vSpeaker.h"

  
// SETUP
	void setup() {
	  // INIT CORE
  	  initSerial();
  	  initSerialCommand();  
  	  serialCommand(); 
	  // INIT MODULES
      initDHT();       
      initSpeaker();       
  
    // Ready  
	    welcomeMsg();
	}
// LOOP
	void loop() {
	  Serial.flush();
	  readCommand();
	  delay(LOOP_DELAY);
	}

// SERIAL
	void cmdGet(){  
	  // GET COMMANDS
        cmdGetDHT(); 
	}
	void cmdDump(){
	  while(!Serial.available()){
	     cmdGet(); 
	     delay(LOOP_DELAY);
	  }
	}
	void serialCommand() {
	  // SERIAL MODULES
      serialDHT();       
      serialSpeaker();       

    // SERIAL CORE
  	  sCmd.addCommand("GET",    cmdGet);  
  	  sCmd.addCommand("DUMP",    cmdDump);    
	}
