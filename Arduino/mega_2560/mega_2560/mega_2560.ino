#include "debugging.h"
#include "buzzer.h"
#include "leds.h"
#include "processor.h"
#include "communication.h"

Buzzer buzzer(35, 36);

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println(">> Inicio controlador mega_2560");
  
  m.init(); // module initialize
  m.setIntensity(15); // dot matix intensity 0-15

  setup_leds();
}
/*
void loop() {
  printEduc8s();
  //Revisar si hay un valor enviado por el modulo WiFi
  //de ser asi, procesarlo, de lo contrario, volver a esperar
  //recieveString();
}
*/
