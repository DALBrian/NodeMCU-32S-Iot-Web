#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHT_PIN 25U
#define DHT_TYPE DHT22

const char* ssid = "SWIFT14";
const char* password = "77754321";
const char* serverUrl = "http://192.168.137.1:5000//upload";

DHT dht(DHT_PIN, DHT_TYPE);

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("[INFO] Serial startup successful. ");

  dht.begin();
  Serial.println("[INFO] DHT startup successful.");

  WiFi.begin(ssid, password);

  uint16_t WiFiTimeout = 0U;
  while((WiFi.status() != WL_CONNECTED) && (WiFiTimeout < 60U))
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

void loop(void) 
{
  volatile float temperature = dht.readTemperature();
  volatile float humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("Error: Failed to read DHT sensor!");
  }
  else
  {
    Serial.printf("Temperature %.1f degree Celcius, Humidity: %.1f %%\n", temperature, humidity);
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    String json = "{\"temperature\":" + String(temperature) + 
                  ",\"humidity\":" + String(humidity) + "}"; /* {temperature: value, humidity*: value} */

    int httpResponse = http.POST(json);
    http.end();
  }
  delay(2000);
}
