#include "../include/servoManager/ServoManager.hpp"
#include <Arduino.h>
namespace servoControlNameSpace
{

  void ServoControl::servoAttach(int pin)
  {
    myServo.attach(pin);
  }

  void ServoControl::speedUp()
  {
    int currentSpeed = myServo.readMicroseconds();
    Serial.println(currentSpeed);
    if (currentSpeed <= MAXSPEED)
    {
      myServo.write(currentSpeed + 1);
    }
    else
    {
      myServo.write(currentSpeed);
    }
  }

  void ServoControl::slowDown()
  {
    int currentSpeed = myServo.readMicroseconds();
    Serial.println(currentSpeed);
    if (currentSpeed >= MINSPEED)
    {
      myServo.write(currentSpeed - 1);
    }
    else
    {
      myServo.write(currentSpeed);
    }
  }

  void ServoControl::handBreak()
  {
    int currentSpeed = myServo.readMicroseconds();
    Serial.println(currentSpeed);
    if (currentSpeed >= MINSPEED)
    {
      myServo.write(currentSpeed - 2);
    }
    else
    {
      myServo.write(currentSpeed);
    }
  }
}