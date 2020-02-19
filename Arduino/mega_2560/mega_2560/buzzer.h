#ifndef Buzzer_h
#define Buzzer_h
#include <Arduino.h>

class Buzzer
{
  public:

    int morse_map[36][5];

    Buzzer(int pin1, int pin2) { //pin1 = sonido y pin2 = encender y apagar buzer.
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);

      power_pin = pin1;
      onOff = pin2;
      instanciacurrent_chares();
      pauseTime = 400;
      intervalTime = 150;
      replayBuzzer = 0;
    }

    void ok() { //Sonido de ok.
      playMorseCharSound(100, 1);
      pausa(50);
      playMorseCharSound(100, 1);
    }

    void offBuzzer() { //Apagar buzzer
      digitalWrite(onOff, LOW);
    }

    void fail() { //Sonido de falla.
      playMorseCharSound(700, 1);
      pausa(50);
      playMorseCharSound(100, 1);
    }

    void playPoint() { //Sonido de playPoint.
      playMorseCharSound(100, 0);
    }

    void playDash() { //Sonido de playDash.
      playMorseCharSound(400, 0);
    }

    void setInterval(int tiempo) { //Cambial el tiempo de la pausa entre letras. Tiempo por defecto de 3000 milisegundos.
      intervalTime = tiempo;
    }

    void setPauseTime(int tiempo) { //Cambial el tiempo de la pausa entre playPoints o playDashs. Tiempo por defecto de 1000 milisegundos.
      pauseTime = tiempo;
    }

    //Obtiene la representacion de una raw_string ASCII en morse
    String getMorseString(String raw_string) {
      String result = "";

      debug(String("Convirtiendo raw_string a morse: ") + raw_string);

      for (int c = 0; c < raw_string.length(); c++) {
        int current_char = -1;

        if (raw_string.charAt(c) == ' ') {
          result += " ^ ";
          continue;
        }
        else if (raw_string.charAt(c) > 64 && raw_string.charAt(c) < 91) {
          current_char = raw_string.charAt(c) - 65;
        }
        else if (raw_string.charAt(c) > 47 && raw_string.charAt(c) < 58) {
          current_char = raw_string.charAt(c) - 22;
        }
        else {
          continue;
        }

        for (int i = 0; i < 5; i++) {
          if (morse_map[current_char][i] == 0)
            break;
          else if (morse_map[current_char][i] == 1)
            result += ".";
          else
            result += "_";
        }

        result += " ";
      }

      result += " $ ";

      return result;
    }

    //Realiza el sonido de un punto o raya, dependiendo del parametro
    void playDashOrPoint(char morse) {
      if (morse == '.') {
        playPoint();
      } else if (morse == '_') {
        playDash();
      } else {
        pauseLetter();
        return;
      }
      pauseSound();
    }

    //Recorre un string codificado en morse para reproducirlo
    void playMorseString(String morse) {
      for (int i = 0; i < morse.length(); i++) {
        playDashOrPoint(morse.charAt(i));
      }
    }

    //Se reproduce texto en morse.
    void playAsciiString(String raw_string) {
      playMorseString(getMorseString(raw_string));
    }

    void replayBuzzerVal() {
      digitalWrite(onOff, HIGH);
      digitalWrite(power_pin, HIGH);
      digitalWrite(power_pin, LOW);
    }

  private:
    int power_pin;
    int onOff;
    int pauseTime;
    int intervalTime;
    int replayBuzzer;

    void pauseSound() { //Pausa entre los pitidos.
      pausa(pauseTime);
    }

    void pauseLetter() { //Pausa entre letras.
      pausa(intervalTime);
    }

    void pausa(int tiempo) { //Crea las pausas (metodo llamado por pauseSound y pauseLetter).
      long contador = millis();
      while (contador + tiempo > millis()) {
        ;
      }
    }

    void playMorseCharSound(int tiempo, int sonido) { //Crea los sonidos de playPoints o playDashs.
      long contador = millis();
      long frecuencia = 0;

      digitalWrite(onOff, HIGH);

      while (contador + tiempo > millis()) {
        if (frecuencia < millis()) {
          digitalWrite(power_pin, HIGH);
          frecuencia = millis() + sonido;
        }
        else {
          digitalWrite(power_pin, LOW);
        }
      }
      digitalWrite(onOff, LOW);
    }

    void instanciacurrent_chares() { //Se instancian la matriz con los current_chares a utilizar.
      //A
      morse_map[0][0] = 1;
      morse_map[0][1] = 2;

      //B
      morse_map[1][0] = 2;
      morse_map[1][1] = 1;
      morse_map[1][2] = 1;
      morse_map[1][3] = 1;

      //C
      morse_map[2][0] = 2;
      morse_map[2][1] = 1;
      morse_map[2][2] = 2;
      morse_map[2][3] = 1;

      //D
      morse_map[3][0] = 2;
      morse_map[3][1] = 1;
      morse_map[3][2] = 1;

      //E
      morse_map[4][0] = 1;

      //F
      morse_map[5][0] = 1;
      morse_map[5][1] = 1;
      morse_map[5][2] = 2;
      morse_map[5][3] = 1;

      //G
      morse_map[6][0] = 2;
      morse_map[6][1] = 2;
      morse_map[6][2] = 1;

      //H
      morse_map[7][0] = 1;
      morse_map[7][1] = 1;
      morse_map[7][2] = 1;
      morse_map[7][3] = 1;

      //I
      morse_map[8][0] = 1;
      morse_map[8][1] = 1;

      //J
      morse_map[9][0] = 1;
      morse_map[9][1] = 2;
      morse_map[9][2] = 2;
      morse_map[9][3] = 2;

      //K
      morse_map[10][0] = 2;
      morse_map[10][1] = 1;
      morse_map[10][2] = 2;

      //L
      morse_map[11][0] = 1;
      morse_map[11][1] = 2;
      morse_map[11][2] = 1;
      morse_map[11][3] = 1;

      //M
      morse_map[12][0] = 2;
      morse_map[12][1] = 2;

      //N
      morse_map[13][0] = 2;
      morse_map[13][1] = 1;

      //O
      morse_map[14][0] = 2;
      morse_map[14][1] = 2;
      morse_map[14][2] = 2;

      //P
      morse_map[15][0] = 1;
      morse_map[15][1] = 2;
      morse_map[15][2] = 2;
      morse_map[15][3] = 1;

      //Q
      morse_map[16][0] = 2;
      morse_map[16][1] = 2;
      morse_map[16][2] = 1;
      morse_map[16][3] = 2;

      //R
      morse_map[17][0] = 1;
      morse_map[17][1] = 2;
      morse_map[17][2] = 1;

      //S
      morse_map[18][0] = 1;
      morse_map[18][1] = 1;
      morse_map[18][2] = 1;

      //T
      morse_map[19][0] = 1;

      //U
      morse_map[20][0] = 1;
      morse_map[20][1] = 1;
      morse_map[20][2] = 2;

      //V
      morse_map[21][0] = 1;
      morse_map[21][1] = 1;
      morse_map[21][2] = 1;
      morse_map[21][3] = 2;

      //W
      morse_map[22][0] = 1;
      morse_map[22][1] = 2;
      morse_map[22][2] = 2;

      //X
      morse_map[23][0] = 2;
      morse_map[23][1] = 1;
      morse_map[23][2] = 1;
      morse_map[23][3] = 2;

      //Y
      morse_map[24][0] = 2;
      morse_map[24][1] = 1;
      morse_map[24][2] = 2;
      morse_map[24][3] = 2;

      //Z
      morse_map[25][0] = 2;
      morse_map[25][1] = 2;
      morse_map[25][2] = 1;
      morse_map[25][3] = 1;

      //0
      morse_map[26][0] = 2;
      morse_map[26][1] = 2;
      morse_map[26][2] = 2;
      morse_map[26][3] = 2;
      morse_map[26][4] = 2;

      //1
      morse_map[27][0] = 1;
      morse_map[27][1] = 2;
      morse_map[27][2] = 2;
      morse_map[27][3] = 2;
      morse_map[27][4] = 2;

      //2
      morse_map[28][0] = 1;
      morse_map[28][1] = 1;
      morse_map[28][2] = 2;
      morse_map[28][3] = 2;
      morse_map[28][4] = 2;

      //3
      morse_map[29][0] = 1;
      morse_map[29][1] = 1;
      morse_map[29][2] = 1;
      morse_map[29][3] = 2;
      morse_map[29][4] = 2;

      //4
      morse_map[30][0] = 1;
      morse_map[30][1] = 1;
      morse_map[30][2] = 1;
      morse_map[30][3] = 1;
      morse_map[30][4] = 2;

      //5
      morse_map[31][0] = 1;
      morse_map[31][1] = 1;
      morse_map[31][2] = 1;
      morse_map[31][3] = 1;
      morse_map[31][4] = 1;

      //6
      morse_map[32][0] = 2;
      morse_map[32][1] = 1;
      morse_map[32][2] = 1;
      morse_map[32][3] = 1;
      morse_map[32][4] = 1;

      //7
      morse_map[33][0] = 2;
      morse_map[33][1] = 2;
      morse_map[33][2] = 1;
      morse_map[33][3] = 1;
      morse_map[33][4] = 1;

      //8
      morse_map[34][0] = 2;
      morse_map[34][1] = 2;
      morse_map[34][2] = 2;
      morse_map[34][3] = 1;
      morse_map[34][4] = 1;

      //9
      morse_map[35][0] = 2;
      morse_map[35][1] = 2;
      morse_map[35][2] = 2;
      morse_map[35][3] = 2;
      morse_map[35][4] = 1;
    }
};


Buzzer buzzer(13, 12);

#endif
