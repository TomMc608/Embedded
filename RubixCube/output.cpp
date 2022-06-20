
#include "Arduino.h"
#include "output.h"

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);


Output::Output(bool serial, bool cryst) {
  lcd.begin(16,2);
  _serial = serial;
  _cryst  = cryst;
}

void Output::clrscr() {          //clear screen (go to next line in Serial output)
  if (_serial) {
    Serial.println();
  }
  if (_cryst) {
    lcd.clear();
  }
}

void Output::txt(String text) {   //write text
  if (_serial) {
    Serial.print(text);     
  }
  if (_cryst) { 
    lcd.print(text);
  }
}

void Output::nxtln() {             //go to next line
  if (_serial) {
    Serial.println();
  }
  if (_cryst) { 
    lcd.setCursor(0,1);
  }
}
