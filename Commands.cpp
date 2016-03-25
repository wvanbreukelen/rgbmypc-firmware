#include "Commands.h"

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
  
}

void Commands::Brightness()
{
  
}

void Commands::Breathing()
{
  
}


