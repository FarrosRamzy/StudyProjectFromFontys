#include "button.h"
#include <Arduino.h>

button::button(int pinNumber, int debounceDelay)
{
    m_pinNumber = pinNumber;
    m_debounceDelay = debounceDelay;
    m_lastDebounceTime = 0;
    m_state = 0;
    pinMode(pinNumber, INPUT_PULLUP);
}

bool button::pressed()
{
    bool currentState = digitalRead(m_pinNumber);
    if ((millis() - m_lastDebounceTime) > m_debounceDelay)
    { 
        if (currentState != m_state)
        { // check if the state has changed
            m_lastDebounceTime = millis();
            m_state = currentState; // remember the previous state
        }
    }
    return m_state;
}
