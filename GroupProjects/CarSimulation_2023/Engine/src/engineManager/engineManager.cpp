#include "../include/engineManager/engineManager.hpp"

void EngineCanManager::engineCanManagerSetup()
{
    myCanManager.canConfig();
    myServoControl.servoAttach(servoPin);
    myServoControl.myServo.write(1600);
}

void EngineCanManager::handleCanMessage()
{
    MessageId messageId;
    String msg = myCanManager.readMessage(messageId);

    switch (messageId)
    {
    case MessageId::MESSAGE_ID_SPEED_UP:
        myServoControl.speedUp();
        Serial.println("speedUp");
        break;

    case MessageId::MESSAGE_ID_SPEED_UP_REMOTE:
        for (int i = 0; i < 10; i++)
        {
            myServoControl.speedUp();
            Serial.println("speedUp");
        }
        break;

    case MessageId::MESSAGE_ID_SPEED_DOWN:
        myServoControl.slowDown();
        Serial.println("SpeedDown");
        break;

    case MessageId::MESSAGE_ID_SPEED_DOWN_REMOTE:
        for (int i = 0; i < 10; i++)
        {
            myServoControl.slowDown();
            Serial.println("SpeedDown");
        }
        break;

    case MessageId::MESSAGE_ID_STOP:
        for (int i = 0; i < 100; i++)
        {
            myServoControl.handBreak();
            Serial.println("handBreak");
        }
        break;

    case MessageId::MESSAGE_ID_STOP_REMOTE:
        for (int i = 0; i < 10; i++)
        {
            myServoControl.handBreak();
            Serial.println("handBreak");
        }
        break;
    case MessageId::MESSAGE_ID_ENGINE_TEMPERATURE_TOO_HIGH:
        for (int i = 0; i < 100; i++)
        {
            myServoControl.handBreak();
            Serial.println("handBreak");
        }
        break;
    case MessageId::MESSAGE_ID_TIRE_PRESSURE_TOO_LOW:
        for (int i = 0; i < 100; i++)
        {
            myServoControl.handBreak();
            Serial.println("handBreak");
        }
        break;
    default:
        break;
    }
}
