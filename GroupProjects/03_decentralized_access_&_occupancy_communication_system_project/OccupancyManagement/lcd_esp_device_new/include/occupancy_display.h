#ifndef OCCUPANCY_DISPLAY_H
#define OCCUPANCY_DISPLAY_H

#include <LiquidCrystal.h>
#include <PubSubClient.h>
#include <EspMQTTClient.h>
#include <WiFi.h>

#define MY_NETWORK_SSID "Kiwy"
#define MY_NETWORK_PASSWORD "aquamagic22"
#define MY_NETWORK_SITE "192.168.117.23"
#define MY_NETWORK_PORT 1883

#define MY_DEVICE_IDENTITY "CommGroup-Display"
#define MY_COUNTER_TOPIC "group4Industry/counter"
#define MY_EMERGENCY_TOPIC "group4Industry/emergency"
#define MY_FASTEST_QUEUE_TOPIC "group4Industry/fastestQueue"

#define GATE_1_DISCONNECTED "Gate 1 broken"
#define GATE_2_DISCONNECTED "Gate 2 broken"
#define GATE_3_DISCONNECTED "Gate 3 broken"

#define GATE_1 "gate1"
#define GATE_2 "gate2"
#define GATE_3 "gate3"

#define MAX_DISPLAY_SWITCH_TIME 3000
#define MAX_OCCUPANCY_NUMBER 10

/**
 * @brief enum state of displaying the occupancy data.
 * 
 */
enum MY_DISPLAY_STATE
{
    SHOW_OCC,
    SHOW_FASTEST_QUEUE,
    SHOW_EMERGENCY,
};

const int input_miso = 19;
const int output_mosi = 23;
const int digital_4 = 26;
const int digital_5 = 32;
const int digital_6 = 27;
const int digital_7 = 13;

/**
 * @brief Class of the display functions.
 * 
 */
class MyDataDisplay
{
private:
    //
public:
    void showMyOccupancy(String);
    void showEmergency(String);
    void showMyFastestQueue(String);
    void showAdisconnectedGate(String);
    void showOccNotification();
};

/**
 * @brief Class of Wi-Fi & MQTT functions.
 * 
 */
class MyStartConnection
{
private:
    //
public:
    void connectToMyWiFi();
    void connectToMyMQTT();
    bool reconnectMyMQTT();
};

WiFiClient myWiFiClient;
PubSubClient mySubscribeClient(myWiFiClient);
LiquidCrystal lcd(input_miso, output_mosi, digital_4, digital_5, digital_6, digital_7);
MyStartConnection myStartConnect;
MyDataDisplay myDisplayData;

void callback(char *, byte *, unsigned int);

String myReadInput(byte *, unsigned int);

#endif