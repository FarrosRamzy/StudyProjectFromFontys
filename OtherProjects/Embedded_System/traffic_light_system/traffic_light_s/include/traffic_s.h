#ifndef TRAFFIC_S_H
#define TRAFFIC_S_H

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
//Listening to the start ping command from the master, then reply it before changing the state.
void trafficListen(trafficStates *);

//Set all traffic to red, then listening to the next command from the master to change the state.
void setTraffic(trafficStates *);

//Set the slave to red, then waiting  until it receives another command from master to change the state.
void trafficStop(trafficStates *);
//Set the slave to green, then waiting  until it receives another command from master to change the state.
void trafficGo(trafficStates *);
//Set the slave to yellow, then waiting  until it receives another command from master to change the state.
void trafficSlow(trafficStates *);
//Set the traffic to blink only if the slave receive NACK from the master or the master is not sending any message any more after some certain seconds in each state, then keep listening for the broadcast message from the master before replying it.
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