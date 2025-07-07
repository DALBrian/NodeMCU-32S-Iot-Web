#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#include <ArduinoJson.h>

#define DHT_PIN 25U
#define DHT_TYPE DHT22
#define IS_SERIALPRINT_ENABLE 1

const char* ssid = "SWIFT14";
const char* password = "77754321";
const char* uploadServerUrl = "http://192.168.137.1:5000//upload";
const char* calibrationServerUrl = "http://192.168.137.1:5000//api//calibration";

DHT dht(DHT_PIN, DHT_TYPE);
float tempOffset = 0.0;
float humidityOffset = 0.0;

static void fetchCalibration(void)
{
  HTTPClient http;
  http.begin(calibrationServerUrl);
  int httpCode = http.GET();
  if (httpCode == 200)
  {
    String payload = http.getString();
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (!error)
    {
      tempOffset = doc["temp_offset"].as<float>();
      humidityOffset = doc["humidity_offset"].as<float>();
#if IS_SERIALPRINT_ENABLE
      Serial.printf("Calibration loaded: tempOffset=%.2f, humidityOffset=%.2f\n", tempOffset, humidityOffset);
#endif
    }
    else
    {
#if IS_SERIALPRINT_ENABLE
      Serial.println("Failed to parse JSON");
#endif
    }
  }
  else
  {
#if IS_SERIALPRINT_ENABLE
    Serial.printf("HTTP GET failed, code: %d\n", httpCode);
#endif
  }
  http.end();
}
void setup(void) 
{
#if IS_SERIALPRINT_ENABLE
  Serial.begin(115200);
  Serial.println("[INFO] Serial startup successful. ");
#endif

  dht.begin();
#if IS_SERIALPRINT_ENABLE
  Serial.println("[INFO] DHT startup successful.");
#endif
  WiFi.begin(ssid, password);

  uint16_t WiFiTimeout = 0U;
  while((WiFi.status() != WL_CONNECTED) && (WiFiTimeout < 60U))
  {
#if IS_SERIALPRINT_ENABLE
    Serial.println("[INFO] Connecting to WiFi...");
#endif
    WiFiTimeout++;
    delay(1000);
  }

  if (WiFi.status() == WL_CONNECTED)
  {
#if IS_SERIALPRINT_ENABLE
    Serial.println("[INFO] WiFi connect successful.");
#endif
    fetchCalibration();
  }
  else
  {
#if IS_SERIALPRINT_ENABLE
    Serial.println("[WARNING] WiFi connect timeout.");
#endif
  }
}

void loop(void) 
{
  volatile float temperature = dht.readTemperature();
  volatile float humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity))
  {
#if IS_SERIALPRINT_ENABLE
    Serial.println("Error: Failed to read DHT sensor!");
#endif
  }
  else
  {
#if IS_SERIALPRINT_ENABLE
    Serial.printf("Temperature %.1f degree Celcius, Humidity: %.1f %%\n", temperature, humidity);
#endif
    HTTPClient http;
    http.begin(uploadServerUrl);
    http.addHeader("Content-Type", "application/json");
    String json = "{\"temperature\":" + String(temperature) + 
                  ",\"humidity\":" + String(humidity) + "}"; /* {temperature: value, humidity*: value} */

    int httpResponse = http.POST(json);
    http.end();
  }
  delay(2000);
}
