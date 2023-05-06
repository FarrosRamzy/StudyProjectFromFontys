/***************************************************************************
  This is a library for the CCS811 air

  This sketch reads the sensor

  Designed specifically to work with the Adafruit CCS811 breakout
  ----> http://www.adafruit.com/products/3566

  These sensors use I2C to communicate. The device's I2C address is 0x5A

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Arduino.h>
#include <wire.h> //I2C
#include <spi.h>
#include "Adafruit_CCS811.h" //Sensor library

bool highTvoc = false;
bool danger = false;
bool ventilation = false;

unsigned long ventilationOnTime = 1000;
unsigned long previousHighTvocTime = 0;

unsigned long sensorInterval = 1000;
unsigned long previousLowTvocTime = 0;

unsigned long previousMillis;
unsigned long interval = 500; // start value set to 1 second

int ledState = LOW;           // led is off at start.

const int buzzer = 9; // buzzer to arduino pin 9
const int LED = 3;
int sound = 450;

Adafruit_CCS811 ccs;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.println("CCS811 test");

  while (!ccs.begin())
  {
    Serial.println("Failed to start sensor! Please check your wiring.");
    //     while (1);
  }

  // Wait for the sensor to be ready
  while (!ccs.available())
    ;
}

void alarm()
{
  digitalWrite(LED, HIGH);
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;

    if (sound == 450)
    {
      sound = 550;
      interval = 300;
    }
    else
    {
      interval = 400;
      sound = 550;
    }
    tone(buzzer, sound);
  }
}

void loop()
{
  if (ccs.available())
  {
    if (!ccs.readData())
    {
      if (ccs.getTVOC() > 50)
      {
        Serial.print("TVOC (ppb): ");
        Serial.println(ccs.getTVOC());
        {
          if (highTvoc == false)
          {
            highTvoc = true;

            unsigned long highVocTime = millis();

            if (highVocTime - previousHighTvocTime >= ventilationOnTime)
            {
              previousHighTvocTime = highVocTime;

              if (ventilation == false)
              {
                ventilation = true;
                alarm();
                Serial.println("High TVOC, Ventilation turned ON");
              }
            }
          }
        }
      }
      else if (ccs.getTVOC() < 50)
      {
        unsigned long lowVocTime = millis();

        if (lowVocTime - previousLowTvocTime >= sensorInterval)
        {
          previousLowTvocTime = lowVocTime;
          Serial.print("TVOC (ppb): ");
          Serial.println(ccs.getTVOC());
          {
            if (highTvoc == true)
            {
              highTvoc = false;
              {
                if (ventilation == true)
                {
                  ventilation = false;
                  noTone(buzzer);
                  digitalWrite(LED, LOW);
                  Serial.println("Low TVOC, Ventilation turned OFF");
                }
              }
            }
          }
        }
      }
    }
    else
    {
      Serial.println("ERROR!");
      // while (1);
    }
  }
}
