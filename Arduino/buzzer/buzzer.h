#ifndef Buzzer_h
#define Buzzer_h
#include <Arduino.h>

class Buzzer
{
  public:
    Buzzer(int pin1,int pin2); //pin1 = sonido y pin2 = encender y apagar buzer.
    void punto(); //Sonido de punto.
    void raya(); //Sonido de raya.
    void reproducirString(String cadena); //Seproduce texto en morse.
    void settiempoPausaSonido(int tiempo); //Cambial el tiempo de la pausa entre puntos o rayas. Tiempo por defecto de 400 milisegundos.
    void settiempoPausaLetra(int tiempo); //Cambial el tiempo de la pausa entre letras. Tiempo por defecto de 1500 milisegundos.
    void ok(); //Sonido de ok.
    void fail(); //Sonido de falla.

  private:
    void sonidosMorse(int tiempo,int sonido); 
    void pausa(int tiempo);
    void pausaLetra();
    void pausaSonido();
    void instanciaCaracteres();

    int letrasMorse[36][5];
    int corriente;
    int onOff;
    int tiempoPausaSonido;
    int tiempoPausaLetra;
};

#endif
