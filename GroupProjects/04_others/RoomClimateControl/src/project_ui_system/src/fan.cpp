#include <room_system.h>

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

void setManualSpeed(uint32_t *speed, uint32_t *previousSpeed, char gasStatus[], bool *autoMode) //, unsigned long *startTime)
{
    if ((strcmp("Danger", gasStatus) == 0))
    {
        *autoMode = true;
        *speed = 5;
        analogWrite(FAN_PWM_PIN, map(*speed, 0, 5, 0, 255));
    }
    else
    {
        bool Once = false;
        if (*previousSpeed != *speed && (*previousSpeed == 0 || *previousSpeed == 1))
            Once = true;
        if (Once)
        {
            analogWrite(FAN_PWM_PIN, 255);
            delay(40); // Due to the complexity of turning a fan on with low PWM signal
                       // it is much more simple at the current stage of our knowledge to
                       // make use of a delay in order to give enough time for the PUSH of the fan to occur.
            Once = false;
            *previousSpeed = *speed;
        }
        uint32_t actualSpeed = map(*speed, 0, 5, 0, 255);
        analogWrite(FAN_PWM_PIN, actualSpeed);
        *previousSpeed = *speed;
    }
}

void adjustFanSpeed(uint32_t setTempVal, uint32_t *fanValue, float readTempVal, float humidVal, char gasStatus[])//, bool *autoTemp)
{
    if ((strcmp("Danger", gasStatus) == 0))
    {
        // Danger state, harmful environment
        *fanValue = 5;
        analogWrite(FAN_PWM_PIN, map(*fanValue, 0, 5, 0, 255));
    }
    else
    {

        // Not danger => Normal environment again.
        if ((setTempVal > (readTempVal + 2)) && humidVal >= HIGHEST_HUMIDITY)
        {
            *fanValue = 5;
            analogWrite(FAN_PWM_PIN, map(*fanValue, 0, 5, 0, 255));
        }
        else if (setTempVal > (readTempVal + 2))
        {
            *fanValue = 5;
            analogWrite(FAN_PWM_PIN, map(*fanValue, 0, 5, 0, 255));
        }
        else if ((setTempVal < (readTempVal - 2)) && humidVal >= HIGHEST_HUMIDITY)
        {
            *fanValue = 5;
            analogWrite(FAN_PWM_PIN, map(*fanValue, 0, 5, 0, 255));
        }
        else if (setTempVal < (readTempVal - 2))
        {
            *fanValue = 5;
            analogWrite(FAN_PWM_PIN, map(*fanValue, 0, 5, 0, 255));
        }
        else if (humidVal < NORMAL_HUMIDITY)
        {
            *fanValue = 3;
            analogWrite(FAN_PWM_PIN, map(*fanValue, 0, 5, 0, 255));
        }
        else
        {
            *fanValue = 4;
            analogWrite(FAN_PWM_PIN, map(*fanValue, 0, 5, 0, 255));
        }
    }
}