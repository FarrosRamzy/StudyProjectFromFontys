#include "../include/remoteController/MyRemoteMQTT.hpp"

MyRemoteMQTT::MyRemoteMQTT(WiFiClient &the_client, const char *the_server, int the_port,
                           const char *the_id,
                           void (*externalCallback)(char *, byte *, unsigned int))
    : my_mqtt_client(the_client), esp_client(the_client), my_server(the_server),
      my_net_port(the_port), my_id(the_id)
{
    my_mqtt_client.setServer(my_server, my_net_port);
    my_mqtt_client.setCallback(externalCallback);
}

MyRemoteMQTT::~MyRemoteMQTT()
{
    ;
}

void MyRemoteMQTT::setServer(const char *the_server)
{
    my_server = the_server;
    my_mqtt_client.setServer(my_server, my_net_port);
}

void MyRemoteMQTT::setPort(int the_port)
{
    my_net_port = the_port;
    my_mqtt_client.setServer(my_server, my_net_port);
}

void MyRemoteMQTT::myCallBackFunction(MQTT_CALLBACK_SIGNATURE)
{
    my_mqtt_client.setCallback(callback);
}

void MyRemoteMQTT::connectToMyNetwork()
{
    static uint32_t lastConnectingAttempt = 0;

    if ((millis() - lastConnectingAttempt) >= COM_DELAY)
    {
        Serial.println("Connecting");
        if (my_mqtt_client.connect(my_id))
        {
            Serial.println("Connected!");
        }
        else
        {
            Serial.print("fail status: ");
            Serial.print(my_mqtt_client.state());
        }
        lastConnectingAttempt = millis();
    }
}

void MyRemoteMQTT::myNetLoop()
{
    if (!amIconnected())
    {
        connectToMyNetwork();
    }
    else
    {
        my_mqtt_client.loop();
    }
}

bool MyRemoteMQTT::amIconnected()
{
    return my_mqtt_client.connected();
}