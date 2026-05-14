#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ErriezMHZ19B.h>

SoftwareSerial mhzSerial(12,13);
ErriezMHZ19B co2mhz19b(&mhzSerial);

float co2;

void setupCO2Sensor()
{
    mhzSerial.begin(9600);
    co2mhz19b.setRange5000ppm();
    co2mhz19b.setAutoCalibration(true);
    while (!co2mhz19b.detect())
    {
        Serial.println(F("CO2 Loading ..."));
    }
}

void readCarbonDioxide(float *co2)
{
    float temporary = *co2;
    if (co2mhz19b.isReady())
    {
        if (co2mhz19b.readCO2() >= 0)
        {
            *co2 = co2mhz19b.readCO2();
        }
    }
    else
    {
        *co2 = temporary;
    }
}

void setup() {
  Serial.begin(9600);
  co2 = 400;
  setupCO2Sensor();
}
 
void loop() {
  readCarbonDioxide(&co2);
  Serial.print("CO2:  ");
  Serial.println(co2);
  delay(3000);
}