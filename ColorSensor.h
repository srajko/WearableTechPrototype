#include "Sensor.h"
#include "Adafruit_TCS34725.h"

class ColorSensor : public Sensor {
  Adafruit_TCS34725 tcs;

public:
  ColorSensor()
    : Sensor("10000000"), tcs(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X)
  {
    if(!WireConnected(41)) {
      return;
    }
  
    initialized = tcs.begin();
    if (initialized) {
      tcs.setInterrupt(false);      // turn on LED
      values.resize(4);
    }
  }
  
  void UpdateValues() {
    uint16_t clear, red, green, blue;
    
    tcs.getRawData(&red, &green, &blue, &clear);

    values[0] = clear;
    values[1] = red;
    values[2] = green;
    values[3] = blue;
  }
};

