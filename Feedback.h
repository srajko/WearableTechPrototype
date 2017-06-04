#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(5, 0);
Adafruit_NeoPixel motors = Adafruit_NeoPixel(3, 15);

void feedbackSetup() {
  pixels.begin();
  pixels.setBrightness(85);
  motors.begin();
  motors.setBrightness(255);
}

float mapAndConstrain(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
  return constrain(map(value, fromLow, fromHigh, toLow, toHigh), toLow, toHigh);
}

typedef void (*feedbackFunction) (const std::vector<float> &data, float &red, float &green, float &blue, float &motor);

void feedbackNineDof(const std::vector<float> &data, float &red, float &green, float &blue, float &motor) {
  red = data[6];
  green = data[7];
  blue = data[8];

  motor = data[0];
}

void feedbackLight(const std::vector<float> &data, float &red, float &green, float &blue, float &motor) {
  float lightIntensity = data[0];

  motor = red = green = blue = mapAndConstrain(lightIntensity, 0, 1000, 0, 255);
}

void feedbackColor(const std::vector<float> &data, float &red, float &green, float &blue, float &motor) {
  red = mapAndConstrain(data[1], 2000, 10000, 0, 255);
  green = mapAndConstrain(data[2], 2000, 10000, 0, 255);
  blue = mapAndConstrain(data[3], 2000, 10000, 0, 255);
}

void feedbackMicAnalog(const std::vector<float> &data, float &red, float &green, float &blue, float &motor) {
  float frequency = data[2];
  float volume = data[1];

  if(frequency > 0.14 && volume > 400) { red = 255; } else { red = 0; }
  blue = volume;
  green = frequency * 255;

  motor = volume;
}



void runFeedback(const std::vector<float> &data, feedbackFunction f) {
  float red, green, blue, motor;

  f(data, red, green, blue, motor);

  for(int i=0; i<5; i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }
  
  for(int i=0; i<3; i++) {
    motors.setPixelColor(i, motors.Color(motor, motor, motor));
  }

  pixels.show();
  motors.show();
}


