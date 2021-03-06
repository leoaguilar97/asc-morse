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

//Funcion que realizara un ciclo del sistema, utilizado para revisar el puerto
//ademas de cambios en el estado
bool loopSystem(bool (*process_fnc)(String val));

//Cambia el valor del estado actual, ya que siempre se lee states[ss_id], al cambiar el indice de
//manera ciclica
void change_state() {
  sid = (sid + 1) % 4;
}

//Devuelve el estado actual del sistema
State currentState() {
  return states[sid];
}
