#include <Adafruit_NeoPixel.h>
#include <string.h>
#include "LEDController.h"
#include "App.h"


/**
 * Firmware constants
 */

const String VERSION        = "1.0.2-alpha";
const String SERIAL_STARTER = "RGB";

/**
 * Defined settings
 */

#define PIN 6
#define LEDS 60
#define BAUD_RATE 9600
#define SERIAL_TIMEOUT 60
#define DEFAULT_COLOR "#FFFFFF"

// Create a new controllable RGB strip
LEDController strip = LEDController(LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Provide us a fresh application instance
App app = App(BAUD_RATE, SERIAL_TIMEOUT, &strip, VERSION);





/**
 * Reset helper function
 */

 void (* resetArduino) (void) = 0;

/**
bool eptCmd(String eptCmd = "", String givenCmd = "")
{
  if (eptCmd.length() > 0)
  {
    return (SERIAL_STARTER + "+" + eptCmd) == givenCmd;
  }
  return SERIAL_STARTER == givenCmd;
}

void runCmd(String cmd)
{
    if (eptCmd("", cmd))
    {
      Serial.println("OK");
    }

    rmp.Status();

    if (eptCmd("VERSION", cmd))
    {
      //rmp.
    }

    if (eptCmd("RESET", cmd))
    {
      Serial.println("OK");
      resetArduino();
    }

    if (eptCmd("OFF", cmd))
    {
      strip.SetPixelsColor(0, LEDS, 0, 0, 0);
      Serial.println("OK");
    }

    if (eptCmd("STATIC_COLOR", cmd))
    {
      Serial.println("SUPPLY");
      while (true)
      {
          if (Serial.available() > 0) 
          {
            String output = rmp.ReadSerial();
            const char * hexColor = output.c_str();

            int r = rmp.ConvertToRGB(hexColor, 'r');
            int g = rmp.ConvertToRGB(hexColor, 'g');
            int b = rmp.ConvertToRGB(hexColor, 'b');

            // Check for valid RGB code
            if (r > 0 || g > 0 || b > 0)
            {
              strip.ColorWipe(strip.Color(r, g, b), 50);
              Serial.println(hexColor);
            } else {
              Serial.println("FALSE");
            }

            break;
          }
      }
    }

    if (eptCmd("BRIGHTNESS", cmd))
    {
      Serial.println("SUPPLY");
      while (true)
      {
        if (Serial.available() > 0)
        {
          String output = rmp.ReadSerial();
          int brightness = output.toInt();

          if (brightness < 256 && brightness > -1)
          {
            strip.setBrightness(brightness);
            strip.show();
            
            Serial.println(brightness);
          } else {
            Serial.println("FALSE");
          }

          break;
        }
      }
    }

    if (eptCmd("BREATHING", cmd))
    {
      Serial.println("SUPPLY");
      while (true)
      {
          if (Serial.available() > 0) 
          {
            String output = rmp.ReadSerial();
            const char * hexColor = output.c_str();

            int r = rmp.ConvertToRGB(hexColor, 'r');
            int g = rmp.ConvertToRGB(hexColor, 'g');
            int b = rmp.ConvertToRGB(hexColor, 'b');

            // Check for valid RGB code
            if (r > 0 || g > 0 || b > 0)
            {
              strip.EffectBreathing(r, g, b, 5);
              Serial.println(hexColor);
            } else {
              Serial.println("FALSE");
            }

            break;
          }
      }
    }

    if (eptCmd("INDV_COLOR", cmd))
    {
      Serial.println("SUPPLY");
      while (true)
      {
        if (Serial.available() > 0)
        {
          int ledNumber = rmp.ReadSerial().toInt();

          while (true)
          {
            if (Serial.available() > 0)
            {
              String hexInput = rmp.ReadSerial();
              const char * hexColor = hexInput.c_str();
  
              int r = rmp.ConvertToRGB(hexColor, 'r');
              int g = rmp.ConvertToRGB(hexColor, 'g');
              int b = rmp.ConvertToRGB(hexColor, 'b');
  
              // Check for valid RGB code
              if (r > 0 || g > 0 || b > 0)
              {
                strip.setPixelColor(ledNumber, r, g, b);
                strip.show();
                
                Serial.println(hexColor);
              } else {
                Serial.println("FALSE");
              }
  
              break;
            }
          }

          break;
        }
      }
    }

    if (eptCmd("INDV_COLOR_SECT", cmd))
    {
      Serial.println("SUPPLY");
      while (true)
      {
        
        if (Serial.available() > 0)
        {
          int sectionBegin = rmp.ReadSerial().toInt();

          while (true)
          {
            if (Serial.available() > 0)
            {
              int sectionEnd = rmp.ReadSerial().toInt();

              // Check if section length is valid
              if (sectionBegin > sectionEnd)
              {
                Serial.println("FALSE");
                break;
              }

              while (true)
              {
                if (Serial.available() > 0)
                {
                  String hexInput = rmp.ReadSerial();
                  const char * hexColor = hexInput.c_str();
      
                  int r = rmp.ConvertToRGB(hexColor, 'r');
                  int g = rmp.ConvertToRGB(hexColor, 'g');
                  int b = rmp.ConvertToRGB(hexColor, 'b');

                  strip.SetPixelsColor(sectionBegin, sectionEnd, r, g, b);

                  Serial.println(hexInput);
                  
                  break; 
                }
              }

              
              
              break;
            }
          }

          break;
        }
      }

    }

}

*/

/**
 * The setup
 */

void setup() {
  

  // Provide the data to the app initialisator
  app.Init();

  //app.WriteEEPROM(0, 7);

  // Read data from EEPROM
  //app.ResetEEPROM();

  //app.Status();

  LEDController* cont = app.GetCont();

  long r = app.ReadEEPROM(1);
  long g = app.ReadEEPROM(2);
  long b = app.ReadEEPROM(3);

  cont->ColorWipe(cont->Color(r, g, b), 50);

  app.StaticColor();

  //String hex = app.AskInput(1)[0];

  //const char* hexstring = hex.c_str();
  
  //long r = app.ConvertToRGB(hexstring, 'r');
  //long g = app.ConvertToRGB(hexstring, 'g');
  //long b = app.ConvertToRGB(hexstring, 'b');

  //cont->ColorWipe(strip.Color(r, g, b), 50);

  //strip.SetPixelsColor(0, 30 , 0, 255, 0);

  //strip.RainbowCycle(50);

 
}

void loop() {
  String command;

  // Write data to EPPROM, so we can remember the last provided color of the first LED, if the Arduino was turned off
  
}
