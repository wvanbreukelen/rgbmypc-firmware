#include <Adafruit_NeoPixel.h>
#include <string.h>

/**
 * Firmware constants
 */

const String VERSION        = "1.0";
const String SERIAL_STARTER = "RGB";

/**
 * Defined settings
 */

#define PIN 6
#define LEDS 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

/**
 * LED helper functions
 */

void effectBreathing(int r, int g, int b, int rounds = 3)
{
  float MaximumBrightness = 255;
  float SpeedFactor = 0.008; // I don't actually know what would look good
  float StepDelay = 5; // ms for a step delay on the lights

    // Make the lights breathe
  for (int i = 0; i < 550 * rounds; i++) {
    // Intensity will go from 10 - MaximumBrightness in a "breathing" manner
    float intensity = MaximumBrightness /2.0 * (1.0 + sin(SpeedFactor * i));
    strip.setBrightness(intensity);
    // Now set every LED to that color
    // NOTE: To do indivial LED control, checks have to be made!
    for (int ledNumber=0; ledNumber < LEDS; ledNumber++) {
      strip.setPixelColor(ledNumber, r, g, b);
    }
  
    strip.show();
    //Wait a bit before continuing to breathe
    delay(StepDelay);

   }

   strip.setBrightness(0);
   strip.show();
}

void setup() {  
  Serial.begin(9600);

  strip.begin();
  strip.show();

  char hexstring[] = "#00960D";
  
  long r = hexToRGB(hexstring, 'r');
  long g = hexToRGB(hexstring, 'g');
  long b = hexToRGB(hexstring, 'b');
  
  colorWipe(strip.Color(r, g, b), 50);


  //effectBreathing(r, g, b);


}

void loop() {
  String command;

  if (Serial.available() > 0) 
  {
    command = readSerial();

    if (command == SERIAL_STARTER)
    {
      Serial.println("OK");
    }

    if (command == SERIAL_STARTER + "+VERSION")
    {
      Serial.println(VERSION);
    }

    if (command == SERIAL_STARTER + "+STATIC_COLOR")
    {
      Serial.println("SUPPLY");
      while (true)
      {
          if (Serial.available() > 0) 
          {
            String output = readSerial();
            const char * hexColor = output.c_str();

            int r = hexToRGB(hexColor, 'r');
            int g = hexToRGB(hexColor, 'g');
            int b = hexToRGB(hexColor, 'b');

            // Check for valid RGB code
            if (r > 0 || g > 0 || b > 0)
            {
              colorWipe(strip.Color(r, g, b), 50);
              Serial.println(hexColor);
            } else {
              Serial.println("FALSE");
            }

            break;
          }
      }
    }

    if (command == SERIAL_STARTER + "+BRIGHTNESS")
    {
      Serial.println("SUPPLY");
      while (true)
      {
        if (Serial.available() > 0)
        {
          String output = readSerial();
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

    if (command == SERIAL_STARTER + "+BREATHING")
    {
      Serial.println("SUPPLY");
      while (true)
      {
          if (Serial.available() > 0) 
          {
            String output = readSerial();
            const char * hexColor = output.c_str();

            int r = hexToRGB(hexColor, 'r');
            int g = hexToRGB(hexColor, 'g');
            int b = hexToRGB(hexColor, 'b');

            // Check for valid RGB code
            if (r > 0 || g > 0 || b > 0)
            {
              effectBreathing(r, g, b, 5);
              Serial.println(hexColor);
            } else {
              Serial.println("FALSE");
            }

            break;
          }
      }
    }

    if (command == SERIAL_STARTER + "+INDV_COLOR")
    {
      Serial.println("SUPPLY");
      while (true)
      {
        if (Serial.available() > 0)
        {
          int ledNumber = readSerial().toInt();

          while (true)
          {
            if (Serial.available() > 0)
            {
              String hexInput = readSerial();
              const char * hexColor = hexInput.c_str();
  
              int r = hexToRGB(hexColor, 'r');
              int g = hexToRGB(hexColor, 'g');
              int b = hexToRGB(hexColor, 'b');
  
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

    
  }
  
}

/**
 * Supporting functions
 */

String readSerial()
{
  return Serial.readString();
}

long hexToRGB(const char hexstring[], char value)
{
  // Get rid of '#' and convert it to integer
  long number = strtol( &hexstring[1], NULL, 16);

  // Split them up into r, g, b values
  switch (value) {
    case 'r': return number >> 16;
    case 'g': return number >> 8 & 0xFF;
    case 'b': return number & 0xFF;
    default: return 0;
  }
}


// Schakel LED na LED aan
void colorWipe(uint32_t c, uint8_t wait)
{
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Iets andere variatie van de rainbow functie maar dan iets gelijkmatiger
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style kruipende LEDs.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //10 x doorlopen
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //zet elke 3de RGD LED aan
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //zet elke 3de RGB LED uit
      }
    }
  }
}

//Theatre-style kruipen met regenboog effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // gebruik alle 256 kleuren in het wiel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //zet elke 3de LED aan
        }
        strip.show();

        delay(wait);

        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //zet elke 3de LED uit
        }
    }
  }
}

// Voer een waarde van 0 tot 255 in voor berekening van kleur waarden.
// De kleuren zijn een r - g - b combinatie.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
