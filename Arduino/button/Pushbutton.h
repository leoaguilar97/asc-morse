#ifndef Pushbutton_h
#define Pushbutton_h
#include <Arduino.h>

class Pushbutton{
public:
  Pushbutton(int pin){ 
    pinMode(pin, INPUT);
    _pin = pin;
    state = 0;
  }

  int getState(){
    if(getTimePressed(isPressed())){
      if (999<time<1499){ return 1; 
      } else if (2999<time<3499){ return 2; 
      } else{ return 3; 
      }
    }
    return -1;
  }

private:
  int _pin;
  int state;
  long time;
  long contMillis;
  
  int timePress(bool value){// Devuelve true y se almacena en la variable time el tiempo que etuvo presionado el boton
    switch (state){
    case 0:
      // Si el valor es falso, proceda al siguiente state.
      if (value){
        contMillis = millis();
        time = 0;
        state = 1;
      }
      break;

    case 1:
      time += millis() - contMillis;
      if (value){
        // El valor es falso o rebota, así que regrese al anterior (inicial)
        state = 0;
      }
      else if (time >= 15){
        // Han pasado al menos 15 ms y el valor sigue siendo verdadero, por lo que pasa al siguiente state.
        state = 2;
      }
      break;

    case 2:    
      time += millis() - contMillis;
      // Si el valor es verdadero, contina con el siguiente estado.
      if (!value){
        state = 3;
      }
      break;

    case 3:
      state = 0;
      return true;
    }
    
    return false;
  }

  bool isPressed(){// Indica si el boton se encuentra presionado
    return digitalRead(_pin) == 1;
  }
};

#endif
