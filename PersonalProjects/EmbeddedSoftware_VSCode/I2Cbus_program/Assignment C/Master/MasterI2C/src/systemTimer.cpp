#include <Arduino.h>
#include <systemTimer.h>

/**
 * @brief Construct a new system Timer::system Timer object
 * 
 * @param systemRunDuration 
 */
systemTimer::systemTimer(unsigned long systemRunDuration)
{
    duration = systemRunDuration;
    autoRestarts = true;
}

/**
 * @brief Destroy the system Timer::system Timer object
 * (In this program, it is actually not needed)
 */
systemTimer::~systemTimer()
{
    //--------------
}

/**
 * @brief get the current state of the system timer (if the timer is active during the duration or not)
 * 
 * @return true 
 * @return false 
 */
bool systemTimer::isActive()
{
    return isRunning;
}

/**
 * @brief check if the active timer duration has passed or not by the system. If it is passed, the system timer will reset the startTime. If it is not passed or not even active, the system will not reset the timer.
 * 
 * @return true 
 * @return false 
 */
bool systemTimer::isPassed()
{
    if (!isRunning)
    {
        return false;
    }
    
    if (millis() - startTime > duration)
    {
        resetSystem();
        if (autoRestarts)
        {
            isRunning = true;
            startTime = millis();
        }
        return true;
    }
    
    return false;
}

/**
 * @brief set the timer to start by initiate the start time and set the isRunning bolean to true.
 * 
 */
void systemTimer::startSystem()
{
    Serial.println("timer_start");
    isRunning = true;
    startTime = millis();
}

/**
 * @brief reset the run timer boolean state to false.
 * 
 */
void systemTimer::resetSystem()
{
    isRunning = false;
}

/**
 * @brief setup the timer duration based on the set parameter.
 * 
 * @param systemRunDuration 
 */
void systemTimer::setDuration(unsigned long systemRunDuration)
{
    duration = systemRunDuration;
}

/**
 * @brief set the timer to do auto restart or not by using the input boolean parameter.
 * 
 * @param setValue 
 */
void systemTimer::setAutoRestart(bool setValue = true)
{
    autoRestarts = setValue;
}