#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Casa 3";
const char *password = "Aa1234zZ";

const char *host = "ascmorse.appspot.com";
const int httpsPort = 443;

const char fingerprint[] PROGMEM = "BB 43 9A E6 99 A4 01 A9 86 EE 11 D0 6D 69 84 38 1D 03 FC DA";

String message = "";
boolean is_app = false;

void process_app_request() {
  WiFiClientSecure httpsClient;
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000);

  int r = 0;

  while ((!httpsClient.connect(host, httpsPort)) && (r < 30)) {
    delay(10);
    r++;
  }

  if (r == 30) {
    return;
  }

  String Link = "/getWord?arduino=true";

  httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" +
                    "Connection: close\r\n\r\n");

  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }

  String line = "";
  while (httpsClient.available()) {
    line += httpsClient.readStringUntil('\n');
  }
  Serial.println(line);

  delay(100);
}

/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/

void setup() {  Serial.begin(115200);

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// the loop function runs over and over again forever
void loop() {
  process_app_request();
  delay(1000);
}
