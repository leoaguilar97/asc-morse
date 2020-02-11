void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  Serial.println(">> Inicio controlador mega_2560");

  
  
}

void loop() {
  if (Serial1.available() > 0){ 
    String val = Serial1.readString();

    Serial.println(String("Recibido: ") + val);

    delay(100);
  }
}
