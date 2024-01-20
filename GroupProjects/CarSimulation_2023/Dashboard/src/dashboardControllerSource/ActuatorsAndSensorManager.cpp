#include "../include/dashboardController/ActuatorsAndSensorManager.hpp"

int prevValue = 0;

bool buttonStateHeadlights = false;
bool headlightsStateHeadlights = false;

bool buttonStateHandBreak = false;
bool StateHandBreak = false;

void ActuatorsAndSensor::Manager::ActuatorsAndSensorSetup()
{
    pinMode(breakPIN, INPUT_PULLUP);
    pinMode(gaspeddalPIN, INPUT_PULLUP);
    pinMode(breakPedalPin, INPUT_PULLUP);
    pinMode(headlightsPIN, INPUT_PULLUP);

    Display.lcd.init();
    Display.lcd.backlight();

    canmanager.canConfig();
}

void ActuatorsAndSensor::Manager::updateSpeed()
{
    if (breakPedal.decreaseSpeed(breakPedalPin))
    {
        if (canmanager.sendMessage(MessageId::MESSAGE_ID_SPEED_UP, MessageValue::MESSAGE_VALUE_ON) != 1)
        {
            Display.displayAlert("Engine ECU down");
        }
    }

    if (gasPedal.increaseSpeed(gaspeddalPIN))
    {
        if (canmanager.sendMessage(MessageId::MESSAGE_ID_SPEED_DOWN, MessageValue::MESSAGE_VALUE_ON) != 1)
        {
            Display.displayAlert("Engine ECU down");
        }
    }

    // if (HandBreak.IsHandBreakPulled(breakPIN))
    // {
    //     canmanager.sendMessage(MessageId::MESSAGE_ID_STOP, MessageValue::MESSAGE_VALUE_ON);
    // }

    bool currentState = HandBreak.IsHandBreakPulled(breakPIN);

    if (currentState && !buttonStateHandBreak)
    {
        StateHandBreak = true;

        StateHandBreak = !StateHandBreak;

        Serial.println(StateHandBreak ? "HIGH" : "LOW");

        if (canmanager.sendMessage(MessageId::MESSAGE_ID_STOP, MessageValue ::MESSAGE_VALUE_ON) != 1)
        {
            Display.displayAlert("Engine ECU down");
        }
    }
    else if (!currentState)
    {
        buttonStateHandBreak = false;
    }
}

void ActuatorsAndSensor::Manager::updateHeadlights()
{
    bool currentState = headlightsController.doHeadlightsNeedToTurnOn(headlightsPIN);

    if (currentState && !buttonStateHeadlights)
    {
        buttonStateHeadlights = true;

        headlightsStateHeadlights = !headlightsStateHeadlights;

        Serial.println(headlightsStateHeadlights ? "HIGH" : "LOW");

        if (canmanager.sendMessage(MessageId::MESSAGE_ID_CONTROL_HEADLIGHTS,
                                   headlightsStateHeadlights ? MessageValue::MESSAGE_HEADLIGHTS_TURN_ON
                                                             : MessageValue::MESSAGE_HEADLIGHTS_TURN_OFF) != 1)
        {
            Display.displayAlert("Headlight ECU down");
        }
    }
    else if (!currentState)
    {
        buttonStateHeadlights = false;
    }
}

void ActuatorsAndSensor::Manager::updateIndiactor()
{
    int value = TurnIndicator.readIndiacator(potentiometerPIN);
    int isInidcatorRight = TurnIndicator.isRightIndicator(value, prevValue);

    if (value != prevValue)
    {
        if (isInidcatorRight == 1)
        {
            if (canmanager.sendMessage(MessageId::MESSAGE_ID_CONTROL_INDICATORS, MessageValue::MESSAGE_INDICATORS_TURN_ON_RIGHT) != 1)
            {
                Display.displayAlert("indicate ECU down");
            }
        }
        else if (isInidcatorRight == 0)
        {
            if (canmanager.sendMessage(MessageId::MESSAGE_ID_CONTROL_INDICATORS, MessageValue::MESSAGE_INDICATORS_TURN_ON_LEFT) != 1)
            {
                Display.displayAlert("indicate ECU down");
            }
        }
        else if (isInidcatorRight == 2)
        {
            if (canmanager.sendMessage(MessageId::MESSAGE_ID_CONTROL_INDICATORS, MessageValue::MESSAGE_INDICATORS_TURN_OFF_LEFT) != 1)
            {
                Display.displayAlert("indicate ECU down");
            }
            if (canmanager.sendMessage(MessageId::MESSAGE_ID_CONTROL_INDICATORS, MessageValue::MESSAGE_INDICATORS_TURN_OFF_RIGHT) != 1)
            {
                Display.displayAlert("indicate ECU down");
            }
        }
    }
    prevValue = value;
}

void ActuatorsAndSensor::Manager::handleReceivedMessage()
{
    MessageId message_id;
    String msg = canmanager.readMessage(message_id);

    switch (message_id)
    {
    case MessageId::MESSAGE_ID_ENGINE_TEMPERATURE_TOO_HIGH:
        Serial.println("Engine temp too high");
        Display.clearLCD();
        Display.displayAlert("Engine temp too high");
        break;
    case MessageId::MESSAGE_ID_TIRE_PRESSURE_TOO_LOW:
        Serial.println("Tire pressure too low)");
        Display.clearLCD();
        Display.displayAlert("Tire pressure too low");
        break;
    case MessageId::MESSAGE_ID_SHOW_PRESSURE:
        Serial.println("Pressure: some value");
        Display.clearLCD();
        Display.displaySpeed("Pres:" + msg);
        break;
    case MessageId::MESSAGE_ID_SHOW_TEMPERATURE:
        Serial.println("Temperature: some value");
        Display.clearLCD();
        Display.displaySpeed("Temp:" + msg);
        break;
    default:
        break;
    }
}

void ActuatorsAndSensor::Manager::loopManager()
{
    updateSpeed();
    delay(10);
    updateIndiactor();
    delay(10);

    updateHeadlights();
    delay(10);
    handleReceivedMessage();
    delay(10);
}