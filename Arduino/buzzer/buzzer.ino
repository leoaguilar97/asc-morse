#include "buzzer.h"

Buzzer buzzer(13,12);
 
void setup() {
  Serial.begin(9600);
  buzzer.reproducirString("HOLAMUNDO");
  //buzzer.fail();
  //buzzer.ok();
  //buzzer.settiempoPausaLetra(1500);
  //buzzer.settiempoPausaSonido(400);
}

void loop() {
}
