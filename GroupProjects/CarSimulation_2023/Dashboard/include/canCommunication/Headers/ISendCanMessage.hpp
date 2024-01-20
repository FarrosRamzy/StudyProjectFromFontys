#pragma once

namespace canCommunication
{
    class ISendCanMessage
    {
    public:
        virtual int sendMessage(MessageId messageId, MessageValue value) = 0;
    };
}
