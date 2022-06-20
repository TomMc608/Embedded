
#ifndef choices_h
#define choices_h

#include "Arduino.h"

class Choices
{
  public:
    Choices(int AIpin, int numOpt);
    int getOption();
    const int arrowUp     = 1;
    const int arrowLeft   = 2;
    const int arrowCentre = 3;
    const int arrowRight  = 4;
    const int arrowDown   = 5;
    const int highBut     = 1;
    const int midBut      = 2;
    const int lowBut      = 3;
    
  private:
    int _AIpin;
    int _numOpt;
    int readValue();
};

#endif
