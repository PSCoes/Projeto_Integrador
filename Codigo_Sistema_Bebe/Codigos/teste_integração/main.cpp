// code by Martyn Currie.
// To enable AT mode connect the EN pin of the HC05 
// to 3.3V before powering the HC05.  
// Caution, do not connect EN to 5V.

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
float medicao = 0;
float xn1 = 0;
float yn1 = 0;
float yn2 = 0;
int k = 0;
int i = 0;

// Criação de um objeto da classe do sensor
Adafruit_VL6180X vl = Adafruit_VL6180X();

// Configuração do hotspot
const char* ssid = "Boneco Resusci"; // Nome do seu ponto de acesso

// Declaração do servidor na porta 80
WiFiServer server(80);


void setup() {
  Serial.begin(115200);
  delay(10);

    // wait for serial port to open on native usb devices
  while (!Serial) {
    delay(1);
  }
  // Teste de conexão do sensor
  Serial.println("Adafruit VL6180x test!");
  if (! vl.begin()) {
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
    Serial.print(medicao/10.0);
    Serial.print(" ");
    Serial.println(yn/10.0);
  }
  k = k+1;


  // Verificar se há clientes
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Novo cliente conectado");

    // Responder à solicitação do cliente
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println(String(yn));
    client.println();
    
    // Fechar a conexão com o cliente
    client.stop();
    Serial.println("Cliente desconectado");
  }
}


// ---------------------------------------------------------------------------------------------------- //



