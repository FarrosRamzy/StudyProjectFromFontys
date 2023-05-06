#include <traffic_m.h>

//////////////////////////////////////////////////////////////////////
//<assignment 2 traffic_system>
//
//Course	    : Embedded System (ES2)
//Assignment	: Serial Communication Protocol
//Date		    : 01-04-2022
//Student		  : - Farros Ramzy
//              - Luka Brandsema
//
//////////////////////////////////////////////////////////////////////
// file       : Traffic Master
//////////////////////////////////////////////////////////////////////

trafficStates state;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupTraffic();
  state = START;
  pinMode(RLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  pinMode(GLED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  switch (state)
  {
  case START:
    trafficStart(&state);
    break;
  case IDLE:
    trafficIdle(&state);
    break;
  case LISTEN:
    trafficListen(&state);
    break;
  case SET_RED:
    setTraffic(&state);
    break;
  case RED:
    trafficStop(&state);
    break;
  case GREEN:
    trafficGo(&state);
    break;
  case YELLOW:
    trafficSlow(&state);
    break;
  case BLINK_ON:
    trafficError(&state);
    break;
  case BLINK_OFF:
    trafficError(&state);
    break;
  default:
    break;
  }
}