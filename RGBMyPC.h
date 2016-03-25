#ifndef RGBMYPC_H
#define RGBMYPC_H

#include "LEDController.h"

class RGBMyPC
{
  public:
    LEDController* controller;
  
    //RGBMyPC(LEDController* strip, String version);
    
    //LEDController* cont = this->GetCont();
    //LEDController* GetCont();
    
    String ReadSerial(bool force = false);
    String* AskInput(int times = 3);
    bool SerialReceived();
    long ConvertToRGB(const char hexstring[], char i);

  private:

  protected:
  
};

#endif

