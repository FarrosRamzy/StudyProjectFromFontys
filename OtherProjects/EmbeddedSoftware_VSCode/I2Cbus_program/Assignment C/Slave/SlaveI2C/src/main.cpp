#include <Arduino.h>
#include <Wire.h>

#define MAX_BUFFER_SIZE 32
#define DEVICE_ADDR 0x50

#define FIRST_NUMBER_ADDR 21
#define SECOND_NUMBER_ADDR 22
#define MIN_NUMBER_ADDR 23
#define MAX_NUMBER_ADDR 24

//Registry as an array (allows for burst reading)
#define REGISTRY_SIZE 30
//Note: currently all registers are unsigned
uint8_t registry[REGISTRY_SIZE] = { 0 };
// Truth table for writability to the registers
bool registryWritePermissions[REGISTRY_SIZE] = { 0 };

int8_t currentRegsitryIndex;

//Function prototypes
void SetUpRegistryReadWritePermissions();
void ClearWireBuffer();
void ReceivedEventHandler(int bytesReceived);
void RequestedEventHandler();
void UpdateMinAndMaxValues();


void setup() 
{
  Serial.begin(9600);
  Wire.begin(DEVICE_ADDR);

  Wire.onReceive(ReceivedEventHandler);
  Wire.onRequest(RequestedEventHandler);

  currentRegsitryIndex = -1;

  SetUpRegistryReadWritePermissions();
}

void loop() 
{
  //Do nothing
}

/**
 * Sets up the registry read-write permissions
*/
void SetUpRegistryReadWritePermissions()
{
  //Everything starts as Read-Only by default
  // Set the registers to be writable here
  registryWritePermissions[21] = true;
  registryWritePermissions[22] = true;
}

/**
 * Clears the wire buffer
*/
void ClearWireBuffer()
{
  while (Wire.available())
  {
    Wire.read();
  }
}

/**
 * Executes when data from the master is received
 * @param bybtesReceived The number of bytes received by the master
*/
void ReceivedEventHandler(int bytesReceived)
{
  //Get address of the desired register
  if (Wire.available())
  {
    int8_t requestedRegistryAddress = Wire.read();

    currentRegsitryIndex = requestedRegistryAddress > REGISTRY_SIZE ? -1 : requestedRegistryAddress;

    if (requestedRegistryAddress > REGISTRY_SIZE)
    {
      currentRegsitryIndex = -1;
      return;
    }

    if (bytesReceived == 1)
    {
      return;
    }
  }

  //Burst-write to registers if more than 1 byte is received
  while (Wire.available() && currentRegsitryIndex < REGISTRY_SIZE)
  {
    uint8_t valueToWrite = Wire.read();

    //Read/Write permission check
    if (registryWritePermissions[currentRegsitryIndex])
    {
      registry[currentRegsitryIndex] = valueToWrite;
    }

    if (currentRegsitryIndex == FIRST_NUMBER_ADDR || currentRegsitryIndex == SECOND_NUMBER_ADDR)
    {
      UpdateMinAndMaxValues();
    }
    
    // Go to the next register
    currentRegsitryIndex++;
  }
  
  ClearWireBuffer();
}

/**
 * Executes when the master requests data.
*/
void RequestedEventHandler()
{
  /*
  Burst read support:
  The buffer size for Arduino AVR boards is 32 bytes. To allow for burst reading, the slave always sends the maximum amount of bytes it can fit inside the buffer.
  */

  // Invalid register address guard
  if (currentRegsitryIndex == -1)
  {
    // Do not send anything
    return;
  }

  // Calculate the maximum possible amount of bytes to send to the master
  uint8_t bytesToSend = REGISTRY_SIZE - currentRegsitryIndex;
  if (bytesToSend > MAX_BUFFER_SIZE)
  {
    bytesToSend = MAX_BUFFER_SIZE;
  }

  uint8_t startRegistryIndex = currentRegsitryIndex;
  uint8_t lastRegistryIndex = currentRegsitryIndex + bytesToSend - 1;
  
  //Fill the buffer (32 bytes) to allow for burst reading
  uint8_t *bufferToSend = (uint8_t*)malloc(bytesToSend * sizeof(*bufferToSend));

  // Fill the buffer
  for (uint8_t i = startRegistryIndex, j = 0; i <= lastRegistryIndex; i++, j++)
  {
    bufferToSend[j] = registry[i];
  }

  Wire.write(bufferToSend, bytesToSend);

  free(bufferToSend);
  // Reset currentRegistryIndex?
  currentRegsitryIndex = -1;
}

/**
 * Updates the minimum and maximum values according to the numbers in FIRST_NUMBER_ADDR and SECOND_NUMBER_ADDR
*/
void UpdateMinAndMaxValues()
{
  if (registry[FIRST_NUMBER_ADDR] > registry[SECOND_NUMBER_ADDR])
  {
    registry[MIN_NUMBER_ADDR] = registry[SECOND_NUMBER_ADDR];
    registry[MAX_NUMBER_ADDR] = registry[FIRST_NUMBER_ADDR];
  }
  else
  {
    registry[MIN_NUMBER_ADDR] = registry[FIRST_NUMBER_ADDR];
    registry[MAX_NUMBER_ADDR] = registry[SECOND_NUMBER_ADDR];
  }
}