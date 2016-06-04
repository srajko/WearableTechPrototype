#include "Sensor.h"
#include <Adafruit_TSL2561_U.h>

class LightSensor : public Sensor {
  Adafruit_TSL2561_Unified tsl;

public:
  LightSensor()
    : Sensor("11001100"), tsl(TSL2561_ADDR_FLOAT, 12345)
  {
    if(!WireConnected(57)) {
      return;
    }
  
    initialized = tsl.begin();
    if (initialized) {
      /* You can also manually set the gain or enable auto-gain support */
      // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
      // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
      tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
      
      /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
      tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
      // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
      // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

      values.resize(1);
    }
  }
  
  void UpdateValues() {
    /* Get a new sensor event */ 
    sensors_event_t event;
    tsl.getEvent(&event);

    values[0] = event.light;
  }
};


