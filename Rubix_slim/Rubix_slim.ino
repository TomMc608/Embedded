#include "x.h"
#include <LiquidCrystal.h>
#include <PololuLedStrip.h>

Choices LeftPanel(A5, 5);
Choices RightPanel(A4, 3);
Cube MyCube(3);           
Output MyOutput(false, true); 


void setup() {
  Serial.begin(9600);
  delay(500);
  MyCube.show();
  delay(500);
  MyOutput.clrscr();

  MyOutput.txt("Hello there!");
  MyOutput.clrscr();
}



const int turnSide  = 0;
const int turnMid   = 1;
const int turnCube  = 2;
const int undoLast  = 3;
const int solveCube = 4;

const bool CW = true;

const int histMax = 30;    
int turnNr      = 0;          
int lastSolved  = 0;      
int turnsInHist = 0;       
byte turnHist[histMax];

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
          MyOutput.txt("Cannot undo");


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
        MyOutput.txt("Undo another");
        MyOutput.nxtln(); 
        MyOutput.txt("turn?");


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
      if ((turnsInHist == 0) || ((turnNr-lastSolved)>turnsInHist)) { 
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
MyOutput.txt("Cube solved!");


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
  const String Tasks[] = {"Turn side ",
                          "Turn mids ",
                          "Turn cube ",
                          "Undo turn ",
                          "Solve cube"};                             


                          
  MyOutput.clrscr();
  MyOutput.txt("Choose task>");
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
  MyOutput.txt("Choice= ");
  MyOutput.nxtln();
  MyOutput.txt(Tasks[ans]);
  delay(1000);
  return ans;
}

 
int getSide() {
                                                
  const String Txts[]       = {"Turn ",
                               " side"};
  const String SidesTxt[]  = {"ground",
                              "front ",
                              " top  ",                             
                              " back ",
                              " left ",
                              "right "};   
                                                  
              
  MyOutput.nxtln();
  MyOutput.clrscr();
  MyOutput.txt("Choose side/axis>");  
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
  MyOutput.txt("Choice= ");
  MyOutput.nxtln();  
  MyOutput.txt(Txts[0]); 
  MyOutput.txt(SidesTxt[ans]);
  MyOutput.txt(Txts[1]);
  delay(1000);
  return ans;
}


bool getDir() {

  const String DirTxt[]   = {"Left  turn",
                             "Right turn"};
                         
  bool CW = 1;
  bool ans = CW;

  MyOutput.clrscr();
  MyOutput.txt("Choose direction>");
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
  MyOutput.txt("Direction=");
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
