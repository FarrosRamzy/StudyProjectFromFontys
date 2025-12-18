#include "ISendCANMessage.hpp"
#include "Dashboard.hpp"
#include <Arduino.h>

// Implement the methods defined in ISendCANMessage as needed
void ISendCANMessage::sendHeartbeatPing()
{
    // Implement sendHeartbeatPing
}

void ISendCANMessage::sendError(const std::string &error_message)
{
    // Implement sendError
}

void ISendCANMessage::sendCommand(const std::string &command_message, mcp2515_can CAN)
{
    unsigned long msgID;
    unsigned char msgValue;
    unsigned char stmp[1];

    if (command_message == BREAK)
    {
        msgID = BREAK_MSGID;
        msgValue = BREAK_MSGVALUE;
        stmp[0] = msgValue;
    }
    else if (command_message == SPEED_UP)
    {
        msgID = SPEED_UP_MSGID;
        msgValue = SPEED_UP_MSGVALUE;
        stmp[0] = msgValue;
    }
    else if (command_message == CONTROL_HEADLIGHTS_ON)
    {
        msgID = CONTROL_HEADLIGHTS_ON_MSGID;
        msgValue = CONTROL_HEADLIGHTS_ON_MSGVALUE;
        stmp[0] = msgValue;
    }
    else if (command_message == CONTROL_HEADLIGHTS_OFF)
    {
        msgID = CONTROL_HEADLIGHTS_OFF_MSGID;
        msgValue = CONTROL_HEADLIGHTS_OFF_MSGVALUE;
        stmp[0] = msgValue;
    }
    else if (command_message == CONTROL_INDICATOR_OFF_LEFT)
    {
        msgID = CONTROL_INDICATOR_OFF_LEFT_MSGID;
        msgValue = CONTROL_INDICATOR_OFF_LEFT_MSGVALUE;
        stmp[0] = msgValue;
    }
    else if (command_message == CONTROL_INDICATOR_ON_LEFT)
    {
        msgID = CONTROL_INDICATOR_ON_LEFT_MSGID;
        msgValue = CONTROL_INDICATOR_ON_LEFT_MSGVALUE;
        stmp[0] = msgValue;
    }
    else if (command_message == CONTROL_INDICATOR_OFF_RIGHT)
    {
        msgID = CONTROL_INDICATOR_OFF_RIGHT_MSGID;
        msgValue = CONTROL_INDICATOR_OFF_RIGHT_MSGVALUE;
        stmp[0] = msgValue;
    }
    else if (command_message == CONTROL_INDICATOR_ON_RIGHT)
    {
        msgID = CONTROL_INDICATOR_ON_RIGHT_MSGID;
        msgValue = CONTROL_INDICATOR_ON_RIGHT_MSGVALUE;
        stmp[0] = msgValue;
    }
    else
    {
        Serial.println("Invalid command");
        return;
    }
    CAN.sendMsgBuf(msgID, 0, 1, stmp);
}
