#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <HardwareSerial.h>
// #include <stdio.h>

//Internet & MQTT credentials
#define INTERNET_SSID "LukaWifi"//"MSI_YZMAR"
#define INTERNET_PASSWORD "Eindhoven1!"//"Yzmar252887"
#define INTERNET_PORT 1883
#define MY_MQTT_BROKER_SITE "test.mosquitto.org"
#define MY_DEVICE_NAME "A-robot"
#define MY_MQTT_TOPIC "robot/data_in"
#define MY_MQTT_SUB_TOPIC "robot/set_distance"

WiFiClient WiFiclient;
PubSubClient subClient(WiFiclient);

HardwareSerial stmSerial(2);
char STMinputMsg[16];

void connectToWiFi();
void connectMQTT();
void callback(char *, byte *, unsigned int);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  stmSerial.begin(115200, SERIAL_8N1, 16, 17);
  connectToWiFi();
  connectMQTT();
}

void loop()
{
  // check esp -> MQTT connection.
  if (!subClient.connected())
  {
    while (!subClient.connected())
    {
      if (subClient.connect(MY_MQTT_SUB_TOPIC))
      {
        subClient.subscribe(MY_MQTT_SUB_TOPIC);
      }
      else
      {
        Serial.print(".");
        delay(100);
      }
    }
  }

  //read input from STM32 via UART.
  if (stmSerial.available() > 0)
  {
    int availableByteNumber = stmSerial.available();
    for (int i = 0; i < availableByteNumber; i++)
    {
      STMinputMsg[i] = stmSerial.read();
    }
    Serial.println(STMinputMsg);
    subClient.publish(MY_MQTT_TOPIC, STMinputMsg);
    memset(STMinputMsg,0,16);
    delay(10);
  }

  //loop connection.
  subClient.loop();
}

//connect ESP to WiFi.
void connectToWiFi()
{
  WiFi.begin(INTERNET_SSID, INTERNET_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
}

//connect MQTT server.
void connectMQTT()
{
  subClient.setServer(MY_MQTT_BROKER_SITE, INTERNET_PORT);
  subClient.setCallback(callback);
}

//read input data from MQTT and transfer it to STM32 serial.
void callback(char *topic, byte *payload, unsigned int length)
{
  String inputMsg;
  for (int i = 0; i < length; i++)
  {
    inputMsg += (char)payload[i];
  }
  stmSerial.print(inputMsg + '\n');
  Serial.println("incoming msg: " + inputMsg);
}