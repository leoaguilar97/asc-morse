#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define DEBUG 0

void debug(String val) {
#if DEBUG
  if (val == "$-1$") return;
  Serial.println(String(">> ") + val);
#endif
}

const char *ssid = "Arnoldo";
const char *password = "12345678";
const char *host = "http://arqui2-api-p2-ayd2.apps.us-west-1.starter.openshift-online.com/";

String message = "";
boolean is_app = false;
//current player id
String cpid = "";

//setup del modulo esp_826
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  
  //Serial.println("");

  //Serial.print("Conectando a internet");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  
  debug("Conectado a: ");
  debug(ssid);
  debug("-----------");
  //*/
}

//Esperar a que el serial este disponible
void waitSerial() {
#if DEBUG
  Serial.println(">> Esperando respuesta");
  int dt = 0;
#endif

  while (!(Serial.available() > 0)) {
#if DEBUG
    if (dt == 10) {
      dt = 0;
      Serial.println(".");
    } else {
      Serial.print(".");
    }
    delay(100);
    dt++;
#endif
  }
#if DEBUG
  Serial.println("\n>> Respuesta obtenida");
#endif
}

//realizar una peticion HTTP y retornar el valor que agrego en string
String app_request(String link) {
  //si el modulo esta conectado a internet
  if (WiFi.status() == WL_CONNECTED) {
    debug("Conectado a internet");
    HTTPClient http;
    //realizar la peticion http
    http.begin(host + link);

    debug("Realizando get: " + link);
    int httpCode = http.GET();
    String result = "";
    //Check the returning code
    if (httpCode > 0) {
      result += http.getString();
    }

    //close connection
    http.end();

    return result;
  }

  return "";
}

//Obtiene la palabra actual del servidor
void getWord() {
  //enviar resultado al arduino
  Serial.println(
    String("$WORD_")
    + app_request("getWord")
    + String("_WORD$$_end_$")
  );
}

//Envia una palabra al servidor
void sendWord() {
  //leer la palabra enviada
  waitSerial();
  String wordToSend = Serial.readString();
  wordToSend.trim();
  /*Serial.print("Enviando palabra: " + wordToSend);
  Serial.println(app_request(String("addMorse?word=") + String(wordToSend)));
  Serial.println("ok");
  */
  app_request(String("addMorse?word=") + String(wordToSend));
}

//Obtiene el juego del server
void getGame() {
  String resp = app_request(String("getGame"));
  String resp2 = resp;

  resp.trim();

  if (resp == "") {
    //no hay ningun juego actual
    Serial.println("$WORD__WORD$$_end_$");
  }
  else {
    //indice del "|" para separar el id del jugador de la palabra
    int slash_index = resp.indexOf("|");

    //obtener el id del jugador
    cpid = resp.substring(0, slash_index);;

    //Serial.println(String("Jugador: ") + cpid);

    Serial.println(
      String("$WORD_")
      + resp.substring(slash_index + 1, resp.length())
      + String("_WORD$$_end_$")
    );
  }
}

//Envia el resultado obtenido por el jugador al server
void sendScore() {
  waitSerial();
  String score = Serial.readString();
  score.trim();
  
  app_request(
    String("setScore?id=")
    + cpid
    + String("&score=")
    + score
  );

  //Serial.println("ok");
}

// The loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0) {
    //Obtener valor ingresado del serial
    String value = Serial.readString();

    if (value.indexOf("getWord") >= 0) {
      getWord();
    }
    else if (value.indexOf("sendWord") >= 0) {
      sendWord();
    }
    else if (value.indexOf("getGame") >= 0) {
      getGame();
    }
    else if (value.indexOf("sendScore") >= 0) {
      sendScore();
    }
    //esperar a que se envie un continue
    while (value.indexOf("$continue$") < 0) {
      waitSerial();
      value = Serial.readString();
    }
    //Serial.println(">> Finalizado");
  }
}
