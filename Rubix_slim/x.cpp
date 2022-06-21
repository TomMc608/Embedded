#define LED_COUNT 54


#include <PololuLedStrip.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
PololuLedStrip<2> ledStrip; 

#include "Arduino.h"
#include "x.h"

Choices::Choices(int AIpin, int numOpt)
{
  _AIpin = AIpin;
  _numOpt = numOpt;
}


int Choices::getOption() {
  bool valid = 0;

  while (!valid) {
    int value = readValue();

    const int maxValue = 1024;
    int stepSize = maxValue/(_numOpt+1);
    int validZone = stepSize/4;

    for (int curOpt = 0; curOpt <= _numOpt; curOpt++) {
      if (value > curOpt*stepSize-validZone && value < curOpt*stepSize+validZone) {
        return(curOpt);
      }   
    }
  }
}


int Choices::readValue(){
  const int numReads = 10; //Value is measured multiple times
  analogReference(EXTERNAL);
  int totVal  = 0;
  int lowest  = 1024;
  int highest = 0;
  delay(10);
  for (int i = 0; i < numReads; i++) {
    int curVal = analogRead(_AIpin);
    if (curVal < lowest) lowest = curVal;
    if (curVal > highest) highest = curVal;
    totVal += curVal;
    delay(10);
  }
  int value = totVal/numReads;
  if ((highest - lowest)>50) value = 0;
  return(value);
}


//--------------------------------------------------------------------------------------------------------------------------------------



Cube::Cube(int) {

  int _noIdeaWhy=noIdeaWhy;

  //initialize cube
  for (int curSide = 0; curSide < numSides; curSide++) {    //fill all sides
    for (int curPos = 0; curPos < numPos; curPos++) {       //fill all positions
      Color[curSide][curPos] = 10*curSide + curPos;       
    }
  }  

  //initialize Rims        01    02    03    04    05    06    07    08    09    10    11    12 
  byte rims[6][12][2] = {{{1,7},{1,6},{1,5},{5,7},{5,6},{5,5},{3,3},{3,2},{3,1},{4,7},{4,6},{4,5}}, //rims side 0
                         {{2,7},{2,6},{2,5},{5,1},{5,8},{5,7},{0,3},{0,2},{0,1},{4,5},{4,4},{4,3}}, //rims side 1
                         {{3,7},{3,6},{3,5},{5,3},{5,2},{5,1},{1,3},{1,2},{1,1},{4,3},{4,2},{4,1}}, //rims side 2
                         {{0,7},{0,6},{0,5},{5,5},{5,4},{5,3},{2,3},{2,2},{2,1},{4,1},{4,8},{4,7}}, //rims side 3
                           
                         {{2,1},{2,8},{2,7},{1,1},{1,8},{1,7},{0,1},{0,8},{0,7},{3,1},{3,8},{3,7}}, //rims side 4
                         {{2,5},{2,4},{2,3},{3,5},{3,4},{3,3},{0,5},{0,4},{0,3},{1,5},{1,4},{1,3}}};//rims side 5
                                                                                                     
  for (int curSide = 0; curSide < numSides; curSide++) {
    for (int curRimPos = 0; curRimPos < numRimPos; curRimPos++) {
      const int side=0;  //element index of Side in rims
      const int pos=1;   //element index of Position in rims
      rimsPtr[curSide][curRimPos] = &Color[rims[curSide][curRimPos][side]][rims[curSide][curRimPos][pos]]; 
    }  
  } 

  //intitialize Mids       01    02    03    04    05    06    07    08    09    10    11    12 
  byte mids[6][12][2] = {{{1,8},{1,0},{1,4},{5,8},{5,0},{5,4},{3,4},{3,0},{3,8},{4,8},{4,0},{4,4}}, //mids side 0
                         {{2,8},{2,0},{2,4},{5,2},{5,0},{5,6},{0,4},{0,0},{0,8},{4,6},{4,0},{4,2}}, //mids side 1                                           
                         {{3,8},{3,0},{3,4},{5,4},{5,0},{5,8},{1,4},{1,0},{1,8},{4,4},{4,0},{4,8}}, //mids side 2   
                         {{0,8},{0,0},{0,4},{5,6},{5,0},{5,2},{2,4},{2,0},{2,8},{4,2},{4,0},{4,6}}, //mids side 3
                         
                         {{2,2},{2,0},{2,6},{1,2},{1,0},{1,6},{0,2},{0,0},{0,6},{3,2},{3,0},{3,6}}, //mids side 4                                                
                         {{2,6},{2,0},{2,2},{3,6},{3,0},{3,2},{0,6},{0,0},{0,2},{1,6},{1,0},{1,2}}};//mids side 5

  for (int curSide = 0; curSide < numSides; curSide++) {
    for (int curMidPos = 0; curMidPos < numMidPos; curMidPos++) {
      const int side=0;  //element index of Side in mids
      const int pos=1;   //element index of Position in mids
      midsPtr[curSide][curMidPos] = &Color[mids[curSide][curMidPos][side]][mids[curSide][curMidPos][pos]]; 
    }  
  } 
}

//This function checks if the cube is solved (each side has one color)
bool Cube::checkCubeSolved() {
  for (int curSide = 0; curSide < numSides; curSide++) {    
    byte sideColor = Color[curSide][0]/10;
    for (int curPos = 1; curPos < numPos; curPos++) {       
      if (!(Color[curSide][curPos]/10==sideColor)) return false;  
    }
  } 
  return true;
}

//This procedure reinitializes the cube
void Cube::reInit() {
  for (int curSide = 0; curSide < numSides; curSide++) {   
    for (int curPos = 0; curPos < numPos; curPos++) {      
      Color[curSide][curPos] = 10*curSide + curPos;       //later colours will be set here  
    }
  } 
  show(); 
}



//This procedure shows a turn of the cube as a whole
void Cube::showTurnCube(int side,bool dir) { 
  showTurnSide(side,dir);
  showTurnMid(side,dir);
  int oppSide = 0;
  if (side<2) oppSide = side+2;
  if (side>1 && side<4) oppSide = side-2; 
  if (side==4) oppSide = 5;
  if (side==5) oppSide = 4;
  showTurnSide(oppSide,!dir);
  delay(delta_t);
}

//This procedure shows a turn of a side
void Cube::showTurnSide(int side,bool dir) { 
  turnRim(side,dir);
  show();
  delay(delta_t);
  for (int i = 0; i<2; i++) {
    turnSide(side,dir);
    show();
    delay(delta_t);
    turnRim(side,dir);
    show();
    delay(delta_t);
  }
}

//This procedrue shows a turn of the mids
void Cube::showTurnMid(int side,bool dir) {
  for (int i = 0; i<3; i++) {
    turnMid(side,dir);
    show();
    delay(delta_t);
  }
}

//This procedure turns the side
void Cube::turnSide(int side, bool dir) {                   //this procedure must be run 2 times per turn
  byte tempStoreColor;
  if (dir == CW) {                                          //turn ClockWise
    tempStoreColor = Color[side][numPos-1];                 //Color value of Position 8 is temporarily stored
    for (int curPos = numPos-2; curPos > 0; curPos--) {        
      Color[side][curPos+1] = Color[side][curPos];          //shift Color value Clockwise
    }
    Color[side][1] = tempStoreColor;                        //put stored Color value in Position 1 
  }
  else {                                                    //turn Counter ClockWise
    tempStoreColor = Color[side][1];                        //Color value of Position 1 is temporarily stored
    for (int curPos = 1; curPos < numPos-1; curPos++) {
      Color[side][curPos] = Color[side][curPos+1];          //shift Color value counter Clockwise
    }
    Color[side][numPos-1] = tempStoreColor;                 //put stored Color value in Position 8
  }  
}

//this procedure turns de mids
void Cube::turnMid(int side, bool dir) {                        //this procedure must be run 3 times per turn      
  byte tempStoreColor;                                        
  if (dir == CW) {                                              //if turn ClockWise
    tempStoreColor = *midsPtr[side][numRimPos-1];               //Color value of Position 12 is temporarily stored
    for (int curPos = numMidPos-1; curPos > 0; curPos--) {   
      *midsPtr[side][curPos] = *midsPtr[side][curPos-1];        //shift Color value Clockwise
    }
    *midsPtr[side][0] = tempStoreColor;                         //put stored Color value in Position 0 
  }
  else {                                                        //turn Counter ClockWise
    tempStoreColor = *midsPtr[side][0];                         //Color value of Position 0 is temporarily stored
    for (int curPos = 0; curPos < numMidPos-1; curPos++) {   
      *midsPtr[side][curPos] = *midsPtr[side][curPos+1];        //shift Color value Clockwise
    }
    *midsPtr[side][numRimPos-1] = tempStoreColor;               //put stored Color value in Position 12 
  } 
}

//This procedure turns the rims of a Side
void Cube::turnRim(int side, bool dir) {                       //this procedure must be run 3 times per turn
  byte tempStoreColor;                                        
  if (dir == CW) {                                              //turn ClockWise
    tempStoreColor = *rimsPtr[side][numRimPos-1];               //Color value of Position 12 is temporarily stored
    for (int curPos = numRimPos-1; curPos > 0; curPos--) {   
      *rimsPtr[side][curPos] = *rimsPtr[side][curPos-1];        //shift Color value Clockwise
    }
    *rimsPtr[side][0] = tempStoreColor;                        
  }
  else {                                                        //turn counter clockwise
    tempStoreColor = *rimsPtr[side][0];                         //Color value of Position 0 is temporarily stored
    for (int curPos = 0; curPos < numRimPos-1; curPos++) {   
      *rimsPtr[side][curPos] = *rimsPtr[side][curPos+1];        //shift Color value counter clockwise
    }
    *rimsPtr[side][numRimPos-1] = tempStoreColor;               //put stored Color value in Position 12 
  }
}

//This function hands the address of the cube to the ledstrip writing procedure
const byte* Cube::handCube() {
  return &Color[0][0];
}

#define _debugging
#ifdef _debugging
//This procedure writes the Cube colors to Serial (for debugging purposes)
void Cube::toScreen() {
  Serial.println("Cube");
  int transPos[] = { 1,2,3,
                     8,0,4,
                     7,6,5 };
  int curSide;
  
  //backSide and TopSide              
  for (curSide = backSide; curSide >= topSide; curSide--) {    
    for (int i=0; i<3; i++) { 
      Serial.print("                ");
      for (int j=(3*i); j<(3+3*i); j++) {                    
        int pos = transPos[j];
        Serial.print('[');
        if(Color[curSide][pos]<9) {Serial.print(' ');}
        Serial.print(Color[curSide][pos]);
        Serial.print("] ");
      }
      Serial.println();
    }
    Serial.println();
  }
  
  //leftSide, frontSide and rightSide
  for (int i=0; i<3; i++) { // voor alle posities
    curSide = leftSide;
    for (int j=(3*i); j<(3+3*i); j++) {                    
      int pos = transPos[j];      
      Serial.print('[');
      if(Color[curSide][pos]<9) {Serial.print(' ');}
      Serial.print(Color[curSide][pos]);
      Serial.print("] ");
    }
    Serial.print(' '); 
    curSide = frontSide;
    for (int j=(3*i); j<(3+3*i); j++) {                    
      int pos = transPos[j];
      Serial.print('[');
      if(Color[curSide][pos]<9) {Serial.print(' ');}
      Serial.print(Color[curSide][pos]);
      Serial.print("] ");
    }
    Serial.print(' ');  
    curSide = rightSide;
    for (int j=(3*i); j<(3+3*i); j++) {                    
      int pos = transPos[j];
      Serial.print('[');
      if(Color[curSide][pos]<9) {Serial.print(' ');}
      Serial.print(Color[curSide][pos]);
      Serial.print("] ");
    }
    Serial.println();
  } 
  Serial.println();
   
  //groundSide
  curSide = groundSide;                    
  for (int i=0; i<3; i++) { // voor alle posities
    Serial.print("                "); 
    for (int j=(3*i); j<(3+3*i); j++) {                         
      int pos = transPos[j];
      Serial.print('[');
      if(Color[curSide][pos]<9) {Serial.print(' ');}
      Serial.print(Color[curSide][pos]);
      Serial.print("] ");
    }
    Serial.println();
  }
  Serial.println();
}
#endif


 void Cube::dark() {
  rgb_color Dark; 
  Dark.red     =  0;
  Dark.green   =  0;
  Dark.blue    =  0;  

  rgb_color colors[54];
  for (int i=0; i<54; i++) {
    colors[i] = Dark;
  }
  ledStrip.write(colors, LED_COUNT);
 }
 
void Cube::show() {
  
  rgb_color Red;
  Red.red      = 10;
  Red.green    =  0;
  Red.blue     =  0;   

  rgb_color Blue;
  Blue.red     =  0;
  Blue.green   =  0;
  Blue.blue    = 10;

  rgb_color Green;
  Green.red    =  0;
  Green.green  = 10;
  Green.blue   =  0;

  rgb_color Yellow;
  Yellow.red   = 60;
  Yellow.green = 45;
  Yellow.blue  =  0;

  rgb_color White;
  White.red    = 20;
  White.green  = 20;
  White.blue   = 20;
  
  rgb_color Orange;
  Orange.red   = 45;
  Orange.green = 15;
  Orange.blue  =  0;

  rgb_color Dark; 
  Dark.red     =  0;
  Dark.green   =  0;
  Dark.blue    =  0;  
  
  rgb_color Colors[54];

  const byte ledStripAddr []= {31,20,32,44,43,42,30,18,19,
                               22,11,23,35,34,33,21, 9,10,
                               25,14,26,38,37,36,24,12,13,
                               28,17,29,41,40,39,27,15,16,
                                4, 2, 3, 8, 7, 6, 5, 0, 1, 
                               49,53,48,47,46,45,50,51,52};

  for (int i=0; i<54; i++) {
    Colors[i] = Dark;
  } 

  const byte* cubePtr = handCube();
  for (int i = 0; i<54; i++) {
      
    byte curColor = *cubePtr/10;
    byte curLedStripAddr  = ledStripAddr[i];
    switch (curColor) {
      case 0:
        Colors[curLedStripAddr] = Yellow;
        break;          
      case 1:
        Colors[curLedStripAddr] = Blue;
        break;
      case 2:
        Colors[curLedStripAddr] = White;
        break; 
      case 3: 
        Colors[curLedStripAddr] = Green;
        break;          
      case 4:
        Colors[curLedStripAddr] = Red;
        break;
      case 5:
        Colors[curLedStripAddr] = Orange;
        break;             
    }
    cubePtr++;
  }
  ledStrip.write(Colors, LED_COUNT);
}

 //--------------------------------------------------------------------------------------------------------------------------





Output::Output(bool serial, bool cryst) {
  lcd.begin(16,2);
  _serial = serial;
  _cryst  = cryst;
}

void Output::clrscr() {          
  if (_serial) {
    Serial.println();
  }
  if (_cryst) {
    lcd.clear();
  }
}

void Output::txt(String text) {  
  if (_serial) {
    Serial.print(text);     
  }
  if (_cryst) { 
    lcd.print(text);
  }
}

void Output::nxtln() {            
  if (_serial) {
    Serial.println();
  }
  if (_cryst) { 
    lcd.setCursor(0,1);
  }
}
