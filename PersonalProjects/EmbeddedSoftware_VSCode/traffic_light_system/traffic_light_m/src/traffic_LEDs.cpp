#include <traffic_m.h>

void allLEDOff()
{
    redLEDOff();
    yellowLEDOff();
    greenLEDOff();
}

void redLEDOn()
{
    digitalWrite(RLED, HIGH);
}

void yellowLEDOn()
{
    digitalWrite(YLED, HIGH);
}

void greenLEDOn()
{
    digitalWrite(GLED, HIGH);
}

void redLEDOff()
{
    digitalWrite(RLED, LOW);
}

void yellowLEDOff()
{
    digitalWrite(YLED, LOW);
}

void greenLEDOff()
{
    digitalWrite(GLED, LOW);
}