#include "../include/Hic/HicManager.hpp"
#include "../include/main.hpp"

String command_val;

HicManager::HicManager(uint8_t leftPin, uint8_t rightPin, uint8_t lightAPin, uint8_t lightBPin)
    : lightSystem(leftPin, rightPin, lightAPin, lightBPin)
{
}

void HicManager::managerConfig()
{
    can_manager.canConfig();
}

void HicManager::handleCanMessage()
{
    MessageId message_id = MessageId::MESSAGE_ID_ENUM_LENGTH;
    command_val = "";

    command_val = can_manager.readMessage(message_id);

    switch (message_id)
    {
    case MessageId::MESSAGE_ID_CONTROL_HEADLIGHTS:
        controlHeadlights();
        break;

    case MessageId::MESSAGE_ID_CONTROL_INDICATORS:
        controlIndicators();
        break;

    case MessageId::MESSAGE_ID_CONTROL_HEADLIGHTS_REMOTE:
        controlHeadlights();
        break;

    case MessageId::MESSAGE_ID_CONTROL_INDICATORS_REMOTE:
        controlIndicators();
        break;

    default:
        break;
    }
}

void HicManager::processIndicators()
{
    if (indicatorsState == MessageValue::MESSAGE_INDICATORS_TURN_ON_LEFT)
        lightSystem.blinkIndicator(LEFT_INDICATOR_PIN, INDICATORS_DELAY);
    else if (indicatorsState == MessageValue::MESSAGE_INDICATORS_TURN_ON_RIGHT)
        lightSystem.blinkIndicator(RIGHT_INDICATOR_PIN, INDICATORS_DELAY);
    else if (indicatorsState == MessageValue::MESSAGE_INDICATORS_TURN_OFF_LEFT || indicatorsState == MessageValue::MESSAGE_INDICATORS_TURN_OFF_RIGHT)
        lightSystem.turnOffIndicators();
}

void HicManager::controlHeadlights()
{
    int val_int = atoi(command_val.c_str());
    if (((MessageValue)val_int) == MessageValue::MESSAGE_HEADLIGHTS_TURN_ON)
        lightSystem.turnOnHeadlights();
    else if (((MessageValue)val_int) == MessageValue::MESSAGE_HEADLIGHTS_TURN_OFF)
        lightSystem.turnOffHeadlights();

    Serial.println("control  headlights");
}

void HicManager::controlIndicators()
{
    indicatorsState = (MessageValue)atoi(command_val.c_str());
}