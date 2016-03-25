#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

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
      if (this->SerialReceived())
      {
        return Serial.readString();
      }
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
    inputs[i] = this->ReadSerial(true); 
  }

  return inputs;
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


