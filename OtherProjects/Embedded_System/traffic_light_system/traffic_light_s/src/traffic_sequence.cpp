#include <traffic_s.h>

SoftwareSerial trafficSerial(7, 8);
unsigned long startTimer = millis();

String c;

void setupTraffic()
{
    trafficSerial.begin(9600);
}

void trafficStart(trafficStates *state)
{
    allLEDOff();
    Serial.println("TRAFFIC_START");
    *state = LISTEN;
}

void trafficListen(trafficStates *state)
{
    if (trafficSerial.available())
    {
        Serial.println("LISTEN_TO_MASTER");
        c = trafficSerial.readStringUntil('\n');
        if (c == START_PING)
        {
            Serial.println("MASTER: " + c);
            trafficSerial.write(REPLY_PING "\n");
            startTimer = millis();
            c = "";
            Serial.println("SET_TRAFFIC");
            redLEDOn();
            *state = SET_RED;
        }
    }
}

void setTraffic(trafficStates *state)
{
    if (trafficSerial.available())
    {
        c = trafficSerial.readStringUntil('\n');
        if (c == GO)
        {
            Serial.println("MASTER: " + c);
            trafficSerial.write(ACK "\n");
            startTimer = millis();
            c = "";
            Serial.println("GREEN");
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
    else if (millis() - startTimer > (WAIT_SET_TRAFFIC + MSG_DEBOUNCE_DELAY))
    {
        Serial.println("TRAFFIC_CUT_OUTED");
        startTimer = millis();
        allLEDOff();
        *state = BLINK_ON;
    }
}

void trafficStop(trafficStates *state)
{
    if (trafficSerial.available())
    {
        c = trafficSerial.readStringUntil('\n');
        if (c == CHECK)
        {
            Serial.println("MASTER: " + c);
            trafficSerial.write(ACK "\n");
            startTimer = millis();
            Serial.println("ACK");
            c = "";
        }
        else if (c == GO)
        {
            Serial.println("MASTER: " + c);
            trafficSerial.write(ACK "\n");
            startTimer = millis();
            c = "";
            Serial.println("GREEN");
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
    else if (millis() - startTimer > (WAIT_IN_RED + WAIT_IN_GREEN + WAIT_IN_YELLOW))
    {
        Serial.println("TRAFFIC_CUT_OUTED");
        startTimer = millis();
        allLEDOff();
        *state = BLINK_ON;
    }
}

void trafficGo(trafficStates *state)
{
    if (trafficSerial.available())
    {
        c = trafficSerial.readStringUntil('\n');
        if (c == SLOW_DOWN)
        {
            Serial.println("MASTER: " + c);
            trafficSerial.write(ACK "\n");
            startTimer = millis();
            c = "";
            Serial.println("SLOW_DOWN");
            greenLEDOff();
            yellowLEDOn();
            *state = YELLOW;
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
        allLEDOff();
        *state = BLINK_ON;
    }
}

void trafficSlow(trafficStates *state)
{
    if (trafficSerial.available())
    {
        c = trafficSerial.readStringUntil('\n');
        if (c == STOP)
        {
            Serial.println("MASTER: " + c);
            trafficSerial.write(ACK "\n");
            startTimer = millis();
            c = "";
            Serial.println("STOP");
            yellowLEDOff();
            redLEDOn();
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
    else if (millis() - startTimer > (WAIT_IN_YELLOW + MSG_DEBOUNCE_DELAY))
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
        if (trafficSerial.available())
        {
            c = trafficSerial.readStringUntil('\n');
            if (c == START_PING)
            {
                Serial.println(c);
                trafficSerial.write(REPLY_PING "\n");
                startTimer = millis();
                c = "";
                Serial.println("SLAVE: RESET");
                yellowLEDOff();
                redLEDOn();
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
        if (trafficSerial.available())
        {
            c = trafficSerial.readStringUntil('\n');
            if (c == START_PING)
            {
                Serial.println(c);
                trafficSerial.write(REPLY_PING "\n");
                startTimer = millis();
                c = "";
                Serial.println("SLAVE: RESET");
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