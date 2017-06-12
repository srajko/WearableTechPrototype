#include <Adafruit_NeoPixel.h>

void neoPixelFeedbackRandom(int numberOfPixels, Adafruit_NeoPixel &pixels, uint32_t color)
{
  // PLACE #1: Define new color variables here
  int onPixels[] = {
    random(numberOfPixels),
    random(numberOfPixels)
  };

  int numberOfOnPixels = sizeof(onPixels) / sizeof(int);

  for(int i=0; i<numberOfPixels; i++) {
    uint32_t c = 0;

    for (int j=0; j<numberOfOnPixels; j++) {
      if (onPixels[j] == i) {
        c = color;
      }
    }

    pixels.setPixelColor(i, c);
  }
}
// ******************************************************************************************************
