#include <Adafruit_NeoPixel.h>

const int numberOfPixels = 24;
const int numberOfMotors = 3;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numberOfPixels, 0);
Adafruit_NeoPixel motors = Adafruit_NeoPixel(numberOfMotors, 15);

const float pi = 3.14159265358979;

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
  red = mapAndConstrain(data[0], -10, 10, 0, 255);
  green = mapAndConstrain(data[1], -10, 10, 0, 255);
  blue = mapAndConstrain(data[2], -10, 10, 0, 255);

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

  float intensity = mapAndConstrain(volume, 0, 1024, 0, 255);
  float hue = constrain(frequency, 0, 1);

  red = intensity*fabs(sin(hue*pi));
  green = intensity*fabs(sin((hue + 0.333)*pi));
  blue = intensity*fabs(sin((hue + 0.666)*pi));

  motor = volume;
}



void runFeedback(const std::vector<float> &data, feedbackFunction f) {
  float red, green, blue, motor;

  f(data, red, green, blue, motor);

  for(int i=0; i<numberOfPixels; i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }

  for(int i=0; i<numberOfMotors; i++) {
    motors.setPixelColor(i, motors.Color(motor, motor, motor));
  }

  pixels.show();
  motors.show();
}
