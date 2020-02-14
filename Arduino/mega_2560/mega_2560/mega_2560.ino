#include "buzzer.h"

#define DEBUG 1
void debug(String val){
  #if DEBUG
  Serial.println(String(">> ") + val); 
  #endif  
}

Buzzer buzzer;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println(">> Inicio controlador mega_2560");
  
  buzzer(35, 36);
}

void process_word(String cword){
  //TODO: Program cword recieval
}

void loop() {
  if (Serial1.available() > 0){ 
    String val = Serial1.readString();
    
    debug(String("Recibido: ") + val);

    int i_index = val.indexOf("$_word");
    if (i_index >= 0){
      int s_index = val.indexOf("word_$");
      if (s_index >= 0){
        String c_word = val.substring(i_index, s_index);
        debug(String("Palabra obtenida: " + c_word));
        process_word(c_word);

        buzzer.
      }  
    }

    Serial1.println("continue");
    Serial1.flush();
  }
}
