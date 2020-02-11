#ifndef Buzzer_h
#define Buzzer_h
#include <Arduino.h>
class Buzzer
{
  public:
    Buzzer(int pin1,int pin2);
    void punto();
    void raya();
    void ok();
    void fail();
    void reproducirString(String cadena);
    
  private:
    void sonidosMorse(int tiempo,int sonido);
    void pausa(int tiempo);
    void pausaLetra();
    void pausaSonido();
    void instanciaCaracteres();

    int letrasMorse[36][5];
    int corriente;
    int onOff;
};

#endif
