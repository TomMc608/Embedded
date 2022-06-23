#include <FastLED.h>
#define LED_PIN  9
#define NUM_LEDS  54


CRGB leds[NUM_LEDS];



void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);

}


//[6][12][2] = {{{1,7},{1,6},{1,5} side middle and rim

//bool Cube::checkCubeSolved() {
//  for (int curSide = 0; curSide < numSides; curSide++) {    
//    byte sideColor = Color[curSide][0]/10;
//    for (int curPos = 1; curPos < numPos; curPos++) {       
//      if (!(Color[curSide][curPos]/10==sideColor)) return false;  
//    }
//  } 
//  return true;

//void Cube::showTurnCube(int side,bool dir) { 
//  showTurnSide(side,dir);
//  showTurnMid(side,dir);
//  int oppSide = 0;
//  if (side<2) oppSide = side+2;
//  if (side>1 && side<4) oppSide = side-2; 
//  if (side==4) oppSide = 5;
//  if (side==5) oppSide = 4;
//  showTurnSide(oppSide,!dir);
//  delay(delta_t);
//}


//int old_ans = ans;
//    int userInput = LeftPanel.getOption();
//    if (ans > -1 && ans < 4) { 
//      if (userInput == LeftPanel.arrowUp) {
//         ans++;
//         if (ans == 4) {
//           ans = MyCube.groundSide;
//         }
//      } 
//      if (userInput == LeftPanel.arrowDown) {
//        ans--;
//        if (ans == -1) {
//          ans = MyCube.backSide;
//        }
//      } 

void loop() {

  Face1Row1();
  Face1Row2();
  Face1Row3();
  Face2Row1();
  Face2Row2();
  Face2Row3();
  Face3Row1();
  Face3Row2();
  Face3Row3();
  Face4Row1();
  Face4Row2();
  Face4Row3();
  Face5Row1();
  Face5Row2();
  Face5Row3();
  Face6Row1();
  Face6Row2();
  Face6Row3();

  Face1Column1();
  Face1Column2();
  Face1Column3();
  delay(1000);
  Face2Column1();
  Face2Column2();
  Face2Column3();
  delay(1000);
  Face3Column1();
  Face3Column2();
  Face3Column3();
  delay(1000);
  Face4Column1();
  Face4Column2();
  Face4Column3();
  delay(1000);
  Face5Column1();
  Face5Column2();
  Face5Column3();
  delay(1000);
  Face6Column1();
  Face6Column2();
  Face6Column3();
}

void Face1Row1() {
  for (int i = 0; i <= 2; i++) {
    leds[i] = CRGB (255, 0, 0);
    FastLED.show();

  }
}

void Face1Row2() {
  for (int i = 3; i <= 5; i++) {
    leds[i] = CRGB (255, 0, 0);
    FastLED.show();

  }
}

void Face1Row3() {
  for (int i = 6; i <= 8; i++) {
    leds[i] = CRGB (255, 0, 0);
    FastLED.show();

  }
}

//----------------------------------------

void Face2Row1() {
  for (int i = 9; i <= 11; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();

  }
}

void Face2Row2() {
  for (int i = 12; i <= 14; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();

  }
}

void Face2Row3() {
  for (int i = 15; i <= 17; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();

  }
}
void Face3Row1() {
  for (int i = 18; i <= 20; i++) {
    leds[i] = CRGB (255, 255, 0);
    FastLED.show();

  }
}

void Face3Row2() {
  for (int i = 21; i <= 23; i++) {
    leds[i] = CRGB (255, 255, 0);
    FastLED.show();

  }
}

void Face3Row3() {
  for (int i = 24; i <= 26; i++) {
    leds[i] = CRGB (255, 255, 0);
    FastLED.show();

  }
}

//----------------------------------------
void Face4Row1() {
  for (int i = 27; i <= 29; i++) {
    leds[i] = CRGB (0, 0, 255);
    FastLED.show();

  }
}

void Face4Row2() {
  for (int i = 30; i <= 32; i++) {
    leds[i] = CRGB (0, 0, 255);
    FastLED.show();

  }
}

void Face4Row3() {
  for (int i = 33; i <= 35; i++) {
    leds[i] = CRGB (0, 0, 255);
    FastLED.show();

  }
}

//----------------------------------------
void Face5Row1() {
  for (int i = 36; i <= 38; i++) {
    leds[i] = CRGB (255, 165, 0);
    FastLED.show();

  }
}

void Face5Row2() {
  for (int i = 39; i <= 41; i++) {
    leds[i] = CRGB (255, 165, 0);
    FastLED.show();

  }
}

void Face5Row3() {
  for (int i = 42; i <= 44; i++) {
    leds[i] = CRGB (255, 165, 0);
    FastLED.show();

  }
}

//----------------------------------------
void Face6Row1() {
  for (int i = 45; i <= 47; i++) {
    leds[i] = CRGB (0, 255, 0);
    FastLED.show();

  }
}

void Face6Row2() {
  for (int i = 48; i <= 50; i++) {
    leds[i] = CRGB (0, 255, 0);
    FastLED.show();

  }
}

void Face6Row3() {
  for(int i = 51; i <= 53; i++){
  leds[i] = CRGB (0, 255, 0);
  FastLED.show();
  }

}


//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



void Face1Column1() {
  int x = 0; int y = 3; int z = 6;
  leds[x] = CRGB (255, 0, 0);
  leds[y] = CRGB (255, 0, 0);
  leds[z] = CRGB (128, 0, 0);
  FastLED.show();

  
}

void Face1Column2() {
  int x = 1; int y = 4; int z = 7;
  leds[x] = CRGB (255, 0, 0);
  leds[y] = CRGB (255, 0, 0);
  leds[z] = CRGB (255, 0, 0);
  FastLED.show();
}

void Face1Column3() {
  int x = 2; int y = 5; int z = 8;
  leds[x] = CRGB (255, 0, 0);
  leds[y] = CRGB (255, 0, 0);
  leds[z] = CRGB (255, 0, 0);
  FastLED.show();
}

//----------------------------------------

void Face2Column1() {
  int x = 9; int y = 12; int z = 15;
  leds[x] = CRGB (255, 255, 255);
  leds[y] = CRGB (255, 255, 255);
  leds[z] = CRGB (255, 255, 255);
  FastLED.show();
}

void Face2Column2() {
 int x = 10; int y = 13; int z = 16;
  leds[x] = CRGB (255, 255, 255);
  leds[y] = CRGB (255, 255, 255);
  leds[z] = CRGB (255, 255, 255);
  FastLED.show();
}

void Face2Column3() {
 int x = 11; int y = 14; int z = 17;
  leds[x] = CRGB (255, 255, 255);
  leds[y] = CRGB (255, 255, 255);
  leds[z] = CRGB (255, 255, 255);
  FastLED.show();
}

//-------------------------------------
void Face3Column1() {
 int x = 18; int y = 21; int z = 24;
  leds[x] = CRGB (255, 255, 0);
  leds[y] = CRGB (255, 255, 0);
  leds[z] = CRGB (255, 255, 0);
  FastLED.show();
}

void Face3Column2() {
 int x = 19; int y = 22; int z = 25;
  leds[x] = CRGB (255, 255, 0);
  leds[y] = CRGB (255, 255, 0);
  leds[z] = CRGB (255, 255, 0);
  FastLED.show();
}

void Face3Column3() {
 int x = 20; int y = 23; int z = 26;
  leds[x] = CRGB (255, 255, 0);
  leds[y] = CRGB (255, 255, 0);
  leds[z] = CRGB (255, 255, 0);
  FastLED.show();
}
//
////----------------------------------------
void Face4Column1() {
 int x = 27; int y = 30; int z = 33;
  leds[x] = CRGB (0, 0, 255);
  leds[y] = CRGB (0, 0, 255);
  leds[z] = CRGB (0, 0, 255);
  FastLED.show();
}

void Face4Column2() {
 int x = 28; int y = 31; int z = 34;
  leds[x] = CRGB (0, 0, 255);
  leds[y] = CRGB (0, 0, 255);
  leds[z] = CRGB (0, 0, 255);
  FastLED.show();
}

void Face4Column3() {
 int x = 29; int y = 32; int z = 35;
  leds[x] = CRGB (0, 0, 255);
  leds[y] = CRGB (0, 0, 255);
  leds[z] = CRGB (0, 0, 255);
  FastLED.show();
}
//
////----------------------------------------
void Face5Column1() {
 int x = 36; int y = 39; int z = 42;
  leds[x] = CRGB (255, 165, 0);
  leds[y] = CRGB (255, 165, 0);
  leds[z] = CRGB (255, 165, 0);
  FastLED.show();
}

void Face5Column2() {
 int x = 37; int y = 40; int z = 43;
  leds[x] = CRGB (255, 165, 0);
  leds[y] = CRGB (255, 165, 0);
  leds[z] = CRGB (255, 165, 0);
  FastLED.show();
}

void Face5Column3() {
 int x = 38; int y = 41; int z = 44;
  leds[x] = CRGB (255, 165, 0);
  leds[y] = CRGB (255, 165, 0);
  leds[z] = CRGB (255, 165, 0);
  FastLED.show();
}
//
////----------------------------------------
void Face6Column1() {
  int x = 45; int y = 48; int z = 51;
  leds[x] = CRGB (0, 255, 0);
  leds[y] = CRGB (0, 255, 0);
  leds[z] = CRGB (0, 255, 0);
  FastLED.show();
}

void Face6Column2() {
 int x = 46; int y = 49; int z = 52;
  leds[x] = CRGB (0, 255, 0);
  leds[y] = CRGB (0, 255, 0);
  leds[z] = CRGB (0, 255, 0);
  FastLED.show();
}

void Face6Column3() {
  int x = 47; int y = 50; int z = 53;
  leds[x] = CRGB (0, 255, 0);
  leds[y] = CRGB (0, 255, 0);
  leds[z] = CRGB (0, 255, 0);
  FastLED.show();
}
