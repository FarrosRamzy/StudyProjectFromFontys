#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H

class systemTimer
{
private:
    bool isRunning;
    bool autoRestarts;
    unsigned long startTime;
    unsigned long duration;
public:
    systemTimer(unsigned long);
    ~systemTimer();

    void startSystem();
    void resetSystem();
    void setDuration(unsigned long);
    void setAutoRestart(bool);
    bool isPassed();
    bool isActive();
};


#endif