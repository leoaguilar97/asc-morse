#include "buzzer.h"

Buzzer buzzer(13,12);
 
void setup() {
  Serial.begin(9600);
  buzzer.reproducirString("ABC");
}

void loop() {
}
