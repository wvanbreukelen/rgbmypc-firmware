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

    // EEPROM
    static bool WriteEEPROM(int address, int data, bool overwrite = false);
    static int ReadEEPROM(int address);
    static bool UnsetEEPROM(int address);
    static void ResetEEPROM();

    
    static String ReadSerial(bool force = false);
    static String* AskInput(int times = 3);
    static bool SerialReceived();
    static long ConvertToRGB(const char hexstring[], char i);

  private:

  protected:
  
};

#endif

