#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "../secrets.h"

// ===== CONFIGURAÇÕES MQTT =====
const char* mqtt_server = "192.168.1.69";
const int mqtt_port = 1883;
const char* mqtt_topic = "test/button";

// ===== HARDWARE =====
const int BUTTON_PIN = D5;

// ===== OBJETOS =====
WiFiClient espClient;
PubSubClient client(espClient);

// ===== CONTROLE DE DEBOUNCE =====
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void connectWiFi() {
  Serial.print("Conectando ao WiFi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi conectado. IP: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");

    String clientId = "ESP8266-";
    clientId += String(ESP.getChipId());

    if (client.connect(clientId.c_str())) {
      Serial.println(" conectado!");
    } else {
      Serial.print(" falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 2s...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  connectWiFi();

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }

  client.loop();

  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    static bool buttonState = HIGH;

    if (reading != buttonState) {
      buttonState = reading;

      // Detecta apenas o momento do pressionamento
      if (buttonState == LOW) {
        Serial.println("Botão pressionado");

        client.publish(
          mqtt_topic,
          "button_pressed"
        );

        Serial.println("Mensagem MQTT enviada");
      }
    }
  }

  lastButtonState = reading;
}
