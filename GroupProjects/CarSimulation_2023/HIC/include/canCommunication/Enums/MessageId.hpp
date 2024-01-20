#pragma once

namespace canCommunication
{
    enum class MessageId
    {
        MESSAGE_ID_STOP = 0x001,
        MESSAGE_ID_SPEED_DOWN = 0x005,
        MESSAGE_ID_SPEED_UP = 0x009,
        MESSAGE_ID_ENGINE_TEMPERATURE_TOO_HIGH = 0x00D,
        MESSAGE_ID_TIRE_PRESSURE_TOO_LOW = 0x011,
        MESSAGE_ID_CONTROL_HEADLIGHTS = 0x015,
        MESSAGE_ID_CONTROL_INDICATORS = 0x019,
        MESSAGE_ID_SHOW_PRESSURE = 0x01D,
        MESSAGE_ID_SHOW_TEMPERATURE = 0x021,
        MESSAGE_ID_STOP_REMOTE = 0x025,
        MESSAGE_ID_SPEED_DOWN_REMOTE = 0x029,
        MESSAGE_ID_SPEED_UP_REMOTE = 0x02D,
        MESSAGE_ID_CONTROL_HEADLIGHTS_REMOTE = 0x031,
        MESSAGE_ID_CONTROL_INDICATORS_REMOTE = 0x035,
        MESSAGE_ID_ENUM_LENGTH = 0x00E // If an element is added or deleted, change this
    };
}