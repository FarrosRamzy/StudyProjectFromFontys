#ifndef BUTTON_H
#define BUTTON_H

class button
{
private:
    int m_pinNumber;
    int m_state;
    int m_debounceDelay;
    int m_lastDebounceTime;

public:
    button(int pinNumber, int debounceDelay);

    ~button() = default;

    bool pressed();
    bool risingEdge();
};

#endif