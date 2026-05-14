#include <wifi_esp.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  // ESPserial.print("AT+RST");
  while (!setUpWifi())
  {
    Serial.println("Device Not Connected.");
  }
  Serial.println("Device Connected.");
  Serial.println("");
  Serial.println("Device Ready.");
}

void loop()
{
  runWifi();
}