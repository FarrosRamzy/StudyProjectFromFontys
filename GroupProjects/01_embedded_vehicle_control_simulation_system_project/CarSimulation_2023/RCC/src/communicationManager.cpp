// #include "communicationManager.hpp"

// uint32_t start_time;
// uint32_t current_time;

// communicationManager::communicationManager() : esp_client(), my_remote_mqtt(esp_client, MY_MQTT_HOST_SERVER, MY_NETWORK_PORT, MY_ID, callback){}
// communicationManager::~communicationManager() {}

// void communicationManager::initializeNetwork()
// {
//     ;
// }

// void communicationManager::callback(char *topic, byte *payload, unsigned int length)
// {   
//     String message = "";

//     /*NOTE - This function mostly only for receive message from remote.
//              The publish message should be added in functions which operates
//              response from the CAN messages.*/

//     for (int i = 0; i < length; i++)
//     {
//         message += (char)payload[i];
//     }

//     if (strcmp(topic, LIGHTING_TOPIC) == 0)
//     {
//         sortCommandToLighting(message);
//     }

//     if (strcmp(topic, ENGINE_TOPIC) == 0)
//     {
//         sortCommandToEngine(message);
//     }
// }