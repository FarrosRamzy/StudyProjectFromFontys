#include <Arduino.h>
//#include <analogWrite.h> //this is not necessary, but it is programmed on an ESP32 remove if used with arduino

const int motor1pin1 = A2;
const int motor1pin2 = A1;
int speedcontrol = A0;

void setup() 
{
  Serial.begin(9600);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(speedcontrol, OUTPUT); 
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(speedcontrol, 255);
}

void setManualSpeed(int speed)
{
  analogWrite(speedcontrol, speed);
}

void loop() 
{
  int temp = random(20, 30); //simulation of temperature
  int hum = random(50, 60); //simulation of humidity
  Serial.println(temp);
  Serial.println(hum);

  if(temp >= 25 && hum >= 58)
  {
    analogWrite(speedcontrol, 255);
    delay(2000);
  }
  else if(temp < 25 || hum <= 55)
  {
    analogWrite(speedcontrol, 128);
    delay(2000);
  }
}


