#ifndef SENSOR_H
#define SENSOR_H

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <vector>

class Sensor {
protected:
  bool initialized;
  std::vector<float> values;
  char *message;

  bool WireConnected(int address) {
    Wire.begin();
    if(address) {
      Wire.beginTransmission(address);
      return Wire.endTransmission() == 0;
    }
    
    for(int address = 1; address < 127; address++ )
    {
      Wire.beginTransmission(address);
      int error = Wire.endTransmission();
      if (error == 0) {
        Serial.println("Address");
        Serial.println(address);
        return true;
      }
    }
    return false;
  }

 public:
  Sensor(char *message) {
    initialized = false;
    this->message = message;
  }
  bool Initialized() {
    return initialized;
  }
  virtual void UpdateValues()=0;
  const char *Message() {
    return message;
  }
  const std::vector<float> &Values() {
    return values;
  }
};

#endif
