#include "App.h"

//static String version = "";

App::App(int baud, int timeout, LEDController* c, String v)
{
  // Setting up some variables
  this->baud    = baud;
  this->timeout = timeout;
  
  // Set up the LED controller for the Commands class, so it has access to our declared functions in the LEDController
  this->SetController(c);

  // Set the application version
  this->SetVersion(v);
}

void App::Init()
{
  // Setting up serial connection on defined baudrate (bits/sec)
  Serial.begin(this->baud);

  // Set up timeout, timeout is important for reading converting serial received bytes to strings
  Serial.setTimeout(this->timeout);

  // Prepare the Adafruit NeoPixel library
  this->GetCont()->begin();

  // Show a empty LED array
  this->GetCont()->show();
}

void App::SetVersion(String v)
{
  this->version = v;
}

String App::GetVersion()
{
  return this->version;
}

void App::Version()
{
  Serial.println(this->GetVersion());
}

void Commands::SetController(LEDController* c)
{
  this->controller = c;
}

LEDController* Commands::GetCont()
{
  return this->controller;
}

