
#include <Arduino.h>

#include "debugging.h"
#include "buzzer.h"
#include "buttons.h"
#include "processor.h"
#include "communication.h"
#include "io_control.h"

//setup del arduino
void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println(">> Inicio controlador mega_2560");

  setupIO();
}

//procesar el estado del sistema actual
void processState() {
  switch (currentState()) {
    case START: {
        //Funcion que muestra HOLA GRUPO #1 en la pantalla, se encuentra en io_control.h
        displayCycle();
      } break;

    case RECIEVING: {
        //Funcion que muestra el texto recibido por el modulo esp2866 en la pantalla, se encuentra en io_control.h
        //el parametro true implica que el string recibido se traducira a morse antes de utilizarse
        displayCycle(true);
      } break;

    case WRITING: {
        loopSystem(recieveString);
      } break;

    case PLAYING: {
        loopSystem(recieveString);
      } break;
  }
}

//funcion que revisara si se presiono el boton de cambio de estado
//si cambia el estado, se cambiara a otro modo del sistema en modo ciclico
bool checkStateChanged() {
  //Si el boton de cambio de estado (pin 22) fue presionado
  if (btnChangeState.pressed()) {
    debug(String("Cambiando estado del sistema"));

    change_state();

    //reiniciar la pantalla y el texto
    if (currentState() == START) {
      setText(String("HOLA GRUPO #1"));
    } else {
      clearText();
    }

    return true;
  }

  return false;
}

//Realizar un ciclo del sistema, retornara false si el sistema sigue en el mismo estado,
//retornara true si el sistema tuvo un cambio en el sistema (cambio de modo)
bool loopSystem(
  //funcion que procesara el ingreso de un string al sistema
  bool (*process_fnc)(String val)
) {
  //revisar si el sistema tuvo un cambio en su estado
  return
    //revisar si hubo un cambio en el modo del sistema
    checkStateChanged() ? true :
    //revisar si algo fue enviado por el puerto serial (esp2866)
    recieveString(process_fnc);
}

void loop() {
  processState();
  delay(100);
}
