#include <Wire.h>
#include <SPI.h>
#include <Adafruit_VL6180X.h>

double x[15];
double valor = 0;
/*
double xp2 = 0;
double xp1 = 0;
double x   = 0;
double xf1 = 0;
double xf2 = 0;
*/
float medicao = 0;
float xn1 = 0;
float yn1 = 0;
float yn2 = 0;
int k = 0;
int i = 0;


Adafruit_VL6180X vl = Adafruit_VL6180X();

void setup() {
  Serial.begin(115200);

  // wait for serial port to open on native usb devices
  while (!Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL6180x test!");
  if (! vl.begin()) {
    Serial.println("Failed to find sensor");
    while (1);
  }
  Serial.println("Sensor found!");
}

void loop() {

  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();

  if (status == VL6180X_ERROR_NONE) {
    medicao = range;
    
  }else{
    medicao = 200;
    }

  // Compute the filtered signal
  float yn = 1.656*yn1 - 0.6859*yn2 + 0.01568*medicao + 0.01383*xn1;

  delay(1);
  xn1 = medicao;
  yn2 = yn1;
  yn1 = yn;
  

  if(k % 3 == 0){
    // This extra conditional statement is here to reduce
    // the number of times the data is sent through the serial port
    // because sending data through the serial port
    // messes with the sampling frequency
  
    // Output
    Serial.print(medicao);
    Serial.print(" ");
    Serial.println(yn);
  }
  k = k+1;
}
