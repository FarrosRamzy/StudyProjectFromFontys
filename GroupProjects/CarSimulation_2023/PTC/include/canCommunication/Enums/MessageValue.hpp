#pragma once

namespace canCommunication
{
    enum class MessageValue
    {
        INVALID_MESSAGE = -1,
        MESSAGE_VALUE_ON = 1,
        MESSAGE_HEADLIGHTS_TURN_OFF = 2,
        MESSAGE_HEADLIGHTS_TURN_ON = 3,
        MESSAGE_INDICATORS_TURN_OFF_LEFT = 4,
        MESSAGE_INDICATORS_TURN_ON_LEFT = 5,
        MESSAGE_INDICATORS_TURN_OFF_RIGHT = 6,
        MESSAGE_INDICATORS_TURN_ON_RIGHT = 7
    };
}