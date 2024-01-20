#include <Arduino.h>
#include <Wire.h>

#define DEVICE_ADDR 0x42

#define THRESHOLD_VALUE 100

//Global variables
uint8_t numberToReturn;

// Function prototypes
void ReceiveEventHandler(int receivedBytes);
void RequestEventHandler();


void setup() 
{
  Serial.begin(9600);           // start serial for output
  Wire.begin(DEVICE_ADDR);      // join I2C bus with address #8
  
  Wire.onReceive(ReceiveEventHandler); // register event
  Wire.onRequest(RequestEventHandler); // register event

  numberToReturn = 0;
}

void loop() 
{
  //do nothing
}

/**
 * Executes whenever data is received from master.
 * @param receivedBytes The number of bytes received by the master
*/
void ReceiveEventHandler(int receivedBytes) 
{
  if (Wire.available())
  {
    // Read only 1 byte, as per assignment requirements
    uint8_t receivedByte = Wire.read();
    numberToReturn = receivedByte > THRESHOLD_VALUE ? 2 : 4;
  } 
}

/**
 * Executes whenever data is requested by master
*/
void RequestEventHandler() 
{
  Wire.write(numberToReturn);
}
