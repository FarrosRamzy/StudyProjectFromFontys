#include <Arduino.h>
#include "MyRobotMQTT.hpp"

WiFiClient robot_wifi_client;
MyRobotMQTT my_robot_mqtt(robot_wifi_client, MY_MQTT_HOST_SERVER, MY_NETWORK_PORT, MY_ID);
HardwareSerial stm_serial(1);

uint32_t start_time;
uint32_t current_time;
char stm_input[32];

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  stm_serial.begin(9600, SERIAL_8N1, 16, 17);
  start_time = millis();
  current_time = 0;
  WiFi.begin(MY_NETWORK_SSID, MY_NETWORK_PASSWORD);

  Serial.println("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED && (millis() - start_time >= WIFI_CONNECT_TIMEOUT))
  {
    start_time = millis();
    // NOTE - Wait to connect or timeout.
  }

  Serial.println("Connected to WiFi!");
  Serial.println("subscribing.");

  my_robot_mqtt.subscribeToMyNetwork(SPEED_TOPIC);
  my_robot_mqtt.subscribeToMyNetwork(DIRECTION_TOPIC);
}

void loop()
{
  current_time = millis();
  if (current_time - start_time >= COM_DELAY)
  {
    //NOTE - WiFi communication took at least 1 second to connect.
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Connection lost, restarting device!");
      ESP.restart();
    }

    if (!my_robot_mqtt.amIconnected())
    {
      //re-subscribe to network on connection lost.
      Serial.println("re-subscribing.");
      my_robot_mqtt.connectToMyNetwork();
      my_robot_mqtt.subscribeToMyNetwork(SPEED_TOPIC);
      my_robot_mqtt.subscribeToMyNetwork(DIRECTION_TOPIC);
    }

    my_robot_mqtt.myNetLoop();
    start_time = current_time;
  }

  //always read serial input.
  if (stm_serial.available() > 0)
  {
    String serial_input = stm_serial.readStringUntil('\n');
    serial_input.trim();
    readMySerialInput(serial_input);
  }
}

/**
 * @brief function to sort serial input before processing the message.
 * 
 * @param data 
 */
void readMySerialInput(String data)
{
  static String message_buffer = ""; // Buffer to store the incoming message

  for (char incoming_char : data)
  {
    if (incoming_char == START_MSG)
    {
      // Start of the message
      message_buffer = "";
    }
    else if (incoming_char == END_MSG)
    {
      // End of the message
      if (message_buffer.startsWith(SPEED_INDICATOR))
      {
        processSpeedMessage(message_buffer);
      }
      else
      {
        processDirectionMessage(message_buffer);
      }
      message_buffer = ""; // Clear the buffer for the next message
    }
    else
    {
      // Append the character to the buffer
      message_buffer += incoming_char;
    }
  }
}

/**
 * @brief A message processor to publish speed data of the robot.
 * 
 * @param message 
 */
void processSpeedMessage(String message)
{
  // Split the message into fields
  int split_index = message.indexOf(SPLIT_MSG);
  if (split_index != -1)
  {
    String speed_value = message.substring(split_index + 1);
    float speed = speed_value.toFloat();

    if (speed < 0)
    {
      speed = 0.00;
    }
    // Send to mqtt topic.
    char speed_to_publish[10];
    sprintf(speed_to_publish, "%.2f\r\n", speed);
    my_robot_mqtt.publishToMyNetwork(SPEED_TOPIC, speed_to_publish);
  }
  else
  {
    // Handle the case where the message is not formatted correctly
    Serial.println("Invalid message format");
  }
}

/**
 * @brief A message processor to publish direction data of the robot.
 * 
 * @param message 
 */
void processDirectionMessage(String message)
{
  const char *direction_to_publish = message.c_str();
  my_robot_mqtt.publishToMyNetwork(DIRECTION_TOPIC, direction_to_publish);
}