/* this program turns a ledstrip glued to a wooden cube into a Rubiks Cube 
 *  
 */
//major changes on March 18th 2019
#include "choices.h"
#include "cube.h"
#include "output.h"
#include <LiquidCrystal.h>
#include <PololuLedStrip.h>

Choices LeftPanel(A5, 5); //set 5 options at pin A5
Choices RightPanel(A4, 3);//set 3 options at pin A3
Cube MyCube(3);           //would be nice to have DO port of ledstrip as an argument
Output MyOutput(false, true);  //output to Serial output and or lcd output

#define _dutch   //dutch language selected, conditional compiling is applied because insufficient dynamic memory to store 2 languages

void setup() {
  Serial.begin(9600);
  delay(500);
  MyCube.show();
  delay(500);
  MyOutput.clrscr();
#ifndef _dutch
  MyOutput.txt("Hello there!");  //default language
#else
  MyOutput.txt("Hallo daar!"); 
#endif
  MyCube.littleShow();
  MyOutput.clrscr();
}



const int turnSide  = 0;
const int turnMid   = 1;
const int turnCube  = 2;
const int undoLast  = 3;
const int solveCube = 4;

const bool CW = true;

const int histMax = 30;    //max number of turns in memory
int turnNr      = 0;       //number of turns done    
int lastSolved  = 0;       //last time that cube was solved
int turnsInHist = 0;       //current number of turns in history
byte turnHist[histMax];
/* turns are stored in turnHist
 *  1 byte is used to store turn
 *  1 byte may represent numbers from 0 - 255
 *  coding: 100*dir + 10 * side + task
 *  history should be implemented in Class Cube
 */
bool escFlag = false;

void loop() {

  int task;
  int side;
  bool dir;

  escFlag = false;
  task = getTask();
  switch (task) {
    case turnSide:
      while (true) {
        side = getSide();
        if (escFlag) break;
        dir  = getDir();
        if (escFlag) break;
        MyCube.showTurnSide(side, dir);     
        turnHist[turnNr%histMax]= 100*dir+ 10*side + task; 
        turnNr++;
        turnsInHist++;
      }
      break;
    case turnMid:
      while (true) {
        side = getSide();
        if (escFlag) break;              
        dir  = getDir();
        if (escFlag) break;
        MyCube.showTurnMid(side, dir);
        turnHist[turnNr%histMax]= 100*dir+ 10*side + task;  
        turnNr++;
        turnsInHist++;
      }
      break;      
    case turnCube:
      while (true) {
        side = getSide();
        if (escFlag) break; 
        dir  = getDir();   
        if (escFlag) break;   
        MyCube.showTurnCube(side,dir);
        turnHist[turnNr%histMax]= 100*dir+ 10*side + task;      
        turnNr++;
        turnsInHist++;
      }
      break;
    case undoLast:      
      do {
        if (turnsInHist == 0) {
          MyOutput.clrscr();
#ifndef _dutch
          MyOutput.txt("Cannot undo");
#else
          MyOutput.txt("Ongedaan maken");
          MyOutput.nxtln();
          MyOutput.txt("niet mogelijk");
#endif
          delay(1000);
          escFlag = true;
        } 
        if (escFlag) break;   
        turnNr--;
        turnsInHist--;           
        undoLastTurn();
        delay(500);
        if (turnsInHist == 0) break;
        MyOutput.clrscr();
#ifndef _dutch
        MyOutput.txt("Undo another");
        MyOutput.nxtln(); 
        MyOutput.txt("turn?");
#else
        MyOutput.txt("Nogmaals"); 
        MyOutput.nxtln();       
        MyOutput.txt("terug draaien?");
#endif
        while (!escFlag) {
          int choice = RightPanel.getOption();        
          if (choice == RightPanel.highBut) {
            escFlag = true;
            break;
          }
          if (choice == RightPanel.lowBut) {
            break;
          }
        }  
      } while (!escFlag);  
      break;
    case solveCube:
      if ((turnsInHist == 0) || ((turnNr-lastSolved)>turnsInHist)) {  //not enough memory to undo until solved
        MyCube.reInit();
        lastSolved = 0;
        turnNr = 0;
        turnsInHist = 0;
      }
      else {
        while(turnNr > lastSolved) {
          turnNr--;   
          turnsInHist--;      
          undoLastTurn();
          delay(500); 
        }     
      }
      break;
  }
  if (MyCube.checkCubeSolved()) {
    MyOutput.clrscr();
#ifndef _dutch
    MyOutput.txt("Cube solved!");
#else
    MyOutput.txt("Kubus opgelost!");
#endif
    for (int i=0; i<5; i++) {
      delay(500);
      MyCube.dark();
      delay(500);
      MyCube.show();
      lastSolved = turnNr;
    }
  }
  if (turnsInHist>histMax) turnsInHist = histMax;
  delay(500);
}

void undoLastTurn() {
  byte dir = turnHist[turnNr%histMax]/100;
  byte side = (turnHist[turnNr%histMax]-100*dir)/10;
  byte task = turnHist[turnNr%histMax]-100*dir-10*side;
  if (task == turnSide) {
    MyCube.showTurnSide(side,!dir);
  }
  if (task == turnMid) {
    MyCube.showTurnMid(side,!dir);
  }
  if (task == turnCube) {
    MyCube.showTurnCube(side,!dir);
  }
}


int getTask() {
#ifndef _dutch
  const String Tasks[] = {"Turn side ",
                          "Turn mids ",
                          "Turn cube ",
                          "Undo turn ",
                          "Solve cube"};                             
#else
  const String Tasks[] = {"Draai zijkant",
                          "Draai midden ",
                          "Draai kubus  ",
                          "Draai terug  ",
                          "Los kubus op "};
#endif
                          
  MyOutput.clrscr();
#ifndef _dutch
  MyOutput.txt("Choose task>");
#else
  MyOutput.txt("Kies taak>");
#endif
  MyOutput.nxtln();
  int ans = turnSide;
  MyOutput.txt(Tasks[ans]);
  MyOutput.nxtln();
  while (!confirmed()) {
    int old_ans = ans;
    int userInput = LeftPanel.getOption();
    if (userInput == LeftPanel.arrowUp   || userInput == LeftPanel.arrowRight)   ans++;
    if (userInput == LeftPanel.arrowDown || userInput == LeftPanel.arrowLeft) ans--;
    if (ans==-1)  ans = solveCube;
    if (ans== 5)  ans = turnSide;
    if (ans != old_ans) {
      MyOutput.txt(Tasks[ans]);
      MyOutput.nxtln();
      delay(100);
    }
  }
  MyOutput.nxtln();
  MyOutput.clrscr();
#ifndef _dutch
  MyOutput.txt("Choice= ");
#else
  MyOutput.txt("Keuze= ");
#endif
  MyOutput.nxtln();
  MyOutput.txt(Tasks[ans]);
  delay(1000);
  return ans;
}

 
int getSide() {

#ifndef _dutch                                                   
  const String Txts[]       = {"Turn ",
                               " side"};
  const String SidesTxt[]  = {"ground",
                              "front ",
                              " top  ",                             
                              " back ",
                              " left ",
                              "right "};   
                                                  
#else                                                   
  const String Txts[]       = {"Draai ",
                               "kant"};
                           
  const String SidesTxt[]  = {" onder",                                       
                              "  voor",
                              " boven",
                              "achter",
                              "linker",
                              "rechter"};
#endif
              
  MyOutput.nxtln();
  MyOutput.clrscr();
#ifndef _dutch
  MyOutput.txt("Choose side/axis>");  
#else
  MyOutput.txt("Kies zijkant/as>");  
#endif
  MyOutput.nxtln();
  MyOutput.txt(Txts[0]);  
  int ans = MyCube.frontSide;
  MyOutput.txt(SidesTxt[ans]);
  MyOutput.txt(Txts[1]);  

  while (!confirmed()) {
    if (RightPanel.getOption() == RightPanel.highBut) {
       escFlag = true;
       return;
    }
    int old_ans = ans;
    int userInput = LeftPanel.getOption();
    if (ans > -1 && ans < 4) { 
      if (userInput == LeftPanel.arrowUp) {
         ans++;
         if (ans == 4) {
           ans = MyCube.groundSide;
         }
      } 
      if (userInput == LeftPanel.arrowDown) {
        ans--;
        if (ans == -1) {
          ans = MyCube.backSide;
        }
      } 
      if (userInput == LeftPanel.arrowLeft) {
        ans = MyCube.leftSide;
      }
      if (userInput == LeftPanel.arrowRight) {
        ans = MyCube.rightSide;
      }
    }
    if (ans == MyCube.leftSide) {
      if (userInput == LeftPanel.arrowRight) {
         ans = MyCube.frontSide;
      }
      if (userInput == LeftPanel.arrowUp) {
         ans = MyCube.topSide;
      }
      if (userInput == LeftPanel.arrowDown) {
         ans = MyCube.groundSide;
      }
    }
    if (ans == MyCube.rightSide) { 
      if (userInput == LeftPanel.arrowLeft) {
        ans = MyCube.frontSide;
      }
      if (userInput == LeftPanel.arrowUp) {
         ans = MyCube.topSide;
      }
      if (userInput == LeftPanel.arrowDown) {
         ans = MyCube.groundSide;
      }
    } 
    if (userInput == LeftPanel.arrowCentre) {
       ans = MyCube.frontSide;
    }
    if (ans != old_ans) {
      MyOutput.nxtln();
      MyOutput.txt(Txts[0]);
      MyOutput.txt(SidesTxt[ans]);
      MyOutput.txt(Txts[1]);
      delay(100);
    }
  }
  MyOutput.clrscr();
#ifndef _dutch
  MyOutput.txt("Choice= ");
#else 
  MyOutput.txt("Keuze = ");
#endif
  MyOutput.nxtln();  
  MyOutput.txt(Txts[0]); 
  MyOutput.txt(SidesTxt[ans]);
  MyOutput.txt(Txts[1]);
  delay(1000);
  return ans;
}


bool getDir() {

#ifndef _dutch
  const String DirTxt[]   = {"Left  turn",
                             "Right turn"};
#else
  const String DirTxt[]   = {"Linksom ",
                             "Rechtsom"}; 
#endif                            
  bool CW = 1;
  bool ans = CW;

  MyOutput.clrscr();
#ifndef _dutch
  MyOutput.txt("Choose direction>");
#else
  MyOutput.txt("Kies richting>");
#endif
  MyOutput.nxtln();
  MyOutput.txt(DirTxt[ans]);
  while (!confirmed()) {
    if (RightPanel.getOption() == RightPanel.highBut) {
       escFlag = true;
       return;
    }
    bool old_ans = ans;
    int userInput = LeftPanel.getOption();
    if (userInput != 0) {
      ans = !ans;
    }
    if (ans != old_ans) {
      MyOutput.nxtln();
      MyOutput.txt(DirTxt[ans]);
      delay(100);
    }
  }
  MyOutput.clrscr();
#ifndef _dutch
  MyOutput.txt("Direction=");
#else
  MyOutput.txt("Richting=");
#endif
  MyOutput.nxtln();
  MyOutput.txt(DirTxt[ans]);
  delay(1000);
  return ans;
}


bool confirmed() {
  int UserInput = RightPanel.getOption();
  if (UserInput == RightPanel.lowBut) {
    return 1;
  }
  return 0;
}
