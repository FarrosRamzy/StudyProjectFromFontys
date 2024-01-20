#pragma once

#include <Arduino.h>
#include <SPI.h>
#include "mcp2515_can.h"

#include "../include/canCommunication/Enums/MessageId.hpp"
#include "../include/canCommunication/Enums/MessageValue.hpp"
#include "../include/canCommunication/Headers/IReadCanMessage.hpp"
#include "../include/canCommunication/Headers/ISendCanMessage.hpp"

namespace canCommunication
{
#define SPI_CS_PIN 5
#define CAN_BEGIN_WAITING_PERIOD 100

    class canManager : public IReadCanMessage, public ISendCanMessage
    {
    public:
        canManager();
        void canConfig();
        // MessageValue readStaticMessage(MessageId &id) override;
        String readMessage(MessageId *id) override;
        void sendMessage(MessageId messageId, MessageValue value) override;
        void sendMessage(MessageId messageId, String value) override;

    private:
        mcp2515_can can;
        unsigned long long canStartTime;
    };
}