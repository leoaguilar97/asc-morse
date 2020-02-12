#ifndef Buzzer_h
#define Buzzer_h
#include <Arduino.h>

class Buzzer
{
  public:
    Buzzer(int pin1,int pin2);
    void punto();
    void raya();
    void reproducirString(String cadena);
    void settiempoPausaSonido(int tiempo);
    void settiempoPausaLetra(int tiempo);
    
    void ok();
    void fail();
    
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
