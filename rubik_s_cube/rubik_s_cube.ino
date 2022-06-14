#include <FastLED.h>
#define LED_PIN  9
#define NUM_LEDS  54


CRGB leds[NUM_LEDS];

int C1F1 [] = {0, 1, 2};
int C2F1 [] = {3, 4, 5};
int C3F1 [] = {6, 7, 8};

int C1F2 [] = {9, 10, 11};
int C2F2 [] = {12, 13, 14};
int C3F2 [] = {15, 16, 17};

int C1F3 [] = {18, 19, 20};
int C2F3 [] = {21, 22, 23};
int C3F3 [] = {24, 25, 26};

int C1F4 [] = {27, 28, 29};
int C2F4 [] = {30, 31, 32};
int C3F4 [] = {33, 34, 35};

int C1F5 [] = {36, 37, 38};
int C2F5 [] = {39, 40, 41};
int C3F5 [] = {42, 43, 44};

int C1F6 [] = {45, 46, 47};
int C2F6 [] = {48, 49, 50};
int C3F6 [] = {51, 52, 53};

//-------------------------------------------------

int R1F1 [] = {0, 3, 6};
int R2F1 [] = {1, 4, 7};
int R3F1 [] = {2, 5, 8};

int R1F2 [] = {9, 12, 15};
int R2F2 [] = {10, 13, 16};
int R3F2 [] = {11, 14, 17};

int R1F3 [] = {18, 21, 24};
int R2F3 [] = {19, 22, 25};
int R3F3 [] = {20, 23, 26};

int R1F4 [] = {27, 30, 33};
int R2F4 [] = {28, 31, 34};
int R3F4 [] = {29, 32, 35};

int R1F5 [] = {36, 39, 42};
int R2F5 [] = {37, 40, 43};
int R3F5 [] = {38, 41, 44};

int R1F6 [] = {45, 48, 51};
int R2F6 [] = {46, 49, 52};
int R3F6 [] = {47, 50, 53};

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);

}

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
  int x = 52; int y = 53; int z = 54;
  leds[x] = CRGB (128, 0, 0);
  leds[y] = CRGB (128, 0, 0);
  leds[z] = CRGB (128, 0, 0);
  FastLED.show();

}


//-------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------



void Face1Column1() {
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

void Face1Column3() {
  for (int i = 6; i <= 8; i++) {
    leds[i] = CRGB (255, 0, 0);
    FastLED.show();

  }
}

//----------------------------------------

void Face2Column1() {
  for (int i = 9; i <= 11; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();

  }
}

void Face2Column2() {
  for (int i = 12; i <= 14; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();

  }
}

void Face2Column3() {
  for (int i = 15; i <= 17; i++) {
    leds[i] = CRGB (255, 255, 255);
    FastLED.show();

  }
}
void Face3Column1() {
  for (int i = 18; i <= 20; i++) {
    leds[i] = CRGB (255, 255, 0);
    FastLED.show();

  }
}

void Face3Column2() {
  for (int i = 21; i <= 23; i++) {
    leds[i] = CRGB (255, 255, 0);
    FastLED.show();

  }
}

void Face3Column3() {
  for (int i = 24; i <= 26; i++) {
    leds[i] = CRGB (255, 255, 0);
    FastLED.show();

  }
}

//----------------------------------------
void Face4Column1() {
  for (int i = 27; i <= 29; i++) {
    leds[i] = CRGB (0, 0, 255);
    FastLED.show();

  }
}

void Face4Column2() {
  for (int i = 30; i <= 32; i++) {
    leds[i] = CRGB (0, 0, 255);
    FastLED.show();

  }
}

void Face4Column3() {
  for (int i = 33; i <= 35; i++) {
    leds[i] = CRGB (0, 0, 255);
    FastLED.show();

  }
}

//----------------------------------------
void Face5Column1() {
  for (int i = 36; i <= 38; i++) {
    leds[i] = CRGB (255, 165, 0);
    FastLED.show();

  }
}

void Face5Column2() {
  for (int i = 39; i <= 41; i++) {
    leds[i] = CRGB (255, 165, 0);
    FastLED.show();

  }
}

void Face5Column3() {
  for (int i = 42; i <= 44; i++) {
    leds[i] = CRGB (255, 165, 0);
    FastLED.show();

  }
}

//----------------------------------------
void Face6Column1() {
  for (int i = 45; i <= 47; i++) {
    leds[i] = CRGB (0, 255, 0);
    FastLED.show();

  }
}

void Face6Column2() {
  for (int i = 48; i <= 50; i++) {
    leds[i] = CRGB (0, 255, 0);
    FastLED.show();

  }
}

void Face6Column3() {
  for (int i = 51; i <= 53; i++) {
    leds[i] = CRGB (0, 255, 0);
    FastLED.show();

  }
}

* /
