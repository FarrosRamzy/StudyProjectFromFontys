#ifndef TRAFFIC_M_H
#define TRAFFIC_M_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define START_PING "master_present"
#define REPLY_PING "slave_present"
#define SET_TRAFFIC "start_red"
#define STOP "now_red"
#define SLOW_DOWN "now_yellow"
#define GO "now_green"
#define ACK "ACK"
#define CHECK "CHECK"
#define NACK "NACK"

enum trafficStates
{
    START,
    IDLE,
    LISTEN,
    SET_RED,
    RED,
    GREEN,
    YELLOW,
    BLINK_ON,
    BLINK_OFF
};

const int RLED = 2;
const int YLED = 3;
const int GLED = 4;

const unsigned long WAIT_SET_TRAFFIC = 2000;
const unsigned long WAIT_IN_RED = 2000;
const unsigned long WAIT_IN_GREEN = 6000;
const unsigned long WAIT_IN_YELLOW = 2000;

const unsigned long BLINK_DELAY = 500;
const unsigned long MSG_DEBOUNCE_DELAY = 1000;

//Setting-up the SoftwareSerial pin library.
void setupTraffic();
//Start the traffic by set all LEDs to off.
void trafficStart(trafficStates *);
//Broadcasting the start ping message to the slave.
void trafficIdle(trafficStates *);
//Listening to the start ping reply from the slave.
void trafficListen(trafficStates *);

//Set all traffic to red.
void setTraffic(trafficStates *);

//Set the master to stay in red, then ask the slave to green, then yellow by sequence while also checking if the slave still available or not.
void trafficStop(trafficStates *);
//Set the master to green, then check if the slave is still available or not.
void trafficGo(trafficStates *);
//Set the master to yellow, then check if the slave is still available or not.
void trafficSlow(trafficStates *);
//Set the traffic to blink only if the slave says NACK or not available, then keep pinging the broadcast message and checks it's reply.
void trafficError(trafficStates *);

//Set all LEDs to LOW.
void allLEDOff();

//Set red LED to LOW.
void redLEDOff();
//Set yellow LED to LOW.
void yellowLEDOff();
//Set green LED to LOW.
void greenLEDOff();

//Set red LED to HIGH.
void redLEDOn();
//Set yellow LED to HIGH.
void yellowLEDOn();
//Set green LED to HIGH.
void greenLEDOn();

#endif