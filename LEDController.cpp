#include "LEDController.h"

LEDController::LEDController(uint16_t n, uint8_t p, uint8_t t) : Adafruit_NeoPixel(n, p, t)
{
  this->LEDs = n;
};

void LEDController::ColorWipe(uint32_t c, uint8_t wait)
{
  for (uint16_t i=0; i < this->numPixels(); i++) {
    this->setPixelColor(i, c);
    this->show();
    delay(wait);
  }
}

void LEDController::Rainbow(uint8_t wait)
{
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i < this->numPixels(); i++) {
      this->setPixelColor(i, this->Wheel((i+j) & 255));
    }
    
    this->show();
    delay(wait);
  }
}

void LEDController::RainbowCycle(uint8_t wait)
{
  uint16_t i, j;

  int numPixels = this->numPixels();

  for(j = 0; j < 256*5; j++) {
    for(i = 0; i < numPixels; i++) {
      this->setPixelColor(i, Wheel(((i * 256 / numPixels) + j) & 255));
    }
    
    this->show();
    delay(wait);
  }
}

void LEDController::TheaterChase(uint32_t c, uint8_t wait)
{
  int numPixels = this->numPixels();
  
  for (int j = 0; j < 10; j++) {
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < numPixels; i = i+3) {
        this->setPixelColor(i + q, c);
      }
      this->show();
  
      delay(wait);
  
      for (int i = 0; i < numPixels; i = i+3) {
        this->setPixelColor(i + q, 0);
      }
    }
  }
}

void LEDController::TheaterChaseRainbow(uint8_t wait)
{
  int numPixels = this->numPixels();
  
  for (int j = 0; j < 256; j++) {
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < numPixels; i=i+3) {
        this->setPixelColor(i+q, this->Wheel((i+j) % 255));
      }
      
      this->show();

      delay(wait);

      for (int i=0; i < numPixels; i=i+3) {
        this->setPixelColor(i+q, 0);
      }
    }
  }
}

void LEDController::EffectBreathing(int r, int g, int b, int rounds)
{
  float MaximumBrightness = 255;
  float SpeedFactor = 0.008;
  float StepDelay = 5; 
  
  for (int i = 0; i < 550 * rounds; i++) {
    // Intensity will go from 10 - MaximumBrightness in a "breathing" manner
    float intensity = MaximumBrightness /2.0 * (1.0 + sin(SpeedFactor * i));
    this->setBrightness(intensity);
    // Now set every LED to that color
    // NOTE: To do indivial LED control, checks have to be made!
    for (int ledNumber=0; ledNumber < this->LEDs; ledNumber++) {
      this->setPixelColor(ledNumber, r, g, b);
    }
  
    this->show();
    //Wait a bit before continuing to breathe
    delay(StepDelay);

   }

   this->setBrightness(0);
   this->show();
}

void LEDController::SetPixelsColor(int sectionBegin, int sectionEnd, int r, int g, int b)
{
  int size = sectionEnd - sectionBegin;
  for (int i=0; i < size; i++)
  {
    int currentLED = i + sectionBegin;
    this->setPixelColor(currentLED, r, g, b);
  }

  this->show();
}

uint32_t LEDController::Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
    return this->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return this->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return this->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

