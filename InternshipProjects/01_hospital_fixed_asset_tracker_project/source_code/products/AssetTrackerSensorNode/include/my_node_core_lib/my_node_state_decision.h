#pragma once

enum MyNodeAction
{
    ACTION_NONE,
    ACTION_TRY_WIFI,
    ACTION_TRY_PROVISION,
    ACTION_TRY_MQTT,
    ACTION_PUBLISH_HEARTBEAT,
    ACTION_READ_RFID
};

MyNodeAction decideNextNodeAction(
    bool wifi_connected,
    bool provisioned,
    bool mqtt_connected,
    bool heartbeat_due);
