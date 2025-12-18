#include <trial_system.h>

float humidity;
float temperature;

int fanSpeed;

bool autoFanSpeed;
bool readTemperature;
bool currentProcessPassed;

uint32_t setTemperatureValue;
uint32_t setFanValue;

static unsigned long startTimer;

STATE state;

void setup()
{
  // put your setup code here, to run once:
  state = IDLE;
  humidity = 0;
  temperature = 0;
  fanSpeed = 0;
  setTemperatureValue = 0;
  setFanValue = 0;

  autoFanSpeed = true;
  readTemperature = true;
  currentProcessPassed = false;

  Serial.begin(9600);
  setupDHTSensor();
  setupFanSystem();
  setupTouchScreen();
  Serial.println("SETUP_DONE");
  startTimer = millis();
}

void loop()
{
  // put your main code here, to run repeatedly:
  readTouchInput();
  readAutoManualState(&autoFanSpeed, &readTemperature, &setFanValue, &setTemperatureValue);
  // Serial.println("LOOP_START");
  switch (state)
  {
  case IDLE:
    if (!currentProcessPassed)
    {
      if (millis() - startTimer > MAX_PROCESS_TIMER)
      {
        currentProcessPassed = true;
        startTimer = millis();
      }
    }
    else
    {
      state = READ;
    }
    break;
  case READ:
  {
    readTemperatureAndHumidity(&humidity, &temperature);
    state = PROCESS;
    break;
  }
  case PROCESS:
  {
    if (autoFanSpeed)
    {
      processFanSpeed(temperature, humidity);
    }
    else //if (!autoFanSpeed)
    {
      setFanSpeedManually(setFanValue);
    }
    state = SEND;
    break;
  }
  case SEND:
    sendTemperatureAndHumidityData(humidity, temperature);
    // Serial.print("Humidity:\t");
    // Serial.println(humidity);
    // Serial.print("Temperature:\t");
    // Serial.println(temperature);

    currentProcessPassed = false;
    state = IDLE;
    break;
  default:
    break;
  }
}