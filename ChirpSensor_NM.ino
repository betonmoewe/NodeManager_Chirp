/*
NodeManager is intended to take care on your behalf of all those common tasks a MySensors node has to accomplish, speeding up the development cycle of your projects.

NodeManager includes the following main components:
- Sleep manager: allows managing automatically the complexity behind battery-powered sensors spending most of their time sleeping
- Power manager: allows powering on your sensors only while the node is awake
- Battery manager: provides common functionalities to read and report the battery level
- Remote configuration: allows configuring remotely the node without the need to have physical access to it
- Built-in personalities: for the most common sensors, provide embedded code so to allow their configuration with a single line 

Documentation available on: https://github.com/mysensors/NodeManager
 */

// load user settings
#include "config_mod.h"
// include supporting libraries
#ifdef MY_GATEWAY_ESP8266
  #include <ESP8266WiFi.h>
#endif
// load MySensors library
#include <MySensors.h>
// load NodeManager library
#include "NodeManager_mod.h"

// define Chrip Sensor Offsets
#define CHIRP_NR 1

#if CHIRP_NR == 1
	#define M_OFFSET 330
	#define M_RANGE 520
#elif CHIRP_NR == 2
	#define M_OFFSET 320
	#define M_RANGE 505	
#else
	#define M_OFFSET 0
	#define M_RANGE 0
#endif


// create a NodeManager instance
NodeManager nodeManager;

// before
void before() {
  // setup the serial port baud rate
  Serial.begin(MY_BAUD_RATE);  

  /*
   * Register below your sensors
  */
  nodeManager.setBatteryMin(1.8);
  nodeManager.setBatteryMax(3.2);
  nodeManager.setSleepMinutes(2);
  nodeManager.setReportIntervalMinutes(2);
  
  //SensorCHIRP* myCHIRP = (SensorCHIRP*)nodeManager.getSensor(nodeManager.registerSensor(SENSOR_CHIRP)); 
  int myCHIRPid = nodeManager.registerSensor(SENSOR_CHIRP);
  SensorCHIRP* myCHIRPmoisture = (SensorCHIRP*)nodeManager.getSensor((myCHIRPid - 2));
  SensorCHIRP* myCHIRPtemperature = (SensorCHIRP*)nodeManager.getSensor((myCHIRPid - 1));
  SensorCHIRP* myCHIRPlight = (SensorCHIRP*)nodeManager.getSensor(myCHIRPid);

  myCHIRPmoisture->setTrackLastValue(true);
  myCHIRPtemperature->setTrackLastValue(true);
  myCHIRPlight->setTrackLastValue(true);  
  myCHIRPmoisture->setForceUpdateMinutes(15);
  myCHIRPtemperature->setForceUpdateMinutes(15);
  myCHIRPlight->setForceUpdateMinutes(15);
    
  myCHIRPmoisture->setMoistureOffset(M_OFFSET);
  myCHIRPmoisture->setMoistureRange(M_RANGE);
  myCHIRPmoisture->setReturnMoistureNormalized(true); 
  myCHIRPmoisture->setReturnLightReversed(true);

  /*
   * Register above your sensors
  */
  nodeManager.before();
}

// presentation
void presentation() {
  // call NodeManager presentation routine
  nodeManager.presentation();
  
}

// setup
void setup() {

  // call NodeManager setup routine
  nodeManager.setup();


}

// loop
void loop() {
  // call NodeManager loop routine
  nodeManager.loop();

}

// receive
void receive(const MyMessage &message) {
  // call NodeManager receive routine
  nodeManager.receive(message);
}

// receiveTime
void receiveTime(unsigned long ts) {
  // call NodeManager receiveTime routine
  nodeManager.receiveTime(ts);
}



