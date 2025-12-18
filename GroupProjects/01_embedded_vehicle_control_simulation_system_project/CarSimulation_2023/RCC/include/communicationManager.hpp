// #ifndef COMMUNICATION_MANAGER_HPP
// #define COMMUNICATION_MANAGER_HPP

// #include <Arduino.h>
// #include "../include/remoteController/MyRemoteMQTT.hpp"
// #include "../include/remoteController/remoteCanManager.hpp"
// #include <functional>

// using namespace canCommunication;

// class communicationManager
// {
// private:
//     WiFiClient esp_client;
//     MyRemoteMQTT my_remote_mqtt;
// public:
//     communicationManager();
//     ~communicationManager();

//     void initializeNetwork();

//     void callback(char *, byte *, unsigned int);
//     void sortCommandToEngine(String);
//     void sortCommandToLighting(String);
//     void speedUpTheCar();
//     void brakeTheCar();
//     void turnOnHeadlights();
//     void turnOffHeadlights();
//     void turnLeft();
//     void turnRight();
//     void goStraight();

//     bool checkWIFIconnection();
//     bool checkMQTTconnection();

//     void connectToNetwork();
//     bool subscribeToTopics(const char *, const char *, const char *);

//     void initializeCAN();
//     void readCANdata();
//     void writeCANdata(MessageId, MessageValue);
// };

// #endif