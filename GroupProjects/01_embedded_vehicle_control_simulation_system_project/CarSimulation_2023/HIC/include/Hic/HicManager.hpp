#pragma once
#include "main.hpp"
#include "../include/Hic/LightSystem.hpp"
#include "../include/canCommunication/Enums/MessageId.hpp"
#include "../include/canCommunication/Enums/MessageValue.hpp"
#include "../include/canCommunication/Headers/canManager.hpp"
#include "../include/Hic/LightSystem.hpp"

using namespace canCommunication;

class HicManager
{
private:
    LightSystem lightSystem;
    canCommunication::canManager can_manager;
    void controlHeadlights();
    void controlIndicators();
    MessageValue indicatorsState;

public:
    HicManager(uint8_t leftPin, uint8_t rightPin, uint8_t lightAPin, uint8_t lightBPin);
    void managerConfig();
    void handleCanMessage();
    void processIndicators();
};