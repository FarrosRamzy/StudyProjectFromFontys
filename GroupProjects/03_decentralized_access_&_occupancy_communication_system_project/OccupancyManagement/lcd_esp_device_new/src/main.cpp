#include <Arduino.h>
#include "occupancy_display.h"

MY_DISPLAY_STATE currentState;

uint32_t startTimer = millis();
uint32_t currentTime = 0;
uint32_t reconnectDelay = 100;

String occupancy_input;
String queue_input;
String gate_info;
String emergency_input;

bool disconnectionNotif;
bool displayMessage;
bool buildingIsFull;
bool aGateIsError;
bool emergency;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  disconnectionNotif = false;
  displayMessage = false;
  buildingIsFull = false;
  emergency = false;
  aGateIsError = false;
  myStartConnect.connectToMyWiFi();
  myStartConnect.connectToMyMQTT();

  currentState = SHOW_OCC;
}

void loop()
{
  if (!mySubscribeClient.connected())
  {
    while (!myStartConnect.reconnectMyMQTT())
    {
      if (!disconnectionNotif)
      {
        lcd.clear();
        lcd.print("Disconnected!");
        disconnectionNotif = true;
      }
    }
  }
  else
  {
    disconnectionNotif = false;
    mySubscribeClient.loop();

    uint32_t currentReceiveMessageTime = millis();
    uint32_t myTimeCalculation = currentReceiveMessageTime - startTimer;

    switch (currentState)
    {
    case SHOW_OCC:
      if (emergency)
      {
        displayMessage = false;
        currentState = SHOW_EMERGENCY;
      }
      else
      {
        if (!displayMessage)
        {
          lcd.clear();
          myDisplayData.showMyOccupancy(occupancy_input);
          displayMessage = true;
        }
        if (myTimeCalculation > MAX_DISPLAY_SWITCH_TIME)
        {
          startTimer = currentReceiveMessageTime;
          displayMessage = false;
          currentState = SHOW_FASTEST_QUEUE;
        }
      }
      break;
    case SHOW_FASTEST_QUEUE:
      if (emergency)
      {
        displayMessage = false;
        currentState = SHOW_EMERGENCY;
      }
      else
      {
        if (queue_input != "" || buildingIsFull)
        {
          if (!displayMessage)
          {
            lcd.clear();
            if (buildingIsFull)
            {
              myDisplayData.showOccNotification();
            }
            else
            {
              myDisplayData.showMyFastestQueue(queue_input);
              queue_input.clear();
            }
            displayMessage = true;
          }
          if (myTimeCalculation > MAX_DISPLAY_SWITCH_TIME)
          {
            startTimer = currentReceiveMessageTime;
            displayMessage = false;
            currentState = SHOW_EMERGENCY;
          }
        }
        else
        {
          currentState = SHOW_EMERGENCY;
        }
      }
      break;
    case SHOW_EMERGENCY:
      if (!emergency)
      {
        if (aGateIsError)
        {
          if (!displayMessage)
          {
            lcd.clear();
            myDisplayData.showAdisconnectedGate(gate_info);
            displayMessage = true;
          }
          if (myTimeCalculation > MAX_DISPLAY_SWITCH_TIME)
          {
            startTimer = currentReceiveMessageTime;
            gate_info.clear();
            aGateIsError = false;
            displayMessage = false;
            currentState = SHOW_OCC;
          }
        }
        else
        {
          currentState = SHOW_OCC;
        }
      }
      else
      {
        if (!displayMessage)
        {
          lcd.clear();
          myDisplayData.showEmergency(emergency_input);
          displayMessage = true;
        }
      }
      break;
    }
  }
}

/**
 * @brief Start Wi-Fi setup.
 *
 */
void MyStartConnection ::connectToMyWiFi()
{
  WiFi.begin(MY_NETWORK_SSID, MY_NETWORK_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    currentTime = millis();
    if (currentTime - startTimer > reconnectDelay)
    {
      lcd.clear();
      lcd.print("Connecting ...");
      startTimer = currentTime;
    }
  }
}

/**
 * @brief MQTT Subscribe setup.
 *
 */
void MyStartConnection ::connectToMyMQTT()
{
  mySubscribeClient.setServer(MY_NETWORK_SITE, MY_NETWORK_PORT);
  mySubscribeClient.setCallback(callback);
}

/**
 * @brief Reconnect MQTT in case disconnection happen.
 *
 * @return true
 * @return false
 */
bool MyStartConnection ::reconnectMyMQTT()
{
  if (mySubscribeClient.connect(MY_COUNTER_TOPIC))
  {
    mySubscribeClient.subscribe(MY_COUNTER_TOPIC);
    mySubscribeClient.subscribe(MY_EMERGENCY_TOPIC);
    mySubscribeClient.subscribe(MY_FASTEST_QUEUE_TOPIC);
    return mySubscribeClient.connected();
  }
  return 0;
}

/**
 * @brief A function to show the occupancy number in the building.
 *
 * @param input data received from the MQTT.
 */
void MyDataDisplay ::showMyOccupancy(String input)
{
  lcd.print("People Inside:");
  lcd.setCursor(0, 1);
  lcd.print(input);

  input.trim();
  if (input.toInt() >= MAX_OCCUPANCY_NUMBER)
  {
    buildingIsFull = true;
  }
  else
  {
    buildingIsFull = false;
  }
}

/**
 * @brief A function to show the less busier Queue of every gates.
 *
 * @param input data received from the MQTT.
 */
void MyDataDisplay ::showMyFastestQueue(String input)
{
  input.replace(':', '\n');
  input.trim();
  lcd.print(input);
  lcd.setCursor(0, 1);
  lcd.print("is less busy!");
}

/**
 * @brief A function to display a disconnected gate
 *
 * @param input data received from the MQTT.
 */
void MyDataDisplay ::showAdisconnectedGate(String input)
{
  lcd.print(input);
}

/**
 * @brief A function to display a notification in case the building
 * is full.
 *
 */
void MyDataDisplay ::showOccNotification()
{
  lcd.print("This Building");
  lcd.setCursor(0, 1);
  lcd.print("is Full!");
}

/**
 * @brief A function to check and display the Emergency alert only
 * if an emergency situation detected.
 *
 * @param input data received from the MQTT.
 */
void MyDataDisplay ::showEmergency(String input)
{
  input.trim();
  if (input == "ON")
  {
    lcd.print("GET OUT!!");
    lcd.setCursor(0, 1);
    lcd.print("IT IS EMERGENCY!!");
  }
  else if (input == "OFF")
  {
    lcd.print("People Inside:");
    lcd.setCursor(0, 1);
    lcd.print("0");
    currentState == SHOW_OCC;
  }
}

/**
 * @brief A function to read and return the payload data from MQTT.
 *
 * @param payload written data received from the MQTT communication.
 * @param length the length of the payload.
 * @return String
 */
String myReadInput(byte *payload, unsigned int length)
{
  String inputMsg;
  if (length > 0)
  {
    inputMsg.clear();
    for (int i = 0; i < length; i++)
    {
      inputMsg += (char)payload[i];
    }
  }
  return inputMsg;
}

/**
 * @brief A function to receive input from MQTT. Only run if the ESP detect a communication
 * via the MQTT network site.
 *
 * @param topic the input topic to determine which data is coming in.
 * @param payload the input data.
 * @param length the length of the input data.
 */
void callback(char *topic, byte *payload, unsigned int length)
{
  if (strcmp(topic, MY_EMERGENCY_TOPIC) == 0)
  {
    emergency_input.clear();
    emergency_input = myReadInput(payload, length);
    emergency_input.trim();
    if (emergency_input == "ON")
    {
      emergency = true;
    }
    else if (emergency_input == "OFF")
    {
      emergency = false;
    }
  }

  if (strcmp(topic, MY_COUNTER_TOPIC) == 0)
  {
    occupancy_input.clear();
    occupancy_input = myReadInput(payload, length);
  }

  if (strcmp(topic, MY_FASTEST_QUEUE_TOPIC) == 0)
  {
    String incomingMessage;
    queue_input.clear();
    incomingMessage = myReadInput(payload, length);

    incomingMessage.trim();
    if ((incomingMessage == GATE_1_DISCONNECTED) || (incomingMessage == GATE_2_DISCONNECTED) || (incomingMessage == GATE_3_DISCONNECTED))
    {
      aGateIsError = true;
      gate_info = incomingMessage;
    }
    else
    {
      queue_input = incomingMessage;
    }
  }
}
