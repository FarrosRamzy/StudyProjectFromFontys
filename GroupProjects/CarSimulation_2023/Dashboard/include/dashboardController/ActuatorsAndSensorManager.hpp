// ActuatorsAndSensorManager.hpp

#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>

#include "IBrakePedal.hpp"
#include "IDisplay.hpp"
#include "IGasPedal.hpp"
#include "IHeadLightsController.hpp"
#include "ITurnIndicator.hpp"
#include "IHandBreak.hpp"
#include "../canCommunication/Headers/canManager.hpp"

using namespace canCommunication;

namespace ActuatorsAndSensor
{
    class Manager
    {
    private:
        IBrakePedal breakPedal;
        IDisplay Display;
        IGasPedal gasPedal;
        IHeadLightsController headlightsController;
        ITurnIndicator TurnIndicator;
        IHandBreak HandBreak;

        canManager canmanager;

        // Constents
        const int headlightsPIN = 9;
        const int breakPIN = 4;
        const int gaspeddalPIN = 7;
        const int breakPedalPin = 8;
        const int potentiometerPIN = A3;

        bool headlightsAreOn = false;

    public:
        // combined methods
        void ActuatorsAndSensorSetup();
        void updateSpeed();
        void updateHeadlights();
        void updateIndiactor();
        void handleReceivedMessage();
        void loopManager();
    };
}