#include <trial_system.h>

void setupFanSystem()
{
    pinMode(FAN_PIN_A, OUTPUT);
    pinMode(FAN_PIN_B, OUTPUT);
    pinMode(FAN_PWM_PIN, OUTPUT);
    setFanDirection();
}

void setFanDirection()
{
    digitalWrite(FAN_PIN_A, LOW);
    digitalWrite(FAN_PIN_B, HIGH);
}

void processFanSpeed(float temperature, float humidity)
{
    if (temperature >= NORMAL_TEMPERTAURE || humidity >= HIGHEST_HUMIDITY)
    {
        analogWrite(FAN_PWM_PIN, 255);
    }
    else if (temperature < NORMAL_TEMPERTAURE && humidity < NORMAL_HUMIDITY)
    {
        analogWrite(FAN_PWM_PIN,128);
    }
}

void setFanSpeedManually(uint32_t speedValue)
{
    uint32_t actualSpeed = speedValue * 51;
    if (actualSpeed == 0)
    {
        analogWrite(FAN_PWM_PIN, 0);
    }
    else
    {
        analogWrite(FAN_PWM_PIN, actualSpeed);
    }
}