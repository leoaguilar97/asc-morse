#ifndef MorseGame_h
#define MorseGame_h
#include <Arduino.h>

#include "Pushbutton.h"
#include "buzzer.h"

Pushbutton pushbutton(2);//boton para ingresar morse
Pushbutton button(3);//boton para regresar palabra
Buzzer buzzer(13,12);

class MorseGame{
  public:

    MorseGame(int start){
      start = 1;
    }

    int startGame(String text){
      for(int i=0;i<10;i++){
        if(obtainCharacter(2000) == text.charAt(i)){
          score += 1;
        }
      }
      int ret = score;
      return ret;
    }
  

  private:
    String cadena;
    int score;
   
};

#endif
