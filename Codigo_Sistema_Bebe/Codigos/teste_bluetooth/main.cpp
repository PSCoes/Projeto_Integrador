#include <Arduino.h>
#include <Adafruit_VL6180X.h>
#include <SoftwareSerial.h>

#define COMAND 9
#define CONECT 8

SoftwareSerial MyBlue(2,3); // RX|TX

void setup() {
  // put your setup code here, to run once:
  MyBlue.begin(38400);
  Serial.begin(9600);
  pinMode(COMAND, OUTPUT);
  pinMode(CONECT, INPUT);
}

void loop() {

  if(!digitalRead(CONECT)){
    Serial.println("Esperando para conectar...");
    while(1){
      if(digitalRead(CONECT)){
        Serial.println("Conectado");
        break;
      }
    }
  }

  if(MyBlue.available()){
    String mensagem = String(MyBlue.read());
    Serial.println("Mensagem recebida: " + mensagem);
    MyBlue.print("Recebido");
  }
}

// Código incompleto