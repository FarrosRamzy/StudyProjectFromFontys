#include "../include/canCommunication/Headers/canManager.hpp"

namespace canCommunication
{
    canManager::canManager() : can(SPI_CS_PIN)
    {
    }

    void canManager::canConfig()
    {
        canStartTime = millis();
        while (CAN_OK != can.begin(CAN_500KBPS))
        {
            if (millis() - canStartTime > CAN_BEGIN_WAITING_PERIOD)
            {
                Serial.println("CAN bus init failed");
                canStartTime = millis();
            }
        }
        Serial.println("CAN bus init successful!");
    }

    String canManager::readMessage(MessageId *id)
    {
        String data = "";
        if (CAN_MSGAVAIL == can.checkReceive())
        {
            unsigned char len = 0;
            unsigned char buf[CAN_MAX_CHAR_IN_MESSAGE];

            can.readMsgBuf(&len, buf);

            *id = (canCommunication::MessageId)can.getCanId();

            for (int i = 0; i < len; i++)
            {
                data = data + buf[i];
            }
            memset(buf, 0, sizeof(buf));
        }

        return data;
    }

    void canManager::sendMessage(MessageId messageId, MessageValue value)
    {
        uint8_t stmp[1] = {(uint8_t)value};

        byte sendStatus = can.sendMsgBuf((uint16_t)messageId, 0, 1, stmp);
        if (sendStatus == CAN_OK)
        {
            Serial.print("Command sent. ID: 0x");
            Serial.println((uint16_t)messageId, HEX);
            Serial.println(stmp[0]);
        }
        else
        {
            Serial.println("CONNECTION ERROR");
        }
    }
    
    void canManager::sendMessage(MessageId messageId, String value)
    {
        uint8_t stmp[MAX_CHAR_IN_MESSAGE];
        uint8_t stmp_len;

        value.getBytes(stmp, MAX_CHAR_IN_MESSAGE);
        stmp_len = value.length();

        byte sendStatus = can.sendMsgBuf((uint16_t)messageId, 0, stmp_len, stmp);
        if (sendStatus == CAN_OK)
        {
            Serial.print("Command sent. ID: 0x");
            Serial.println((uint16_t)messageId, HEX);
            Serial.println(stmp[0]);
        }
        else
        {
            Serial.println("CONNECTION ERROR");
        }
    }
}