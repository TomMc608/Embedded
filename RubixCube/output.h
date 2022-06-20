#ifndef output_h
#define output_h

#include "Arduino.h"
#include <LiquidCrystal.h>

class Output
{
  public:
    Output(bool serial,bool cryst);
    int noIdeaWhy;
    void txt(String);
    void nxtln();
    void clrscr();
  private:
    bool _serial;
    bool _cryst; 
};

#endif
