#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHT_PIN 25U
#define DHT_TYPE DHT22

const char* ssid = "HITRON-2-1";
const char* password = "XXXXX";
const char* serverUrl = "http://YOUR_SERVER_IP:5000/upload";

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("[INFO] Serial startup successful. ");

  dht.begin();
  Serial.println("[INFO] DHT startup successful.");

  WiFi.begin(ssid, password);

  uint16_t WiFiTimeout = 0U;
  while((WiFi.status() != WL_CONNECTED) && (WiFiTimeout < 0xFFU))
  {
    Serial.println("[INFO] Connecting to WiFi...");
    WiFiTimeout++;
    delay(1000);
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("[INFO] WiFi connect successful.");
  }
  else
  {
    Serial.println("[WARNING] WiFi connect timeout.");
  }
}

void loop() {
  volatile float temperature = dht.readTemperature();
  volatile float humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("Error: Failed to read DHT sensor!");
  }
  else
  {
    Serial.printf("Temperature %.1f degree Celcius, Humidity: %.1f %%\n", temperature, humidity);
    
  }
  delay(2000);
}
