#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#include <EEPROM.h>
#include "RGBMyPC.h"

//LEDController* RGBMyPC::GetCont()
//{
//  return controller;
//}

bool RGBMyPC::SerialReceived()
{
  return Serial.available() > 0;
}

String RGBMyPC::ReadSerial(bool force)
{
  if (force)
  {
    while (true)
    {
      if (SerialReceived())
      {
        return Serial.readString();
      }

      delay(50);
    }
  }
  
  return Serial.readString();
}

String* RGBMyPC::AskInput(int times)
{
  String* inputs = new String[times];
  
  for (int i=0; i < times; i++)
  {
    Serial.println("SUPPLY");
    inputs[i] = ReadSerial(true); 
  }

  return inputs;
}

bool RGBMyPC::WriteEEPROM(int address, int data, bool overwrite)
{
  if (address <= EEPROM.length())
  {
    if (EEPROM.read(address) == 255)
    {
      EEPROM.write(address, data);
      return true;
    } else {
      if (overwrite)
      {
        EEPROM.write(address, data);
        return true;
      }
    }
  }

  return false;
}

int RGBMyPC::ReadEEPROM(int address)
{
  if (address <= EEPROM.length())
  {
    return EEPROM.read(address);
  }

  return 0;
}

bool RGBMyPC::UnsetEEPROM(int address)
{
  if (address <= EEPROM.length())
  {
    if (EEPROM.read(address) != 255)
    {
      EEPROM.write(address, 255);
      return true;
    }
  }

  return false;
}

void RGBMyPC::ResetEEPROM()
{
  int length = EEPROM.length();
  
  for (int i=0; i <= length; i++)
  {
    EEPROM.write(i, 255);
  }
}

long RGBMyPC::ConvertToRGB(const char hexstring[], char i)
{
  // Get rid of '#' and convert it to integer
  long number = strtol( &hexstring[1], NULL, 16);

  // Split them up into r, g, b values
  switch (i) {
    case 'r': return number >> 16;
    case 'g': return number >> 8 & 0xFF;
    case 'b': return number & 0xFF;
    default: return 0;
  }
}


