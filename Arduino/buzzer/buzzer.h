#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"

class Buzzer
{
  public:
    Buzzer(int pin1,int pin2);
    void dot();
    void dash();
  private:
    int _pin1;
    int _pin2;
};

Buzzer::Buzzer(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

#endif