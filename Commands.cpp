#include "Commands.h"
#include "RGBMyPC.h"

void Commands::RunCommand(String exptInput, String givenInput)
{
  
}

void Commands::Status()
{
  Serial.println("OK");
}

void Commands::Reset()
{
  Serial.println("OK");

  // Resets Arduino
  void (* resetArduino) (void) = 0;
}

void Commands::Off()
{
  GetCont()->SetPixelsColor(0, GetCont()->numPixels(), 0, 0, 0);
  
  Serial.println("OK");
}

void Commands::StaticColor()
{
  String input = RGBMyPC::AskInput(1)[0];

  const char* hexColor = input.c_str();
  
  int r = RGBMyPC::ConvertToRGB(hexColor, 'r');
  int g = RGBMyPC::ConvertToRGB(hexColor, 'g');
  int b = RGBMyPC::ConvertToRGB(hexColor, 'b');

  // Check for valid RGB code
  if (r > 0 || g > 0 || b > 0)
  {
    GetCont()->ColorWipe(GetCont()->Color(r, g, b), 50);
    Serial.println(hexColor);
  } else {
    Serial.println("FALSE");
  }
  
  // Write EEPROM
  RGBMyPC::WriteEEPROM(1, r);
  RGBMyPC::WriteEEPROM(2, g);
  RGBMyPC::WriteEEPROM(3, b);
}

void Commands::Brightness()
{
  
}

void Commands::Breathing()
{
  
}


