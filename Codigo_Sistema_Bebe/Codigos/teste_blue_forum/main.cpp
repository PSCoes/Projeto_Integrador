// code by Martyn Currie.
// To enable AT mode connect the EN pin of the HC05 
// to 3.3V before powering the HC05.  
// Caution, do not connect EN to 5V.

#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

const char* ssid = "Boneco Resusci"; // Nome do seu ponto de acesso
const char* password = "1234"; // Senha do ponto de acesso

WiFiServer server(80);


void setup() {
  Serial.begin(115200);
  delay(10);

  // Configurar a ESP8266 como ponto de acesso
  WiFi.softAP(ssid);

  Serial.println();
  Serial.print("Ponto de Acesso Wi-Fi: ");
  Serial.println(ssid);
  Serial.print("Endereço IP:");
  Serial.println(WiFi.softAPIP());

  server.begin();

  }

void loop() {
  // Verificar se há clientes
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Novo cliente conectado");

    // Responder à solicitação do cliente
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("Olá, Mundo!");
    client.println();
    
    // Fechar a conexão com o cliente
    client.stop();
    Serial.println("Cliente desconectado");
  }
}
