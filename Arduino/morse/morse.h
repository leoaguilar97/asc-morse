#ifndef Morse_h
#define Morse_h
#include <Arduino.h>
#include "Pushbutton.h"
#include "buzzer.h"

Pushbutton pushbutton(2);
Buzzer buzzer(13,12);

class Morse{
public:
    String obtainCharacter(){
        if (state){ state = 0; return "?";
        }else if(contMorse == 5){ contMorse = 0; return obtainMorse()}
        
        switch(pushbutton.getState()){
            case 0:
                state = 0;
                time = 0;
                contMillis = millis();
                if(milliss()-timeFinalli>5000&&timeFinalli!=0){
                    state = 1;
                    timeFinalli = 0;
                }
                break;
  
            case -1:          
                time += millis() - contMillis;
                if(time>2000){
                    state = 1;
                    buzzer.fail();
                }
                break;
  
            case 3:
                buzzer.fail();
                state = 1;
                break;
            
            case 1:
                morse[contMorse] = 1;
                contMorse++;
                buzzer.ok();
                timeFinalli = millis();
                break;
        
            case 2:
                morse[contMorse] = 2;
                contMorse++;
                buzzer.ok();
                timeFinalli = millis();
            break;
        }
    }

    String obtainMorse(){
        for(int i=0;i<36;i++){
            for(int j=0;j<5;j++){
                if(buzzer.letrasMorse[i][j] != morse[j]){
                    break;
                }
                if(j==4){
                    morse[0] = 0;
                    morse[1] = 0;
                    morse[2] = 0;
                    morse[3] = 0;
                    morse[4] = 0;
                    return i <25 ? i+65:i+23;
                }
            }
        }
    }

private:
  int morse[5];
  int contMorse;
  int state;
  long time;
  long contMillis;
  long timeFinalli;
 
};

#endif
