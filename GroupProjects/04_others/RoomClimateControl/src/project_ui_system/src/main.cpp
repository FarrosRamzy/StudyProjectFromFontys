#include <Arduino.h>
#include <room_system.h>

float humidity;
float temperature;
float co;
float co2;
float voc;

uint32_t autoFanValue;

int16_t tvocAndCO2DataReceived;
int16_t coDataReceived;

bool autoFan;
bool currentProcessPassed;

uint32_t setTempVal;
uint32_t setFanValue;
uint32_t previousSetFanVal;
uint32_t previousSetTempVal;

String payloadType;
String payloadState;
uint32_t payload;

char gasStatus[MAX_CHAR_ARRAY];

STATE state;

static unsigned long startTime;

void setup()
{
  // put your setup code here, to run once:

  state = IDLE;
  humidity = 0;
  temperature = 0;

  co = 0;
  co2 = 0;
  voc = 0;

  coDataReceived = 0;
  // co2DataReceived = 0;
  tvocAndCO2DataReceived = 0;

  autoFanValue = 0;

  autoFan = true;
  currentProcessPassed = false;

  setTempVal = 0;
  setFanValue = 0;
  previousSetFanVal = 0;

  previousSetTempVal = setTempVal;

  payloadType = HUMIDITY_TYPE;
  payloadState = READ_DATA;
  payload = 0;

  Serial.begin(9600);
  Wire.begin();

  setupEspWifi();
  setupTouchsreen();
  setupHumidTempSensor();
  setupCJMCUMeasure();

  setupFanSystem();

  startTime = millis();
}

void loop()
{
  // put your main code here, to run repeatedly:
  readTouchInput();
  readAutoManualState(&autoFan, &previousSetTempVal, &setTempVal, &setFanValue, payloadType, payloadState, payload);
  switch (state)
  {
  case IDLE:
    if (!currentProcessPassed)
    {
      if (millis() - startTime > MAX_PROCESS_TIMER)
      {
        currentProcessPassed = true;
        startTime = millis();
      }
    }
    else
    {
      state = READ_AIR_Q;
    }
    break;
  case READ_AIR_Q:
    readCarbonMonoxide(&co, &coDataReceived);
    readCJMCUgas(&voc, &co2, &tvocAndCO2DataReceived);

    state = READ_TMP;
    break;
  case READ_TMP:
    readTempAndHumid(&humidity, &temperature);
    // if (readInputMessage(&payloadType, &payloadState, &payload))
    // {
    //   readAutoManualState(&autoFan, &previousSetTempVal, &setTempVal, &setFanValue, payloadType, payloadState, payload);
    // }
    state = PROCESS;
    break;
  case PROCESS:
    processGasSensors(co, co2, voc, tvocAndCO2DataReceived, gasStatus);
    if (!autoFan)
    {
      setManualSpeed(&setFanValue, &previousSetFanVal, gasStatus, &autoFan);
    }
    else
    {
      adjustFanSpeed(setTempVal, &autoFanValue, temperature, humidity, gasStatus);
    }
    state = SEND;
    break;
  case SEND:
    sendTemperatureData(temperature);
    sendHumidityData(humidity);
    sendCOData(co, coDataReceived);
    sendCO2Data(co2, tvocAndCO2DataReceived);
    sendVOCData(voc, tvocAndCO2DataReceived);
    sendGasStatus(gasStatus);

    if (autoFan)
    {
      sendFanSpeedValue(autoFanValue);
    }
    else
    {
      sendFanSpeedValue(setFanValue);
    }
    currentProcessPassed = false;
    state = IDLE;
    break;
  default:
    break;
  }
}