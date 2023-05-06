////////////////////////////////////////////////////
// This is the code for gate 2 and its connections//
// Functionalities made by Kuba, Marco            //
// Connection part made by Dorin                  //
////////////////////////////////////////////////////

#include <helper.h>
#include "button.h"
#include "mqueue.h"

#define OPENGATE 1000
#define STOPGATE 2000
#define CLOSEGATE 3000
#define MINUTE 60000

#define OPENGATECLOCKWISE 180
#define STOPGATESPIN 90
#define CLOSEGATECOUNTERCLOCKWISE 0

#define DELAYTIMECONNECTION 5000

// variable init
int counter;
int maxAmountOfPeople = 10;

float gate1QueueLength = 0;
float gate2QueueLength = 0;
float gate3QueueLength = 0;

int fastestQueue = 0;
int numberOfgates = 3;

//////////////////////////////////////Change based on which gate you are using
int currentGate;
int otherGate1;
int otherGate2;

String currentGateName = "gate1:";
String other1GateName = "gate2:";
String other2GateName = "gate3:";
//////////////////////////////////////

bool OpenTheGate = false;
bool Open_Close_Gate = false;
bool SendCounterPlus = false;
bool SendCounterMinus = false;
bool buttonPressed = false;
bool HandleDoors = false;
bool doorOpening = false;
bool priority = false;

long int timeCount = 0;
long int lastTime = 0;
long int ledTime = 0;
long int currentTime = 0;
long int timeElapsed = 0;
long int GateWorkingTime = 0;

unsigned long Gate1WorkingTime = 0;
unsigned long Gate2WorkingTime = 0;
unsigned long Gate3WorkingTime = 0;
unsigned long previousTimeGate = 0;
unsigned long previousTimeEmergency = 0;
unsigned long previousQueueSend = 0;

bool checker = false;


button enterButton = button(ENTERBUTTON, buttonDebounceDelay);
button emergencyButton = button(EMERGENCYBUTTON, buttonDebounceDelay);
button exitButton = button(EXITBUTTON, buttonDebounceDelay);

Queue queue;

void setup()
{
  Serial.begin(115200);
  setupGate();
  setupConnection();
  // SIOUX: I like the use of these helper functions, they make it readable and emphasize the division of work
}

void loop()
{
  HandleButtons();
  HandleGate();
  HandleConnection();
  queue.regularPPCheck();
  currentGate = queue.sendQueueLenght(); //to be changed when using different gate
  HandleQueueManagment();
  HandleWorkingGates();
}
void HandleWorkingGates()
{
  GateWorkingTime = millis();

  if (GateWorkingTime - Gate1WorkingTime >= MINUTE)
  {
    client.publish("group4Industry/fastestQueue", "Gate 1 broken", 0);
    Gate1WorkingTime = GateWorkingTime;
  }
  else if (GateWorkingTime - Gate2WorkingTime >= MINUTE)
  {
    client.publish("group4Industry/fastestQueue", "Gate 2 broken", 0);
    Gate2WorkingTime = GateWorkingTime;
  }
  else if (GateWorkingTime - Gate3WorkingTime >= MINUTE)
  {
    client.publish("group4Industry/fastestQueue", "Gate 3 broken", 0);
    Gate3WorkingTime = GateWorkingTime;
  }
}

void HandleQueueManagment()
{ 
  //config for gate 2
  otherGate1 = gate2QueueLength;
  otherGate2 = gate3QueueLength;

  if ((currentGate > otherGate1) && (currentGate > otherGate2))
  {
    priority = true;
  }
  else if ((currentGate == otherGate1) && (currentGate == otherGate2) && (currentGateName == "gate1:"))
  {
    priority = true;
  }
  else
  {
    priority = false;
  }

  if (millis() - previousQueueSend >= 5000)
  {
    sendQueueLenght();
    sendFastestQueue();
    previousQueueSend = millis();
  }
}
// when the connection starts, subscribe to topics needed. for the "ack" message it sends "ack back" and for the counter topic update it when the counter updates
void onConnectionEstablished()
{
  client.subscribe("group4Industry/counter", [](const String &topic, const String &payload)
  { 
    counter = payload.toInt(); 
  });


  client.subscribe("group4Industry/emergency", [](const String &topic, const String &payload)
  {    
    if(payload == "ON")
    {
      emergency = LOW;
      digitalWrite(LED_RED_PIN, HIGH);
      OpenTheGate = true;
    }
    else if(payload == "OFF")
    {
      emergency = HIGH;
      digitalWrite(LED_RED_PIN, LOW);
      OpenTheGate = false;
    }
    previousTimeEmergency = millis();
  });

  client.subscribe("group4Industry/queues", [](const String &topic, const String &payload)
  { 
    String message = payload;
    // Split the message into gate name and queue length
    int splitIndex = message.indexOf(":");
    String gateName = message.substring(0, splitIndex);
    String queueLength = message.substring(splitIndex + 1);
    // Filter the message based on gate name
    if (gateName == "gate1") 
    {
      gate1QueueLength = queueLength.toInt();
      Gate1WorkingTime = GateWorkingTime;
      Serial.println(gate1QueueLength);
    } 
    else if (gateName == "gate2") 
    {
      gate2QueueLength = queueLength.toInt();
      Gate2WorkingTime = GateWorkingTime;
      Serial.println(gate2QueueLength);
    }
    else if (gateName == "gate3") 
    {
      gate3QueueLength = queueLength.toInt();
      Gate3WorkingTime = GateWorkingTime;
      Serial.println(gate3QueueLength);
    }
  });
}

void sendQueueLenght() 
{
  String data = currentGateName + String(currentGate);
  client.publish("group4Industry/queues", data.c_str(), 0);
}
void sendFastestQueue()
{
  if ((currentGate < otherGate2) && (currentGate < otherGate1))
    {
      client.publish("group4Industry/fastestQueue", currentGateName, 0);
    }
}

// Handles the gate servo and openin/closing
// Sioux: Lots of magic numbers. Use defines for these
// In addition, you can simplify the statement by checking for "(millis() - previousTimeEmergency) <= 500" in the outer if statement.
void HandleGate()
{
  currentTime = millis();
  //timeElapsed = (currentTime - previousTimeEmergency);
  if (OpenTheGate == true)
  {
    if ((currentTime - previousTimeEmergency) <= OPENGATE)
    {
      servo.write(OPENGATECLOCKWISE);
    }
    else
    {
      servo.write(STOPGATESPIN);
      HandleDoors = false;
    }
  }
  else if (OpenTheGate == false) // Sioux: this if is not neaded
  {
    if ((currentTime - previousTimeEmergency) <= OPENGATE)
    {
      servo.write(CLOSEGATECOUNTERCLOCKWISE);
    }
    else
    {
      servo.write(STOPGATESPIN);
      HandleDoors = false;
    }
  }

  if (Open_Close_Gate == true)
  {
    if ((currentTime - previousTimeGate) <= OPENGATE)
    {
      servo.write(OPENGATECLOCKWISE);
      digitalWrite(LED_WHITE_PIN, HIGH);
    }
    else if (((currentTime - previousTimeGate) >= OPENGATE) && ((currentTime - previousTimeGate) < STOPGATE))
    {
      servo.write(STOPGATESPIN);
    }
    else if (((currentTime - previousTimeGate) >= STOPGATE) && ((currentTime - previousTimeGate) <= CLOSEGATE))
    {
      servo.write(CLOSEGATECOUNTERCLOCKWISE);
    }
    else
    {
      servo.write(STOPGATESPIN);
      digitalWrite(LED_WHITE_PIN, LOW);
      HandleResetGate();
    }
  }
}

// Handles buttons and debounces them
void HandleButtons()
{
  if (emergency == HIGH && !enterButton.pressed())
  {
    EntranceButton();
  }

  if (!emergencyButton.pressed())
  {
    EmergencyButton();
  }

  if (emergency == HIGH && !exitButton.pressed())
  {
    ExitButton();
  }
}

// gate setup
void setupGate()
{
  servo.attach(SERVOPIN); // attaches the servo on pin 9 to the servo object
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_WHITE_PIN, OUTPUT);
  pinMode(CONNECTION_LED, OUTPUT);
}

// connection setup extra properties
void setupConnection()
{
  client.enableDebuggingMessages();
  client.enableHTTPWebUpdater();
}

// add 1 to counter and open the in gate

void EntranceButton()
{
  if (SendCounterPlus == false)
  {
    if ((counter < (maxAmountOfPeople - numberOfgates)) || (priority && counter < maxAmountOfPeople))
    {
      if(doorOpening == false)
      {
        doorOpening = true;
        Open_Close_Gate = true;
        String message = "add";
        client.publish(mqtt_topic_counter, message, 1);
        SendCounterPlus = true;
        previousTimeGate = millis();
      }
    }
  }
}

// remove 1 from counter and open the out gate
void ExitButton()
{
  if (SendCounterMinus == false)
  {
    if (counter >= 1)
    {
      if(doorOpening == false)
      {
        Open_Close_Gate = true;
        doorOpening == true;
        String message = "substract";
        client.publish(mqtt_topic_counter, message, 1);
        previousTimeGate = millis();
        SendCounterMinus = true;
      }
    }
  }
}

// Emergency and reset button
void EmergencyButton()
{
  String messageEmerg = "";

  if(millis() - previousTimeEmergency >= 500)
  {
    if (emergency == HIGH)
    {
      messageEmerg = "ON";
      emergency = LOW;
      digitalWrite(LED_RED_PIN, HIGH);
      OpenTheGate = true;
    }
    else if (emergency == LOW)
    {
      messageEmerg = "OFF";
      emergency = HIGH;
      digitalWrite(LED_RED_PIN, LOW);
      OpenTheGate = false;
    }
    if (HandleDoors == false)
    {
      String message = String(0);
      client.publish(mqtt_topic_global_counter, message, 1);
      client.publish(mqtt_topic_emergency, messageEmerg, 0);
      HandleDoors = true;
    }
    previousTimeEmergency = millis();
  }
}

// handles the connection and sends ack message each 5 seconds
void HandleConnection()
{
  client.loop();
  timeCount = millis();
  if (timeCount - lastTime >= DELAYTIMECONNECTION)
  {
    client.publish(mqtt_topic, "ack", 0);
    lastTime = timeCount;
  }
  if ((checker == true) && (timeCount - ledTime >= 1000))
  {
    digitalWrite(CONNECTION_LED, LOW);
    checker = false;
  }
}

void HandleResetGate()
{
  Open_Close_Gate = false;
  SendCounterPlus = false;
  SendCounterMinus = false;
  doorOpening = false;
}