#ifndef TIMER_HELPER_H
#define TIMER_HELPER_H

class Timer
{
    private:
        bool isRunning;
        bool autoRestarts;
        unsigned long timeStarted;
        unsigned long duration; //timeToWait

    public:
        Timer(unsigned long timerDuration);
        ~Timer();

        void start();
        void reset();
        bool isActive();
        void setDuration(unsigned long timerDuration);
        bool isElapsed();
        void setAutoRestart(bool value);
};

#endif