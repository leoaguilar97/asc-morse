#define NULL_STRING String("")

enum State {
  START, //Valor inicial del sistema, mostrando mensaje "HOLA GRUPO #1" en la pantalla
  RECIEVING, //El sistema se encuentra esperando palabras para mostrar en pantalla
  WRITING, //El sistema se encuentra escuchando a los botones para
  PLAYING //El sistema se encuentra en estado de juego
};

State states[4] = {START, RECIEVING, WRITING, PLAYING};
//State ID
int sid = 0;

/*
   Obtiene el valor del String dentro de los delimitadores, funcion que facilita el uso de substring.
   Si no encuentra los delimitadores, devuelve "null"
   El parametro wait se utiliza para saber si debe esperar a que se le envie el final de la cadena por el Serial1
   De lo contrario, fallara si no encuentra el final de la cadena y retornara null.
*/
String getRecievedValue(
  String raw_value,
  String first_del,
  String last_del,
  bool wait = false
) {
  //Obtener la posicion del primer delimitador
  int findex = raw_value.indexOf(first_del);
  if (findex < 0) {
    return NULL_STRING;
  }

  //Obtener la posicion del ultimo delimitador
  int lindex = raw_value.indexOf(last_del);
  if (lindex < 0) {
    //Si no se debe esperar a que se termine de enviar, se retorna nulo
    if (!wait) {
      return NULL_STRING;
    }

    //Esperar a que se termine de enviar la finalizacion del mensaje
    //Esperar a que el mensaje este disponible
    while (!Serial1.available()) {
      ;
    }

    //Leer el mensaje disponible
    while (lindex < 0 && Serial1.available()) {
      raw_value += Serial1.readString();
      lindex = raw_value.indexOf(last_del);
    }

    //Si el valor de lindex sigue siendo menor, devolver nulo
    if (lindex < 0) {
      return NULL_STRING;
    }
  }

  //retornar el valor que esta entre los delimitadores
  return raw_value.substring(findex, lindex);
}

//Procesar un valor string enviado, revisar cual comando esta siendo enviado
//Y realizar una accion dependiendo de el valor obtenido
void process(String value) {
  //Revisar si es un valor de palabra
  
}

//Procesar un ciclo del sistema
void process_loop() {
  switch (states[sid]) {
    case START: {} break;
    case RECIEVING: {} break;
    case WRITING: {} break;
    case PLAYING: {} break;
  }
}

//Cambia el valor del estado actual, ya que siempre se lee states[ss_id], al cambiar el indice de 
//manera ciclica
void change_state(){
  sid = (sid + 1) % 4;
}
