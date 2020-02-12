#include "buzzer.h"
#include "Arduino.h"

//pin1 = sonido y pin2 = encender y apagar buzer
Buzzer::Buzzer(int pin1,int pin2)
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
  
  corriente = pin1;
  onOff = pin2;
  instanciaCaracteres();
  tiempoPausaSonido = 400;
  tiempoPausaLetra = 1500;
}

void Buzzer::ok(){
  sonidosMorse(100,1);
  pausa(50);
  sonidosMorse(100,1);
}

void Buzzer::fail(){
  sonidosMorse(700,1);
  pausa(50);
  sonidosMorse(100,1);
}

//tiempo = tiempo de pausas entre letras
void Buzzer::settiempoPausaLetra(int tiempo){
    tiempoPausaLetra = tiempo;
}

//tiempo = tiempo entre pitidos
void Buzzer::settiempoPausaSonido(int tiempo){
    tiempoPausaSonido = tiempo;
}

void Buzzer::reproducirString(String cadena){
  for(int c=0;c<cadena.length();c++){
    int caracter = -1;
    
    if(cadena.charAt(c)>64&&cadena.charAt(c)<91){
      caracter = cadena.charAt(c)-65;
    }
    else if(cadena.charAt(c)>47&&cadena.charAt(c)<58){    
      caracter = cadena.charAt(c)-23;
    }
    
    if(caracter == -1){
      break;  
    }
      
    for(int i=0;i<5;i++){
      if(letrasMorse[caracter][i]==0)
        break;
      else if(letrasMorse[caracter][i]==1)
        punto();
      else
        raya();
      
      pausaSonido();
    }
      pausaLetra();
  }
}

void Buzzer::punto(){
  sonidosMorse(200,1);
}

void Buzzer::raya(){
  sonidosMorse(600,150);
}

void Buzzer::pausaSonido(){
  pausa(tiempoPausaSonido);
}

void Buzzer::pausaLetra(){
  pausa(tiempoPausaLetra);
}

void Buzzer::pausa(int tiempo){
  int contador = millis();
  while(contador+tiempo>millis()){
  }
}

void Buzzer::sonidosMorse(int tiempo,int sonido){
  int contador = millis();
  int frecuencia = 0;  
  
  digitalWrite(onOff,HIGH);
  
  while(contador+tiempo>millis()){
    if(frecuencia<millis()){
      digitalWrite(corriente,HIGH);
      frecuencia = millis()+sonido;
    }
    else{
      digitalWrite(corriente,LOW);
    }
  }  
  
  digitalWrite(onOff,LOW);
}

void Buzzer::instanciaCaracteres(){
  //A
  letrasMorse[0][0] = 1;
  letrasMorse[0][1] = 2;
  
  //B
  letrasMorse[1][0] = 2;
  letrasMorse[1][1] = 1;
  letrasMorse[1][2] = 1;
  letrasMorse[1][3] = 1;
  
  //C
  letrasMorse[2][0] = 2;
  letrasMorse[2][1] = 1;
  letrasMorse[2][2] = 2;
  letrasMorse[2][3] = 1;
  
  //D
  letrasMorse[3][0] = 2;
  letrasMorse[3][1] = 1;
  letrasMorse[3][2] = 1;
  
  //E
  letrasMorse[4][0] = 1;
  
  //F
  letrasMorse[5][0] = 1;
  letrasMorse[5][1] = 1;
  letrasMorse[5][2] = 2;
  letrasMorse[5][3] = 1;
  
  //G
  letrasMorse[6][0] = 2;
  letrasMorse[6][1] = 2;
  letrasMorse[6][2] = 1;
  
  //H
  letrasMorse[7][0] = 1;
  letrasMorse[7][1] = 1;
  letrasMorse[7][2] = 1;
  letrasMorse[7][3] = 1;
  
  //I
  letrasMorse[8][0] = 1;
  letrasMorse[8][1] = 1;
  
  //J
  letrasMorse[9][0] = 1;
  letrasMorse[9][1] = 2;
  letrasMorse[9][2] = 2;
  letrasMorse[9][3] = 2;
  
  //K
  letrasMorse[10][0] = 2;
  letrasMorse[10][1] = 1;
  letrasMorse[10][2] = 2;
  
  //L
  letrasMorse[11][0] = 1;
  letrasMorse[11][1] = 2;
  letrasMorse[11][2] = 1;
  letrasMorse[11][3] = 1;
  
  //M
  letrasMorse[12][0] = 2;
  letrasMorse[12][1] = 2;
  
  //N
  letrasMorse[13][0] = 2;
  letrasMorse[13][1] = 1;
  
  //O
  letrasMorse[14][0] = 2;
  letrasMorse[14][1] = 2;
  letrasMorse[14][2] = 2;
  
  //P
  letrasMorse[15][0] = 1;
  letrasMorse[15][1] = 2;
  letrasMorse[15][2] = 2;
  letrasMorse[15][3] = 1;
  
  //Q
  letrasMorse[16][0] = 2;
  letrasMorse[16][1] = 2;
  letrasMorse[16][2] = 1;
  letrasMorse[16][3] = 2;
  
  //R
  letrasMorse[17][0] = 1;
  letrasMorse[17][1] = 2;
  letrasMorse[17][2] = 1;
  
  //S
  letrasMorse[18][0] = 1;
  letrasMorse[18][1] = 1;
  letrasMorse[18][2] = 1;

  //T
  letrasMorse[19][0] = 1;
  
  //U
  letrasMorse[20][0] = 1;
  letrasMorse[20][1] = 1;
  letrasMorse[20][2] = 2;
  
  //V
  letrasMorse[21][0] = 1;
  letrasMorse[21][1] = 1;
  letrasMorse[21][2] = 1;
  letrasMorse[21][3] = 2;
  
  //W
  letrasMorse[22][0] = 1;
  letrasMorse[22][1] = 2;
  letrasMorse[22][2] = 2;
  
  //X
  letrasMorse[23][0] = 2;
  letrasMorse[23][1] = 1;
  letrasMorse[23][2] = 1;
  letrasMorse[23][3] = 2;
  
  //Y
  letrasMorse[24][0] = 2;
  letrasMorse[24][1] = 1;
  letrasMorse[24][2] = 2;
  letrasMorse[24][3] = 2;
  
  //Z
  letrasMorse[25][0] = 2;
  letrasMorse[25][1] = 2;
  letrasMorse[25][2] = 1;
  letrasMorse[25][3] = 1;

  //0
  letrasMorse[26][0] = 2;
  letrasMorse[26][1] = 2;
  letrasMorse[26][2] = 2;
  letrasMorse[26][3] = 2;
  letrasMorse[26][4] = 2;
  
  //1
  letrasMorse[27][0] = 1;
  letrasMorse[27][1] = 2;
  letrasMorse[27][2] = 2;
  letrasMorse[27][3] = 2;
  letrasMorse[27][4] = 2;
  
  //2
  letrasMorse[28][0] = 1;
  letrasMorse[28][1] = 1;
  letrasMorse[28][2] = 2;
  letrasMorse[28][3] = 2;
  letrasMorse[28][4] = 2;
  
  //3
  letrasMorse[29][0] = 1;
  letrasMorse[29][1] = 1;
  letrasMorse[29][2] = 1;
  letrasMorse[29][3] = 2;
  letrasMorse[29][4] = 2;
  
  //4
  letrasMorse[30][0] = 1;
  letrasMorse[30][1] = 1;
  letrasMorse[30][2] = 1;
  letrasMorse[30][3] = 1;
  letrasMorse[30][4] = 2;
  
  //5
  letrasMorse[31][0] = 1;
  letrasMorse[31][1] = 1;
  letrasMorse[31][2] = 1;
  letrasMorse[31][3] = 1;
  letrasMorse[31][4] = 1;
  
  //6
  letrasMorse[32][0] = 2;
  letrasMorse[32][1] = 1;
  letrasMorse[32][2] = 1;
  letrasMorse[32][3] = 1;
  letrasMorse[32][4] = 1;
  
  //7
  letrasMorse[33][0] = 2;
  letrasMorse[33][1] = 2;
  letrasMorse[33][2] = 1;
  letrasMorse[33][3] = 1;
  letrasMorse[33][4] = 1;
  
  //8
  letrasMorse[34][0] = 2;
  letrasMorse[34][1] = 2;
  letrasMorse[34][2] = 2;
  letrasMorse[34][3] = 1;
  letrasMorse[34][4] = 1;
  
  //9
  letrasMorse[35][0] = 2;
  letrasMorse[35][1] = 2;
  letrasMorse[35][2] = 2;
  letrasMorse[35][3] = 2;
  letrasMorse[35][4] = 1;  
}
