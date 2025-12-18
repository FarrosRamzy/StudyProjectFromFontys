#pragma once

namespace canCommunication
{
    class ISendCanMessage
    {
    public:
        virtual void sendMessage(MessageId messageId, MessageValue value) = 0;
    };
}
