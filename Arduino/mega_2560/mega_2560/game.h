#ifndef MorseGame_h
#define MorseGame_h

//Clase que instancia un juego,
//en este se espera que con 10 caracteres enviados
//se ingresen los 10 caracteres codificados en morse por el usuario
class Game {

  public:
    //Game constructor
    Game(){ ; }

    //Realiza el juego, en este se piden 10 caracteres y deben ser iguales
    //a cada caracter enviado de la palabra que se envia en el parametro texto
    int start(String text){
      //reiniciar el contador del juego
      int score = 0;

      //obtener 10 caracteres del jugador
      for(int i=0;i<10;i++){
        //definir el texto actual al numero de caracter que se esta ingresando
        setText(String(i) + (": "));

        //obtener un caracter, se tienen 2 segundos para responder o se toma como erronea
        char obtained = obtainChar(2000);

        if(obtainChar(2000) == text.charAt(i)){

          score += 1;
        }
      }

      return score;
    }
};

#endif
