#include <Arduino.h>
#include "DHT.h"
#define DHT_PIN 25U
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 startup successful. ");
  dht.begin();
  Serial.println("Initialize DHT module.");
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
