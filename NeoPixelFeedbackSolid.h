#include <Adafruit_NeoPixel.h>

void neoPixelFeedbackSolid(int numberOfPixels, Adafruit_NeoPixel &pixels, uint32_t color)
{
  for(int i=0; i<numberOfPixels; i++) {
    pixels.setPixelColor(i, color);
  }
}
