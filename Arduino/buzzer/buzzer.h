#ifndef Buzzer_h
#define Buzzer_h

class Buzzer
{
  public:
    Buzzer(int pin1,int pin2);
    void dot();
    void dash();
  private:
    void sonidosMorse(int tiempo,int sonido);
    void pausa(int tiempo);
    void pausaLetra();
    void pausaSonido();
    void punto();
    void raya();
    void instanciaCaracteres();

    int letrasMorse[36][5];
    int corriente;
    int onOff;
};

#endif
