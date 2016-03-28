#ifndef APP_H
#define APP_H

#include "RGBMyPC.h"
#include "Commands.h"

class App : public RGBMyPC, public Commands
{
  public:
    // Variables
    String version;
    int baud;
    int timeout;
  
    // Application methods
    App(int baud, int timeout, LEDController* s, String v);
    void Init();
    
    String GetVersion();
    void SetVersion(String version);
    // Command helper functions, declared in App
    void Version();
};

#endif
