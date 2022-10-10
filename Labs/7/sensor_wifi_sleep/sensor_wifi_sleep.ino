#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "config.h"

const uint8_t IN = D5;

const char* ssid = SSID;
const char* password = PASSWORD;

void setup() {
  pinMode(IN, INPUT);
  
  Serial.begin(115200);

  int val = analogRead(IN);
  Serial.print("Read value from sensor: ");
  Serial.println(val);

  WiFi.begin(ssid, password);
  Serial.println("");
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  ESP.deepSleep(20e6);
}

void loop() {}