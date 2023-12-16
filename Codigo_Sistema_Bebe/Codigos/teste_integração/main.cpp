/*

Conexão do sensor com a ESP8266:

Portas SENSOR X ESP8266:

Vin X 3.3V
GND X GND
SCL X D1
SDA X D2


*/


#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_VL6180X.h>


// Constantes do filtro de medição
double medicao = 0;
double xn1 = 0;
double yn1 = 0;
double yn2 = 0;
int k = 0;
int i = 0;

// Constantes de frequência
bool positivo = 1;
double freq = 0;
double freq2 = 0;
double freq1 = 0;
double t0 = 0;
double t1 = 0;
double T1 = 0;
double T2 = 0;

// Criação de um objeto da classe do sensor
Adafruit_VL6180X vl = Adafruit_VL6180X();



// Configuração do hotspot
const char* ssid = "Boneco Resusci"; // Nome do seu ponto de acesso

// Declaração do servidor na porta 80
WiFiServer server(80);


void setup() {
  Serial.begin(115200);
  delay(10);
  
  // Teste de conexão do sensor
  Serial.println("Adafruit VL6180x test!");
  if (!vl.begin()) {
    Serial.println("Failed to find sensor");
    while (1);
  }
  Serial.println("Sensor found!");



  // Configurar a ESP8266 como ponto de acesso
  WiFi.softAP(ssid);

  Serial.println();
  Serial.print("Ponto de Acesso Wi-Fi: ");
  Serial.println(ssid);
  Serial.print("Endereço IP:");
  Serial.println(WiFi.softAPIP());

  server.begin(); // Inicia o servidor

  }

void loop() {
  // Leitura de distância do sensor
  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();

  if (status == VL6180X_ERROR_NONE) {
    medicao = range;
    
  }else{
    medicao = 200;
    }

  // Compute the filtered signal
  double yn = 1.656*yn1 - 0.6859*yn2 + 0.01568*medicao + 0.01383*xn1;

  delay(1);
  xn1 = medicao;
  yn2 = yn1;
  yn1 = yn;

  yn = yn/10.0;

  if(positivo && ((yn) < 3.5)){
    positivo = 0;
    t0 = t1;
    t1 = millis();
    T1 = t1-t0;
    
  }else if((!positivo) && ((yn)>3.5)){
    positivo = 1;
    t0 = t1;
    t1 = millis();
    T2 = t1-t0;
    freq = 60/((T1+T2)/1000);
    
    
  }

  
  if(k % 3 == 0){
    // This extra conditional statement is here to reduce
    // the number of times the data is sent through the serial port
    // because sending data through the serial port
    // messes with the sampling frequency
  
    // Output
    //Serial.print(medicao/10.0);
    Serial.print("Distância: ");
    Serial.print(String(yn) + ";" + freq);
    Serial.print(" ");
    Serial.print("Frequência: ");
    Serial.println(freq);
  }


  // Verificar se há clientes
  WiFiClient client = server.available();
  if (client) {

    // Responde à solicitação do cliente
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println(String(yn) + ";" + freq);
    client.println();
    
    // Fechar a conexão com o cliente
    client.stop();
  }
}


// ---------------------------------------------------------------------------------------------------- //



