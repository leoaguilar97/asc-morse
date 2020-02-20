#ifndef Morse_h
#define Morse_h

//Clase que recibe una entrada de pulsos por un boton
//y la decodifica para generar strings a partir del codigo
//morse ingresado
class Morse {
  public:
    //constructor del juego
    Morse() {
      morseIndex = 0;
      raw_string = "";
      state = 0;
    }

    // Agrega caracteres a la raw_string hasta que se presiona el boton de confirmado
    String getWord() {
      if (btnConfirmWord.pressed()) {
        if (raw_string == "") {
          return " ";
        }
        String ret = raw_string;
        raw_string = "";
        return ret;
      }

      raw_string += getStringChar(2000);
      
      return "";
    }

    // Obtiene un caracter codificado en morse y lo retorna como un String
    String getStringChar(int waitTime) {
      if (state == 2|| morseIndex == 5) {
        state = 0; 
        morseIndex = 0;
        timeFinalli = 0;
        buzzer.fail();
        return "?";
      } else if (state == 1) {
        state = 0;
        morseIndex = 0;
        return (String)getMorse();
      }

      switch (btnInsMorse.getState()) {
        case 0:
          state = 0;
          time = 0;
          contMillis = millis();
          if (millis() - timeFinalli > waitTime && timeFinalli != 0) {
            state = 1;
            timeFinalli = 0;
            buzzer.ok();
            return "";
          }
          break;

        case -1:
          buzzer.replayBuzzerVal();
          break;

        case 3:
          state = 2;
          buzzer.offBuzzer();
          break;

        case 1:
          morse[morseIndex] = 1;
          morseIndex++;
          timeFinalli = millis();
          buzzer.offBuzzer();
          break;

        case 2:
          morse[morseIndex] = 2;
          morseIndex++;
          timeFinalli = millis();
          buzzer.offBuzzer();
          break;
      }

      return "";
    }

    //Obtiene la representacion de morse de un caracter
    char getMorse() {
      for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 5; j++) {
          if (buzzer.morse_map[i][j] != morse[j]) {
            break;
          }
          if (j == 4) {
            morse[0] = 0;
            morse[1] = 0;
            morse[2] = 0;
            morse[3] = 0;
            morse[4] = 0;
            return i < 25 ? (char)i + 65 : (char)i + 22;
          }
        }
      }

      buzzer.fail();
      return '-';
    }

  private:
    String raw_string;
    int morse[5];
    int morseIndex;
    int state;
    long time;
    long contMillis;
    long timeFinalli;

};

Morse morse;

#endif
