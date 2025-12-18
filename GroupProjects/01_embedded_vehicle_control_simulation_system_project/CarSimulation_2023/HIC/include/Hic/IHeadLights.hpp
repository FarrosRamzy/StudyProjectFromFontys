#pragma once
#include "main.hpp"

class IHeadLights {
public:
    virtual void turnOnHeadlights() = 0;
    virtual void turnOffHeadlights() = 0;
};