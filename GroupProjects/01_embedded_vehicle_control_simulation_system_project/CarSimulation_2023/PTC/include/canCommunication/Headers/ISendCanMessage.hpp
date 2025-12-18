#pragma once

namespace canCommunication
{
    class ISendCanMessage
    {
    public:
        virtual void sendMessage(MessageId messageId, MessageValue value) = 0;
        virtual void sendMessage(MessageId messageId, String value) = 0;
    };
}
