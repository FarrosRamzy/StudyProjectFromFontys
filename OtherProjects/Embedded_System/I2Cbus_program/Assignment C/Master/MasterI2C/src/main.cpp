#include <Arduino.h>
#include <Wire.h>
#include <systemTimer.h>

#define SLAVE_ADDR 0x50

#define INA_ADDR 21
#define INB_ADDR 22

#define MIN_ADDR 23
#define MAX_ADDR 24

#define SECONDS *1000

int inputA;
int inputB;

int maxVal;
int minVal;

void changeStates();
void handleStates();
void setValue(int *, int *);
int getOutputMin();
int getOutputMax();

// State machine states
typedef enum
{
  IDLE,
  SET_VALUE,
  FIND_MIN,
  FIND_MAX,
} PARALLEL_STATE;

PARALLEL_STATE previousState;
PARALLEL_STATE currentState;

systemTimer stateChangeTimer(0.5 SECONDS);

void setup()
{
  inputA = 0;
  inputB = 0;

  previousState = IDLE;
  currentState = IDLE;

  Serial.begin(9600);
  Wire.begin();

  stateChangeTimer.startSystem();
}

void loop()
{
  if (stateChangeTimer.isPassed())
  {
    changeStates();
    handleStates();
  }
}

/**
 * Sets the values for inputA and inputB in the slave's registers
 * @param inputA The value which to write to the second number's register of the slave
 * @param inputB The value which to write to the second number's register of the slave
 */
void setValue(int *inputA, int *inputB)
{
  *inputA = 8;
  *inputB = 9;

  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(INA_ADDR);
  Wire.write(*inputA);
  Wire.write(*inputB);
  Wire.endTransmission();
}

/**
 * Gets the max number from the slave
 * @returns The max number from the slave
 */
int getOutputMax()
{
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(MAX_ADDR);
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_ADDR, 1);
  uint8_t receivedByte = Wire.read();
  int maxValReceived = receivedByte;
  return maxValReceived;
}

/**
 * Gets the min number from the slave
 * @returns The min number from the slave
 */
int getOutputMin()
{
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(MIN_ADDR);
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_ADDR, 1);
  uint8_t receiveByte = Wire.read();
  int minValReceived = receiveByte;
  return minValReceived;
}

/**
 * Handles the states of the master
 */
void handleStates()
{
  switch (currentState)
  {
    case IDLE:
    {
      break;
    }
    case SET_VALUE:
    {
      if (previousState != currentState)
      {
        setValue(&inputA, &inputB);
        previousState = currentState;
      }
      break;
    }

    case FIND_MIN:
    {
      if (previousState != currentState)
      {
        minVal = getOutputMin();
        Serial.print("Min:\t");
        Serial.println(minVal);
        previousState = currentState;
      }
      break;
    }
    case FIND_MAX:
    {
      if (previousState != currentState)
      {
        maxVal = getOutputMax();
        Serial.print("Max:\t");
        Serial.println(maxVal);
        previousState = currentState;
      }
      break;
    }

    default:
    {
      break;
    }
  }
}

/**
 * Changes the state of the master
*/
void changeStates()
{
  switch (currentState)
  {
    case IDLE:
    {
      currentState = SET_VALUE;
      break;
    }
    case SET_VALUE:
    {
      currentState = FIND_MIN;
      break;
    }
    case FIND_MIN:
    {
      currentState = FIND_MAX;
      break;
    }
    case FIND_MAX:
    {
      currentState = IDLE;
      break;
    }
    default:
    {
      break;
    }
  }
}