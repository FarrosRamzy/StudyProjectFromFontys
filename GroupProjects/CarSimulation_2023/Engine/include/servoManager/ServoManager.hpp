#pragma once

#include <Servo.h>

#define MAXSPEED 1720
#define MINSPEED 1500
namespace servoControlNameSpace
{
  class ServoControl
  {
  public:
    void servoAttach(int pin);
    void speedUp();
    void slowDown();
    void handBreak();
    Servo myServo;

  private:
    // Servo myServo;
  };
}