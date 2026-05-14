#include <arduino.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void loop() {
  delay(2000); //making it faster won't change anything, it's a slow sensor, it will only update with a 2 second interval 

  float rh = dht.readHumidity();
  float t = dht.readTemperature();
 
  if (isnan(rh) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F(" Humidity: "));
  Serial.print(rh);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("C "));
}