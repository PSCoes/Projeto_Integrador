#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <WiFiUDP.h>

const char* apSSID = "Boneco Resusci"; // Nome do seu ponto de acesso
int i =0;

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Iniciar o modo de ponto de acesso
  WiFi.softAP(apSSID);

  Serial.print("Aguardando conexão de clientes no SSID: ");
  Serial.println(apSSID);
}

void loop() {
  // Endereço IP e porta do celular
  IPAddress celularIP(192, 168, 4, 2); // Endereço IP do celular (dentro da rede do AP)
  int celularPort = 12345; // Porta desejada

  udp.beginPacket(celularIP, celularPort);
  udp.write("Oi Mundo" + i);
  udp.endPacket();
  i++;

  Serial.println("Mensagem enviada para o celular");

  delay(10); // Aguarde um 10 milissegundos antes de enviar a próxima mensagem
}
