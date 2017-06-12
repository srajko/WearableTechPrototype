#include <Adafruit_NeoPixel.h>

uint8_t offset = 0;

bool pattern[] = {
  true,
  false,
  true,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false,
  false
};

int delayMilliseconds = 200;

void neoPixelFeedbackChase(int numberOfPixels, Adafruit_NeoPixel &pixels, uint32_t color)
{
  for(int i=0; i<numberOfPixels; i++) {
    uint32_t c = 0;

    if(pattern[(offset + i) % numberOfPixels]) {
      c = color;
    }

    pixels.setPixelColor(i, c);
  }
  offset++;
}
