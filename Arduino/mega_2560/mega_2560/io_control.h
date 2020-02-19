/*
   8x8 LED Matrix MAX7219 Scrolling Text
   Librerias utilizadas:
      https://github.com/riyas-org/max7219
   Basado en:
      https://howtomechatronics.com/tutorials/arduino/8x8-led-matrix-max7219-tutorial-scrolling-text-android-control-via-bluetooth/

   Comandos de prueba:
    Estado START:
    Estado RECIEVING:
      $WORD_1{TEXTO}_WORD$$_end_$
      $WORD_1HOLA_WORD$$_end_$
      $WORD_1LEO12345_WORD$$_end_$

    Estado WRITING:
    Estado PLAYING:

*/

#include "MaxMatrix.h"
#include <avr/pgmspace.h>

PROGMEM const unsigned char CH[] = {
  3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
  1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
  3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
  5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
  4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
  5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
  5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
  1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
  3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
  3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
  5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
  5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
  2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
  4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
  2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
  4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
  3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
  4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
  4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
  4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
  4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
  4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
  4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
  4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
  4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
  2, 8, B01010000, B00000000, B00000000, B00000000, B00000000, // :
  2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
  3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
  3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
  3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
  4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
  5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
  4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
  4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
  4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
  4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
  4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
  4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
  4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
  4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
  3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
  4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
  4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
  4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
  5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
  5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
  4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
  4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
  4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
  4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
  4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
  5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
  4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
  5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
  5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
  5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
  5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
  4, 8, B01100001, B01010001, B01001001, B01000111, B00000000, // Z
  2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
  4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
  2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
  3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
  4, 8, B01100000, B01100000, B01100000, B01100000, B00000000, // _
  2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
  4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
  4, 8, B01111111, B01000100, B01000100, B00111000, B00000000, // b
  4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
  4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
  4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
  3, 8, B00000100, B01111110, B00000101, B00000000, B00000000, // f
  4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
  4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
  3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
  4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
  4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
  3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
  5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
  4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
  4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
  4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
  4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
  4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
  4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // text
  3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
  4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
  5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
  5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
  5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
  4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
  3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
  3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
  1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
  3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
  4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~
};

int DIN = 10;
int CS = 9;
int CLK = 8;
int MAX = 1;

byte buffer[10];
byte scrollSpeed = 100;
byte brightness = 15;
byte indicator = 0;
byte buffer_size = 0;
byte isMorse = 0;

char text[100] = "HOLA GRUPO #1";

MaxMatrix matrix(DIN, CS, CLK, MAX);

//Iniciar la configuracion inicial de la matriz de leds, y del buzzer
void setupIO() {
  matrix.init();
  matrix.setIntensity(brightness);
}

//limpiar la pantalla y el texto que hay en el buffer
void clearText() {
  for (int i = 0; i < 100; i++) {
    text[i] = 0;
    matrix.clear();
  }
}

//cambia el texto actual al texto enviado en el parametro, existe la posibilidad de limpiar la pantalla antes
void setText(String sent_text, bool cleart = true) {
  if (cleart) {
    clearText();
  }

  //asignar el string al texto
  for (int i = 0; i < sent_text.length(); i++) {
    text[i] = sent_text.charAt(i);
  }
}

//Obtener el buffer de texto en formato String
String getStringText() {
  String result = "";
  for (int i = 0; i < 100; i++) {
    if (!text[i]) {
      break;
    }

    result += String(text[i]);
  }

  return result;
}

//Procesa un ingreso de una cadena, ya sea del serial, del WiFi o del mismo juego
void getRecievedString(String sent_text) {

  //Obtener el texto recibido a traves del puerto serial
  sent_text = getRecievedValue(sent_text, "$WORD_", "_WORD$");
  debug(sent_text);
  // Printing the text
  indicator = sent_text.charAt(0);
  sent_text = sent_text.substring(1, sent_text.length());

  //Si es cambiar el texto
  if (indicator == '1') {
    setText(buzzer.getMorseString(sent_text));
    debug(String("Nuevo Texto: ") + getStringText());
  }
  // Ajustar velocidad de movimiento del texto
  else if (indicator == '2') {
    scrollSpeed = 150 - sent_text.toInt();
  }
  // Ajustar la intensidad del brillo
  else if (indicator == '3') {
    brightness = sent_text.toInt();
    matrix.setIntensity(brightness);
  }
}

//Imprime un caracter en un ciclo, moviendose a la izquierda
bool printCharWithShift(char c, int shift_speed, bool isMorse) {
  //Si es un caracter válido, caracteres imprimibles
  if (c < 32) {
    return;
  }

  //regresar al valor del indice correcto, basado en 0
  c -= 32;

  //Copiar el valor del char pasado y reiniciarlo
  memcpy_P(buffer, CH + 7 * c, 7);
  matrix.writeSprite(8, 0, buffer);
  matrix.setColumn(8 + buffer[0], 0);

  //mover el valor que debe correrse, en el buffer
  int last_bf_index = buffer[0] + 1;
  for (int i = 0; i < buffer[0] + 1; i++)
  {
    delay(shift_speed);
    matrix.shiftLeft(false, false);
  }

  c += 32;

  if (isMorse) {
    buzzer.playDashOrPoint(c);
  }
  else {
    buzzer.playAsciiString(String(c));
  }

  return loopSystem(getRecievedString);
}

//Imprimir un string, corriendolo a la izquierda
void printStringWithShift(char* text, int shift_speed, bool isMorse) {
  while (*text != 0) {
    buffer_size = 0;
    if (printCharWithShift(*text, shift_speed, isMorse)) {
      break;
    }
    text++;
  }
}

//Realiza un ciclo de imprimir en la pantalla el texto que se tiene actualmente
void displayCycle(bool convertToMorse = false) {
  if (convertToMorse && !isMorse) {
    String m = buzzer.getMorseString(getStringText());

    debug(String("Morse: ") + m);

    setText(m);
    isMorse = 1;
  }

  printStringWithShift(text, scrollSpeed, convertToMorse);
}
