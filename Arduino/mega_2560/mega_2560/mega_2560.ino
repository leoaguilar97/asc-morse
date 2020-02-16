#include "debugging.h"
#include "buzzer.h"
#include "processor.h"
#include "communication.h"
#include "io_control.h"

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println(">> Inicio controlador mega_2560");
  
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
