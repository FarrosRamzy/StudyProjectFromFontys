#include "mqueue.h"
#include "Arduino.h"

Queue::Queue()
{
  timer = millis();
  for (int i = 0; i < NUMBOFSENS; i++)
  {
    timerSD[i] = millis();
    pinMode(PRESSURE_PLATE_PINS[i], INPUT);
    pPValue[i] = HIGH;
    updt[i] = true;
    prevPPValue[i] = HIGH;
    values[i] = HIGH;
  }
}
// This function is used when the previous recording for that sensor is different that the current one
void Queue::regularPPCheck()
{
  for (int i = 0; i < NUMBOFSENS; i++)
  {
    pPValue[i] = digitalRead(PRESSURE_PLATE_PINS[i]);
  }
  SpikeDetect();
}

void Queue::SpikeDetect()
{ // in case there is any diffrence int the previous values send top the other Function
  for (int i = 0; i < NUMBOFSENS; i++)
  {
    if (updt[i])
    {
      updateSpikeTimer(i);
    }
    if (pPValue[i] != prevPPValue[i])
    {
      updt[i] = false; // this counter is kept for the timing in the spike detection
      readPressPlates(1000, i);
    }
    else
    {
      updt[i] = true; // this counter is kept for the timing in the spike detection
    }
  }
  checkNewPressedPP();
}

void Queue::readPressPlates(int del, int i)
{

  if (millis() - timerSD[i] > del)
  {
    pPValue[i] = digitalRead(PRESSURE_PLATE_PINS[i]);
    prevPPValue[i] = pPValue[i];
    timerSD[i] = millis();
    updt[i] = true;
    updateValues(i);
  }
}

void Queue::checkNewPressedPP()
{ // PP stands for Pressure Plate
  numbOfSensTrigg = 0;
  numbOfSensNotTrigg = 0;
  for (int i = 0; i < NUMBOFSENS; i++)
  {
    if (values[i] == LOW)
    {
      numbOfSensTrigg++;
    }
    else if (i > 0)
    {
      if (values[i] == HIGH)
      {
        if (values[i - 1] == HIGH)
        {
          break;
        }
      }
    }
  }
  if (numbOfSensTrigg != prevNumbOfSensTrigg)
  {
    prevNumbOfSensTrigg = numbOfSensTrigg;
    sendQueueLenght();
  }
}

int Queue::PeopleOnTheFirstSensor()
{
  int pTPD = APW + DBP;                                 // this is the distance that is from front of the person tol the front of the person behind
  int pOFS = (DGS - DFTG) / pTPD;                       // calculate the number of people on the first sensor
  int aL = pOFS * pTPD;                                 // actual Lenght
  if (aL >= DGS - DFTG + APW || aL <= DGS - DFTG - APW) // in that case the second sensor might not get triggered
  {
    int sD = (pOFS + 1) * pTPD + DFTG; // suggested Distance
  }
  return pOFS;
}
float Queue::WaitingTime(int tPP, int tIP)
{ // Algorithm for the queue time //tPP-time Per Person //tIP-tolerance in Percentage
  int tNOP = GetNumberOfPeopleOnTheQueue();
  float waitingTime = 0.0;
  float waitTime = 0.0;
  float deviation;
  float tTPP = tPP; // tempTimePerPerson
  for (int i = tNOP; i >= 1; i--)
  {                                       // Calculate the deviation that may occure basedon a rate given to the function
    float tempVar = (tIP * tTPP) / 100.0; // devide to get the percentage value
    deviation += tempVar;
    tTPP += tempVar;
  }
  waitTime = tPP * tNOP + deviation; // calculate the queue time based on each person that is waiting
  if (waitTime > 59)
  {
    return waitingTime = waitTime / 60.0; // devide the seconds so you can get minutes
  }
  else
  {
    return waitingTime = 0;
  }
}

int Queue::GetNumberOfPeopleOnTheQueue()
{
  int tNOP = 0; // total Number of People
  int pOFS = PeopleOnTheFirstSensor();
  int pBS = PeopleBetweenSensors();

  if (values[0] == 1)
  {
    tNOP = pOFS + ((numbOfSensTrigg - 1) * pBS); // Calculate the total number of people in the queue with the fisrt sensor triggered
  }
  else
  {
    tNOP = pBS * numbOfSensTrigg; // Calculation for the total number of people on the queue if the first sensor is not activated
  }
  return tNOP;
}

void Queue::updateSpikeTimer(int i)
{
  timerSD[i] = millis();
}

float Queue::sendQueueLenght()
{
  float waitingTime = WaitingTime(20, 10);
  return waitingTime;
}

int Queue::PeopleBetweenSensors()  //fDBS:function Distance Between Sensors//fAPW:function Average People Width//fDBP:function Distance between People
{
  int pTPD = APW + DBP;      //from Person to Person Distance
  int pBS = (DBS) / (pTPD);  //variable explanation: people between Sensors
  return pBS;
}

void Queue::updateValues(int i) 
{
  values[i] = pPValue[i];
}
