  #include "morse.h"

#include <Arduino.h>

Morse morse(0);
void setup() {
  Serial.begin(9600);
}

void loop() {
  morse.obtainCharacter();
}
