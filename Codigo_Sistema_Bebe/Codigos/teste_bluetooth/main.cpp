#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>

int i = 0;
const char* apSSID = "Boneco Ressuci";
ESP8266WebServer server(80);

void handleRoot() {
  // Obter o endereço IP do cliente
  IPAddress clientIP = server.client().remoteIP();
  Serial.print("Endereço IP do cliente: ");
  Serial.println(clientIP);

  server.send(200, "text/plain", String(i));
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // Configurar a ESP-12E como ponto de acesso
  WiFi.softAP(apSSID);

  Serial.println();
  Serial.print("Ponto de Acesso Wi-Fi: ");
  Serial.println(apSSID);

  // Configurar o servidor
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}

void loop() {
  i++;
  server.handleClient();
}