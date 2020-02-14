#define DEBUG 1

void debug(String val){
  #if DEBUG
  Serial.println(String(">> ") + val); 
  #endif  
}
