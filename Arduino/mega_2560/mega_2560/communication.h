String val = "";
bool keepReading = false;

//Valor recibido desde el modulo esp826
bool checkAvailable(Stream &_stream, bool (*process)(String val)) {
  if (_stream.available() > 0) {
    if (keepReading) {
      val += _stream.readString();
    }
    else {
      val = _stream.readString();
    }

    keepReading = val.indexOf("$_end_$") < 0;

    if (!keepReading) {
      debug(String("Recibido: ") + val);
      
      //Procesar el valor obtenido por el modulo, funcion ubicada en processor.h
      bool interrupted = process(val);

      _stream.println("$continue$");
      _stream.flush();

      return interrupted;
    }
  }

  return false;
}

//recibir del Serial1, funcion por defecto
bool recieveStringS1(bool (*process_fnc)(String val) = process) {
  return checkAvailable(Serial1, process_fnc);
}

//recibir del Serial, funcion customizada
bool recieveString(bool (*process_fnc)(String val) = process){
  return checkAvailable(Serial, process_fnc);
}
