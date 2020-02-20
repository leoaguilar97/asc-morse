#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

#define DEBUG 1

void debug(String val) {
#if DEBUG
  if (val == "$-1$") return;
  Serial.println(String(">> ") + val);
#endif
}

const char *ssid = "Casa 3";
const char *password = "Aa1234zZ";
const char *host = "http://arqui2-api-p2-ayd2.apps.us-west-1.starter.openshift-online.com/";

String message = "";
boolean is_app = false;
//current player id
int cpid = 0;

//setup del modulo esp_826
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Conectando a internet");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Conectado a: ");
  Serial.println(ssid);
  Serial.print("IP local: ");
  Serial.println(WiFi.localIP());
  Serial.println("-----------");
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
  Serial.println(">> Respuesta obtenida");
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
    
    debug("Realizando get");
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

  app_request(String("addWord?word=") + String(wordToSend));
  Serial.println("ok");
}

//Obtiene el juego del server
void getGame() {
  waitSerial();

  String resp = app_request(String("getGame"));
  resp.trim();

  Serial.println(String("Respuesta: ") + resp);

  if (resp == "") {
    //no hay ningun juego actual
    Serial.println("...");
  }
  else {
    //indice del "|" para separar el id del jugador de la palabra
    int slash_index = resp.indexOf("|");
    resp.substring(0, slash_index);

    //obtener el id del jugador
    cpid = resp.toInt();

    Serial.println(String("Jugador: ") + String(cpid));
    String gameWord = resp.substring(slash_index + 1, resp.length());

    Serial.println(
      String("$WORD_") + gameWord + String("_WORD$$_end_$")
    );
  }
}

//Envia el resultado obtenido por el jugador al server
void sendScore() {
  waitSerial();
  String score = Serial.readString();

  app_request(
    String("setScore?id=")
    + String(cpid)
    + String("&score=")
    + score
  );

  Serial.println("ok");
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
    Serial.println(">> Finalizado");
  }
}
