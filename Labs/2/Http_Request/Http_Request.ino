#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "config.h"

const char* ssid = SSID; //Your Wifi's SSID
const char* password = PASSWORD; //Wifi Password

WiFiClient wifiClient;
const char* laptopAt = LAPTOP_IP; //change to your Laptop's IP

void setup(void){
  Serial.begin(115200);
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
}

void loop(void){
  Serial.print("Sending...");
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    
    String url = laptopAt;
    url += "data?data1=31.2&data2=76"; //hardcoded values for example only
    
    http.begin(wifiClient,url);
    int returnCode = http.GET();   //perform a HTTP GET request
    
    if (returnCode > 0){
      String payload = http.getString();
      Serial.println(payload);
    }
    http.end();
    
  } else {
    Serial.println("WiFi disconnected");
  }
  delay(5000);  //Five second delay
}
