#ifndef COMMANDS_H
#define COMMANDS_H

#include "Adafruit_NeoPixel.h"
#include "LEDController.h"


class Commands
{
  public:
    
    void RunCommand(String exptInput, String givenInput);
    
    void Status();
    void Version();
    void Reset();
    void Off();
    void StaticColor();
    void Brightness();
    void Breathing();

    LEDController* GetCont();
    

  protected:
    LEDController* controller;
  
    void SetController(LEDController* c);
};

#endif


