#include "../include/canCommunication/Headers/canManager.hpp"
#include "../include/Hic/HicManager.hpp"

HicManager manager(LEFT_INDICATOR_PIN, RIGHT_INDICATOR_PIN, HEADLIGHT_A_PIN, HEADLIGHT_B_PIN);

void setup() {
    Serial.begin(9600);
    manager.managerConfig();
}

void loop() {
    manager.handleCanMessage();
    manager.processIndicators();
    
}