String val = "";
bool keepReading = false;

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
  bool wait = false,
  Stream &_stream = Serial1
) {
  //Obtener la posicion del primer delimitador
  int findex = raw_value.indexOf(first_del);
  if (findex < 0) {
    return NULL_STRING;
  }
  findex += first_del.length();
  //Obtener la posicion del ultimo delimitador
  int lindex = raw_value.indexOf(last_del);
  if (lindex < 0) {
    //Si no se debe esperar a que se termine de enviar, se retorna nulo
    if (!wait) {
      return NULL_STRING;
    }

    //Esperar a que se termine de enviar la finalizacion del mensaje
    //Esperar a que el mensaje este disponible
    while (!(_stream.available() > 0)) {
      ;
    }

    //Leer el mensaje disponible
    while (lindex < 0 && _stream.available()) {
      raw_value += _stream.readString();
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
      //Procesar el valor obtenido por el modulo
      //Funcion configurable enviada por parametro, debe devolver un boolean y obtener un parametro String
      bool interrupted = process(val);

      _stream.println("$continue$");
      _stream.flush();

      return interrupted;
    }
  }

  return false;
}

//recibir del Serial1, funcion por defecto
bool recieveString(bool (*process_fnc)(String val)) {
  return checkAvailable(Serial1, process_fnc);
}

//recibir del Serial, funcion customizada
bool recieveStringS0(bool (*process_fnc)(String val)) {
  return checkAvailable(Serial, process_fnc);
}
