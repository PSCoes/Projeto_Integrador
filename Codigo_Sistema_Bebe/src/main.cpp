#include <Arduino.h>
#include <Adafruit_VL6180X.h>
#include <SoftwareSerial.h>

#define COMAND 9
#define CONECT 8

SoftwareSerial MyBlue(2,3); // RX|TX

void setup() {
  // put your setup code here, to run once:
  MyBlue.begin(9600);
  Serial.begin(9600);
  pinMode(COMAND, OUTPUT);
  pinMode(CONECT, INPUT);
}

void loop() {
  //while()
  // put your main code here, to run repeatedly:
  if(MyBlue.available()){
    //Serial.println(MyBlue.read());
  }
}

// Código incompleto