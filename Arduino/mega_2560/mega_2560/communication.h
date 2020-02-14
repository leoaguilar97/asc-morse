String val = "";
bool keepReading = false;

//Valor recibido desde el modulo esp826
void recieveString(){
  if (Serial1.available() > 0){ 
    
    if (keepReading){
      val += Serial1.readString();
    }
    else {
      val = Serial1.readString();
    }
    
    keepReading = val.indexOf("$_end_$") < 0;

    if (!keepReading){
      debug(String("Recibido: ") + val);
      //Procesar el valor obtenido por el modulo, funcion ubicada en processor.h
      process(val);
      
      Serial1.println("$continue$");
      Serial1.flush();
    }
  }
}
