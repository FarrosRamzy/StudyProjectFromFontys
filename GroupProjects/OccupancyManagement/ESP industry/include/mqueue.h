#ifndef MQUEUE_H
#define MQUEUE_H

#include <Arduino.h>

#define TIMEOUTFINALPP 5000
#define NUMBOFSENS 4
//////////////////////////////////////////////////////////////////////////////////
///***Configure these parameters below as you would like you system to work!***///
#define DGS 347        // distance from the Gate to the Sensor
#define DFTG 50        // distance form the Gate
#define DBS DGS - DFTG // distance between the Sensors
#define APW 24         // average Person Width
#define SW 30          // sensor Width
#define DBP 75         // distance between People
////***-------------------------------------------------------------------***/////
//////////////////////////////////////////////////////////////////////////////////

class Queue
{
private:
    const int PRESSURE_PLATE_PINS[NUMBOFSENS] = {15, 4, 5, 18}; // If the NUMBOFSENS is chnaged dont forget to add the new sensors PINs here else there will be issues
    bool pPValue[NUMBOFSENS];
    bool values[NUMBOFSENS];
    bool prevPPValue[NUMBOFSENS];
    bool updt[NUMBOFSENS];
    int numbOfSensTrigg = 0;
    int numbOfSensNotTrigg = 0; // number of sensors that are not activated but are considered a tolerance
    int prevNumbOfSensTrigg = 0;
    int difference;
    unsigned long timer;
    unsigned long timerSD[NUMBOFSENS]; // timer for the Spike Detect;
    unsigned long timerExtendedQTime;

public:
    Queue();

    // First read of the Pressure Plates
    void regularPPCheck(); // Check evry button every N-time

    void SpikeDetect(); // in case there is any diffrence int the previous values send top the other Function

    void readPressPlates(int, int); // Read the PINs for new states

    void updateValues(int); // Update the value once the code has verified it

    // Check if this PP is already pressed
    // If only the 3rd PP is pressed then there should be nno queue as it is expected that the person that is at  the end of the queue is just standing there but not waiting on a queue
    // The tolerance that will be implemented later will be maximum of 1 PP that is not triggered betwee two others(e.g. 1-ON 2-ON 3-OFF 4-ON (In that case there are going to be 3PP that will contribute to the waiting time))
    void checkNewPressedPP(); // PP stands for Pressure Plate

    // The purpose of this function is to find out how many people are there infont of the gate to the first sensor
    int PeopleOnTheFirstSensor();

    // This functions purpose is of calculating the avg number between two sensors that are trggred
    int PeopleBetweenSensors(); // fDBS:function Distance Between Sensors//fAPW:function Average People Width//fDBP:function Distance between People

    // This Function is used to get the total amount of people on the queue
    int GetNumberOfPeopleOnTheQueue();

    float WaitingTime(int, int); // Algorithm for the queue time//tPP-time Per Person//tIP-tolerance in Percentage

    // This function is getting involved once there is a change that should be chaecked if it is a spike
    void updateSpikeTimer(int);

    // This function sends out the time for the queue
    float sendQueueLenght();
};

#endif

