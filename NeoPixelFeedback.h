#include "NeoPixelFeedbackChase.h"
#include "NeoPixelFeedbackRandom.h"
#include "NeoPixelFeedbackSolid.h"

void (*neoPixelFeedback)(int, Adafruit_NeoPixel &, uint32_t) = neoPixelFeedbackSolid;
