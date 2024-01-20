#include <traffic_m.h>

SoftwareSerial trafficSerial(7, 8);
unsigned long startTimer = millis();

int redState;

String c;

void setupTraffic()
{
    trafficSerial.begin(9600);
}

void trafficStart(trafficStates *state)
{
    allLEDOff();
    *state = IDLE;
}

void trafficIdle(trafficStates *state)
{
    trafficSerial.print(START_PING "\n");
    *state = LISTEN;
}

void trafficListen(trafficStates *state)
{
    if (trafficSerial.available())
    {
        c = trafficSerial.readStringUntil('\n');
        if (c == REPLY_PING)
        {
            Serial.println(c);
            startTimer = millis();
            c = "";
            Serial.println("SET_TRAFFIC");
            redLEDOn();
            *state = SET_RED;
        }
    }
    else if (millis() - startTimer > MSG_DEBOUNCE_DELAY)
    {
        startTimer = millis();
        c = "";
        Serial.println("BROADCAST");
        *state = IDLE;
    }
}

void setTraffic(trafficStates *state)
{
    if (millis() - startTimer > WAIT_SET_TRAFFIC)
    {
        Serial.println("SLAVE->GO");
        trafficSerial.print(GO "\n");
        if (trafficSerial.available())
        {
            c = trafficSerial.readStringUntil('\n');
            if (c == ACK)
            {
                Serial.println("SLAVE: " + c);
                startTimer = millis();
                c = "";
                redState = 0;
                Serial.println("MASTER: STOP");
                *state = RED;
            }
            else if (c == NACK)
            {
                startTimer = millis();
                c = "";
                allLEDOff();
                *state = BLINK_ON;
            }
        }
        else if (millis() - startTimer > (WAIT_SET_TRAFFIC + MSG_DEBOUNCE_DELAY))
        {
            Serial.println("TRAFFIC_CUT_OUTED");
            startTimer = millis();
            allLEDOff();
            *state = BLINK_ON;
        }
    }
}

void trafficStop(trafficStates *state)
{
    switch (redState)
    {
    case 0:
        if (millis() - startTimer > WAIT_IN_GREEN)
        {
            Serial.println("SLAVE->SLOW_DOWN");
            trafficSerial.print(SLOW_DOWN "\n");
            if (trafficSerial.available())
            {
                c = trafficSerial.readStringUntil('\n');
                if (c == ACK)
                {
                    Serial.println("SLAVE: " + c);
                    startTimer = millis();
                    c = "";
                    redState = 1;
                }
                else if (c == NACK)
                {
                    startTimer = millis();
                    c = "";
                    allLEDOff();
                    *state = BLINK_ON;
                }
            }
            else if (millis() - startTimer > (WAIT_IN_GREEN + MSG_DEBOUNCE_DELAY))
            {
                Serial.println("TRAFFIC_CUT_OUTED");
                startTimer = millis();
                redState = 0;
                allLEDOff();
                *state = BLINK_ON;
            }
        }
        break;
    case 1:
        if (millis() - startTimer > WAIT_IN_YELLOW)
        {
            Serial.println("SLAVE->STOP");
            trafficSerial.print(STOP "\n");
            if (trafficSerial.available())
            {
                c = trafficSerial.readStringUntil('\n');
                if (c == ACK)
                {
                    Serial.println("SLAVE: " + c);
                    startTimer = millis();
                    c = "";
                    redState = 0;
                    Serial.println("MASTER: GO");
                    redLEDOff();
                    greenLEDOn();
                    *state = GREEN;
                }
                else if (c == NACK)
                {
                    startTimer = millis();
                    c = "";
                    allLEDOff();
                    *state = BLINK_ON;
                }
            }
            else if (millis() - startTimer > (WAIT_IN_YELLOW + MSG_DEBOUNCE_DELAY))
            {
                Serial.println("TRAFFIC_CUT_OUTED");
                startTimer = millis();
                redState = 0;
                allLEDOff();
                *state = BLINK_ON;
            }
        }
        break;
    }
}

void trafficGo(trafficStates *state)
{
    if (millis() - startTimer > WAIT_IN_RED)
    {
        trafficSerial.print(CHECK "\n");
        if (trafficSerial.available())
        {
            c = trafficSerial.readStringUntil('\n');
            if (c == ACK)
            {
                Serial.println("SLAVE: " + c);
                if (millis() - startTimer > (WAIT_IN_RED + WAIT_IN_GREEN))
                {
                    startTimer = millis();
                    c = "";
                    Serial.println("MASTER: SLOW_DOWN");
                    greenLEDOff();
                    yellowLEDOn();
                    *state = YELLOW;
                }
            }
            else if (c == NACK)
            {
                startTimer = millis();
                c = "";
                allLEDOff();
                *state = BLINK_ON;
            }
        }
        else if (millis() - startTimer > (WAIT_IN_RED + WAIT_IN_GREEN))
        {
            Serial.println("TRAFFIC_CUT_OUTED");
            startTimer = millis();
            allLEDOff();
            *state = BLINK_ON;
        }
    }
}

void trafficSlow(trafficStates *state)
{
    trafficSerial.print(CHECK "\n");
    if (trafficSerial.available())
    {
        c = trafficSerial.readStringUntil('\n');
        if (c == ACK)
        {
            Serial.println("SLAVE: " + c);
            if (millis() - startTimer > WAIT_IN_YELLOW)
            {
                startTimer = millis();
                c = "";
                Serial.println("MASTER: STOP");
                yellowLEDOff();
                redLEDOn();
                *state = SET_RED;
            }
        }
        else if (c == NACK)
        {
            startTimer = millis();
            c = "";
            allLEDOff();
            *state = BLINK_ON;
        }
    }
    else if (millis() - startTimer > (WAIT_IN_RED + WAIT_IN_YELLOW))
    {
        Serial.println("TRAFFIC_CUT_OUTED");
        startTimer = millis();
        allLEDOff();
        *state = BLINK_ON;
    }
}

void trafficError(trafficStates *state)
{
    if (*state == BLINK_ON)
    {
        trafficSerial.print(START_PING "\n");
        if (trafficSerial.available())
        {
            c = trafficSerial.readStringUntil('\n');
            if (c == REPLY_PING)
            {
                Serial.println(c);
                startTimer = millis();
                yellowLEDOff();
                redLEDOn();
                c = "";
                Serial.println("MASTER: RESTART");
                *state = SET_RED;
            }
        }
        else if (millis() - startTimer > BLINK_DELAY)
        {
            trafficSerial.print(NACK "\n");
            startTimer = millis();
            yellowLEDOff();
            *state = BLINK_OFF;
        }
    }
    else if (*state == BLINK_OFF)
    {
        trafficSerial.print(START_PING "\n");
        if (trafficSerial.available())
        {
            c = trafficSerial.readStringUntil('\n');
            if (c == REPLY_PING)
            {
                Serial.println(c);
                startTimer = millis();
                c = "";
                Serial.println("MASTER: RESTART");
                redLEDOn();
                *state = SET_RED;
            }
        }
        else if (millis() - startTimer > BLINK_DELAY)
        {
            trafficSerial.print(NACK "\n");
            startTimer = millis();
            yellowLEDOn();
            *state = BLINK_ON;
        }
    }
}