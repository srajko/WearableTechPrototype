#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(5, 0);
Adafruit_NeoPixel motors = Adafruit_NeoPixel(3, 15);

void feedbackSetup() {
  pixels.begin();
  pixels.setBrightness(85);
  motors.begin();
  motors.setBrightness(255);
}

void feedback(const std::vector<float> &data) {
  float forLED = data[2];
  float forMotors = data[1];

  float forLEDNormalized = forLED * 255;
  float forMotorsNormalized = forMotors;

  for(int i=0; i<5; i++) {
    pixels.setPixelColor(i, pixels.Color(forLEDNormalized, forLEDNormalized, forLEDNormalized));
  }

  for(int i=0; i<3; i++) {
    motors.setPixelColor(i, motors.Color(forMotorsNormalized, forMotorsNormalized, forMotorsNormalized));
  }

  pixels.show();
  motors.show();
}


