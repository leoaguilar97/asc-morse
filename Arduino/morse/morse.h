#ifndef Morse_h
#define Morse_h
#include <Arduino.h>

#include "Pushbutton.h"
#include "buzzer.h"

Pushbutton pushbutton(2);
Pushbutton button(3);
Buzzer buzzer(13,12);

class Morse{
  public:

    Morse(int start){
        contMorse = start;
        cadena = "";
    }
    
    String obtainWord(){// Obtiene palabra de morse
        if(button.timePress(button.isPressed())==1){
          
            //Serial.println("___-------_"+ret);
            if(cadena == ""){
                return "$";
            }
            String ret = cadena;
            cadena = "";
           // Serial.println("___-------_"+ret);
            return ret;  
        }
        
        cadena += obtainCharacter();
        return "";
    }

    String obtainCharacter(){// Obtiene caracteres de morse 
        if (state == 2){ state = 0; return "?";
        }else if(contMorse==5 || state==1){ state = 0; contMorse = 0; return (String)obtainMorse();}
        
        switch(pushbutton.getState()){
            case 0:
                state = 0;
                time = 0;
                contMillis = millis();
                if(millis()-timeFinalli>5000&&timeFinalli!=0){
                    state = 1;
                    timeFinalli = 0;
                    buzzer.ok();
                }
                break;
  
            case -1:    
                buzzer.reprodusBuzzer();  
                break;
  
            case 3:
                buzzer.fail();
                state = 2;
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
        return "";
    }

    char obtainMorse(){
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
                    return i < 25 ? (char)i+65 : (char)i+23;
                }
            }
        }
    }

  private:
    String cadena;
    int morse[5];
    int contMorse;
    int state;
    long time;
    long contMillis;
    long timeFinalli;
   
};

#endif
