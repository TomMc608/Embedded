#ifndef cube_h
#define cube_h

#include "Arduino.h"
#include  <PololuLedStrip.h>


class Cube
{
  public:
    Cube(int);
    int noIdeaWhy;                      //somehow a class cannot have a constructor without an arguement...
    void reInit();                      //reinitializes the Cube
    void show();
    void dark();
    void showTurnSide(int side,bool dir);
    void showTurnMid(int side,bool dir); 
    void showTurnCube(int side,bool dir);
    bool checkCubeSolved();             //checks if the cube is solved
    void littleShow();                  //gives a little show
    void toScreen();                    //writes Cube to computer screen via Serial
    const byte* handCube();             //hands Cube to main program

    static const int numSides = 6;      //Cube has 6 sides
    
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
#endif
