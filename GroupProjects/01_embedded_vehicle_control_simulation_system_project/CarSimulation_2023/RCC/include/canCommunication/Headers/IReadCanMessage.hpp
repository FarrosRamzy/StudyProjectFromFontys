#pragma once

namespace canCommunication
{
    class IReadCanMessage
    {
    public:
        // virtual MessageValue readStaticMessage(MessageId &id) = 0;
        virtual String readMessage(MessageId *id) = 0;
    };
}
