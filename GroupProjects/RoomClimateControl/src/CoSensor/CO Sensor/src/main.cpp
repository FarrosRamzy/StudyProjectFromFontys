#include <Arduino.h>

const int LED = 2; 
const int DO = 8; 

void setup() { 
  Serial.begin(9600); 
} 
 
void loop() {
  int alarm = 0; 
  float sensor_volt; 
  float RS_gas; 
  float ratio; 
 //-Replace the name "R0" with the value of R0 in the demo of First Test -/ 
  float R0 = 0.91; 
 
  int sensorValue = analogRead(A0); 
  sensor_volt = ((float)sensorValue / 1024) * 5.0; 
 RS_gas = (5.0 - sensor_volt) / sensor_volt; // Depend on RL on yor module 
 
 
  ratio = RS_gas / R0; // ratio = RS/R0 
  // This ration represents the reading of the sensor 
  // When it is BELLOW < 0.7 It is not CO anymore , when it is more the > 2 it is not CO any more
  // Therefore Co gas is detected by the sensor in this interval ( 2.0, 0.7 )
 //------------------------------------------------------------/ 
 


  Serial.print("sensor_volt = "); 
  Serial.println(sensor_volt); 
  Serial.print("RS_ratio = "); 
  Serial.println(RS_gas); 
  Serial.print("Rs/R0 = "); 
  Serial.println(ratio); 
 
  Serial.print("\n\n"); 
 
  alarm = digitalRead(DO); 
  if (alarm == 1) digitalWrite(LED, HIGH); 
  else if (alarm == 0) digitalWrite(LED, LOW); 
 
  delay(1500); 
 
}