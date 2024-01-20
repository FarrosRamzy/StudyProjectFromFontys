#pragma once
#include "main.hpp"
#include "../include/Hic/IHeadLights.hpp"
#include "../include/Hic/IIndicator.hpp"

class LightSystem : public IIndicator, public IHeadLights {
private:
    uint8_t leftIndicatorPin;
    uint8_t rightIndicatorPin;
    uint8_t headlightLeftPin;
    uint8_t headlightRightPin;
    bool isHeadlightsOn;
    void blink(uint8_t pin_nr, uint32_t delay);

public:
    LightSystem(uint8_t leftPin, uint8_t rightPin, uint8_t lightAPin, uint8_t lightBPin);
    void blinkIndicator(uint8_t pin_nr, uint32_t delay) override;
    void turnOffIndicators() override;
    void turnOnHeadlights() override;
    void turnOffHeadlights() override;
};