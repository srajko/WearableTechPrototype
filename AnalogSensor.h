#include "Sensor.h"

class AnalogSensor : public Sensor {

public:
  AnalogSensor()
    : Sensor("111111111")
  {
    initialized = true;
    values.resize(1);
  }
  
  void UpdateValues() {
    values[0] = analogRead(A0);
  }
};

