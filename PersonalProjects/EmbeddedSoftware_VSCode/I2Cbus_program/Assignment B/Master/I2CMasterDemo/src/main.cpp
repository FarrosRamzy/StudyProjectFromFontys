// Wire Master Writer and Reader
#include <Arduino.h>
#include <timerHelper.h>
#include <Wire.h>

#define SECONDS *1000

#define SLAVE_ADDR 0x42

// Function prototypes
void HandleWriting();
void HandleReading();
void HandleReadWrite();
void GoToNextState();

// Timers
Timer modeChangeTimer(0.25 SECONDS);

void setup()
{
  Wire.begin();       // join I2C bus (address optional for master)
  Serial.begin(9600); // start serial for output

  // Start timers
  modeChangeTimer.start();
}

// State machine states
typedef enum
{
  IDLE,
  WRITING,
  READING
} RW_STATE;

RW_STATE prevState = IDLE;
RW_STATE currentState = IDLE;

void loop()
{
  if (modeChangeTimer.isElapsed())
  {
    GoToNextState();
    HandleReadWrite();
  }
}

/**
 * Handles the I2C writing logic
 */
void HandleWriting()
{
  static uint8_t byteToSend = 90;

  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(byteToSend);
  Wire.endTransmission();

  byteToSend++;
}

/**
 * Handles the I2C reading logic
 */
void HandleReading()
{
  Wire.requestFrom(SLAVE_ADDR, 1); // request 6 bytes from slave device #8

  if (Wire.available())
  {
    uint8_t receivedByte = Wire.read();
    Serial.println(receivedByte);
  }
}

/**
 * State machine for the I2C reading and writing
 */
void HandleReadWrite()
{
  switch (currentState)
  {
  case IDLE:
    break;

  case WRITING:
    if (prevState != currentState)
    {
      HandleWriting();
      prevState = currentState;
    }
    break;

  case READING:
    if (prevState != currentState)
    {
      HandleReading();
      prevState = currentState;
    }
    break;

  default:
    break;
  }
}

/**
 * Goes to the next state of the reading/writing, changing the value of currentState
 */
void GoToNextState()
{
  switch (currentState)
  {
  case IDLE:
    currentState = WRITING;
    break;

  case WRITING:
    currentState = READING;
    break;

  case READING:
    currentState = WRITING;
    break;

  default:
    break;
  }
}