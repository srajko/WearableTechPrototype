#include "Sensor.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

class OrientationSensor : public Sensor {
  Adafruit_BNO055 bno;

public:
  OrientationSensor() : Sensor("10001000") {
    if(!WireConnected(40)) {
      return;
    }
  
    initialized = bno.begin();
    if (initialized) {
      delay(1000);

      bno.setExtCrystalUse(true);

      values.resize(3);
    }
  }
  
  void UpdateValues() {
    /* Get a new sensor event */ 
    sensors_event_t event; 
    bno.getEvent(&event);

    // print out orientation data
    values[0] = event.orientation.x;
    values[1] = event.orientation.y;
    values[2] = event.orientation.z;    
  }
};

