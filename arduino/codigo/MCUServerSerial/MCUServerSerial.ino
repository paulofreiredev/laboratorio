#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "../secrets.h"

ESP8266WebServer server(80);

unsigned long lastLog = 0;

void handleRoot() {
  String msg = "HTTP request recebida de ";
  msg += server.client().remoteIP().toString();

  Serial.println(msg);

  // Envia para o Arduino pela serial
  Serial.println("REQ");

  server.send(200, "text/plain", "Mensagem enviada para o Arduino");
}

void setup() {
  Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Conectando");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Conectado!");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();

  Serial.println("Servidor iniciado");
}

void loop() {
  server.handleClient();

  if (millis() - lastLog >= 2000) {
    lastLog = millis();

    Serial.print("IP atual: ");
    Serial.println(WiFi.localIP());
  }
}
