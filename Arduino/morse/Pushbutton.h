#ifndef buttons_h
#define buttons_h

#include <Arduino.h>

class Pushbutton {
  public:
    Pushbutton(int pin) {
      pinMode(pin, INPUT);
      _pin = pin;
      state = 0;
    }

    int getState() {
      switch (pressed()) {
        case 0: // El boton esta presionado
          return -1;

        case 1: // Se suelta el boton
          if (15 < timePressButton && timePressButton < 500) {
            return 1;
          } else if (501 < timePressButton && timePressButton < 3499) {
            return 2;
          }
          return 3;

        case 2: // El boton no hace nada
          return 0;
      }
    }

    bool pressed(){
      return timePress(isPressed());
    }

  private:
    int _pin;
    int state;
    long timePressButton;
    long contMillis;

    int timePress(bool value) { // Devuelve true y se almacena en la variable time el tiempo que etuvo presionado el boton
      switch (state) {
        case 0:
          // Si el valor es verdadero, proceda al siguiente state.
          if (value) {
            contMillis = millis();
            timePressButton = 0;
            state = 1;
          }
          return 2;

        case 1:
          timePressButton = millis() - contMillis;
          if (!value) {
            // El valor es falso o rebota, así que regrese al anterior (inicial)
            state = 0;
          }
          else if (timePressButton >= 15) {
            // Han pasado al menos 15 ms y el valor sigue siendo verdadero, por lo que pasa al siguiente state.
            state = 2;
          }
          return 2;

        case 2:
          timePressButton = millis() - contMillis;
          // Si el valor es verdadero, contina con el siguiente estado.
          if (!value) {
            state = 3;
          }
          return 0;

        case 3:
          state = 0;
          return 1;
      }

      return 2;
    }
    
<<<<<<< HEAD
    return 2;
  }

  bool isPressed(){// Indica si el boton se encuentra presionado
    return digitalRead(_pin) == 1;
  }
  
private:
  int _pin;
  int state;
  long timePressButton;
  long contMillis;
  
=======
    bool isPressed() { // Indica si el boton se encuentra presionado
      return digitalRead(_pin) == 1;
    }
>>>>>>> f64ece3c452d0134c2be06bb68ff288b40c9974a
};

#endif
