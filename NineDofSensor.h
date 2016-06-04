#include "Sensor.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>

class NineDofSensor : public Sensor {
  Adafruit_LSM9DS0 lsm;

public:
  NineDofSensor() : Sensor("11111100") {
    if(!WireConnected(29)) {
      return;
    }
  
    initialized = lsm.begin();
    if (initialized) {
      /* Setup the sensor gain and integration time */
      // 1.) Set the accelerometer range
      lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
      // 2.) Set the magnetometer sensitivity
      lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
      // 3.) Setup the gyroscope
      lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);

      values.resize(9);
    }
  }
  
  void UpdateValues() {
    sensor_t accelSensor, magSensor, gyroSensor, tempSensor;
  
    lsm.getSensor(&accelSensor, &magSensor, &gyroSensor, &tempSensor);
  
    /* Get a new sensor event */ 
    sensors_event_t accel, mag, gyro, temp;
    lsm.getEvent(&accel, &mag, &gyro, &temp); 

    // print out accelleration data
    values[0] = accel.acceleration.x;
    values[1] = accel.acceleration.y;
    values[2] = accel.acceleration.z;
    
     // print out magnetic data
    values[3] = mag.magnetic.x;
    values[4] = mag.magnetic.y;
    values[5] = mag.magnetic.z;
    
    // print out gyroscope data
    values[6] = gyro.gyro.x;
    values[7] = gyro.gyro.y;
    values[8] = gyro.gyro.z;
  }
};


