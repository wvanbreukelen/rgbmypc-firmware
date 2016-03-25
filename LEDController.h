#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include "Adafruit_NeoPixel.h"
#include <stdint.h>


class LEDController : public Adafruit_NeoPixel
{
  
  public:
    LEDController(uint16_t n, uint8_t p=6, uint8_t t=NEO_GRB + NEO_KHZ800);

    String Test(String name);
    
    void EffectBreathing(int r, int g, int b, int rounds = 3);
    void SetPixelsColor(int sectionBegin, int sectionEnd, int r, int g, int b);
    void ColorWipe(uint32_t c, uint8_t wait);
    void Rainbow(uint8_t wait);
    void RainbowCycle(uint8_t wait);
    void TheaterChase(uint32_t c, uint8_t wait);
    void TheaterChaseRainbow(uint8_t wait);
    
    
  private:
    int LEDs;

    uint32_t Wheel(byte WheelPos);
    
};

#endif
