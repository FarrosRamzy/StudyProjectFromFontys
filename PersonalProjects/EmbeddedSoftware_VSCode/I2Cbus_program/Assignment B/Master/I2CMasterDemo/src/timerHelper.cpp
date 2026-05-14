#include "timerHelper.h"
#include <Arduino.h>

/**
 * @param timerDuration The duration that the timer runs for, in milliseconds
*/
Timer::Timer(unsigned long timerDuration)
{
    duration = timerDuration;
    autoRestarts = true;
}

Timer::~Timer()
{
    //nothing to destruct
}

/**
 * Starts the timer
*/
void Timer::start()
{
    isRunning = true;
    timeStarted = millis();
}

/**
 * Resets the timer
*/
void Timer::reset()
{
    isRunning = false;
}

/**
 * Determines whether the timer is active or not
*/
bool Timer::isActive()
{
    return isRunning;
}

/**
 * Sets the duration of the timer
 * @param timerDuration The time that the timer should run for, in milliseconds
*/
void Timer::setDuration(unsigned long timerDuration)
{
    duration = timerDuration;
}

/**
 * Determine whether the timer automatically restarts. If no value is passed, it is set to true by default
 * @param value True to enable automatic restarting, False to disable it
*/
void Timer::setAutoRestart(bool value = true)
{
    autoRestarts = value;
}

/**
 * Determines whether the timer has elapsed
*/
bool Timer::isElapsed()
{
    //Guard if
    if (!isRunning)
    {
        //timer not running, therefore cannot be finished
        return false;
    }

    if (millis() - timeStarted > duration)
    {
        reset();

        if (autoRestarts)
        {
            isRunning = true;
            timeStarted = millis();
        }
        
        return true;
    }

    return false;  
}
