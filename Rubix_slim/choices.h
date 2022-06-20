#define choices_h
#define cube_h
#define output_h

#include <LiquidCrystal.h>
#include  <PololuLedStrip.h>
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



class Cube
{
  public:
    Cube(int);
    int noIdeaWhy;                     
    void reInit();                     
    void show();
    void dark();
    void showTurnSide(int side,bool dir);
    void showTurnMid(int side,bool dir); 
    void showTurnCube(int side,bool dir);
    bool checkCubeSolved();             //checks if the cube is solved
    void littleShow();                  //gives a little show
    void toScreen();                    
    const byte* handCube();             

    static const int numSides = 6;      
    
    const int backSide   = 3;
    const int topSide    = 2;
    const int frontSide  = 1;
    const int groundSide = 0;
    const int leftSide   = 4;
    const int rightSide  = 5;
  
    static const int numPos  = 9;        //Each side has 9 positions  //needs to be static zijn as number of array elements needs to be fixed before compilation

    const bool CW = true;

    
  private:

    void turnSide(int, bool);           //turns a side of Cube
    void turnRim(int, bool);            //turns rim of a side of Cube
    void turnMid(int, bool);            //turns the mids of of Cube
    int _noIdeaWhy;
    byte Color[numSides][numPos];         //dach position has a color that will be represented in a byte
    static const int numRimPos=12;        //dach rim has 12 positions
    static const int numMidPos=12;        //each mid has 12 positions
    byte* rimsPtr[numSides][numRimPos];   //array of pointers to addresses of the rim positions of a Side, used in turnRim()      
    byte* midsPtr[numSides][numRimPos];   //array of pointers to addresses of the mids positions of a Side, used in turnMid()   
    byte delta_t = 150;                   //gives good visuals
};


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
