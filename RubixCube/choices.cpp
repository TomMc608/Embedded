/*
  Choices.h - Library for multiple choice via analog input
  Created by Koen Meesters, February 21st 2019
  Last edited by Koen Meesters, February 21st 2019
*/

#include "Arduino.h"
#include "choices.h"

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
