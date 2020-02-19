#ifndef buttons_h
#define buttons_h

//Clase que se utiliza para crear controladores de botones
//se obtiene si un boton fue presionado en la funcion "pressed"
class PushButton {
  public:

    PushButton(int pin) {
      pinMode(pin, INPUT);
      buttonPin = pin;
      state = 0;
    }

    //Obtiene el estado del boton
    int getState() {
      switch (!pressed()) {
        case 0: // El boton esta presionado
          return -1;

        case 1: // Se suelta el boton
          if (15 < timePressButton && timePressButton < 1000) {
            return 1;
          } else if (1001 < timePressButton && timePressButton < 3499) {
            return 2;
          }
          return 3;

        case 2: // El boton no hace nada
          return 0;
      }
    }

    //Obtiene si el boton esta presionado
    bool pressed() {

      bool p = false;
      long milsel = millis();

      //check 10 times for a change
      while (!p && millis() - milsel <= 100) {
        p = !timePress(isPressed() == 1);
        delay(10);
      }

      if (p) {
        delay(1000);
      }
    
      return !timePress(isPressed() == 1);
    }

  private:
    int buttonPin;
    int state;
    long timePressButton;
    long contMillis;

    // Devuelve true y se almacena en la variable time el tiempo que etuvo presionado el boton
    int timePress(bool value) {
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
          else if (timePressButton >= 50) {
            // Han pasado al menos 50 ms y el valor sigue siendo verdadero, por lo que pasa al siguiente state.
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

    // Indica si el boton se encuentra presionado
    bool isPressed() {
      return digitalRead(buttonPin) == 1;
    }
};


PushButton btnChangeState(22);  //boton para cambiar el estado del sistema
PushButton btnInsMorse(24);     //boton para ingresar morse
PushButton btnConfirmWord(25);  //boton para regresar palabra
#endif
