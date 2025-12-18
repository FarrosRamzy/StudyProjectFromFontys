#include "../include/canCommunication/Headers/canManager.hpp"
#include "../include/servoManager/ServoManager.hpp"

#define servoPin 9

using namespace canCommunication;
using namespace servoControlNameSpace;

class EngineCanManager
{
public:
    void engineCanManagerSetup();
    void handleCanMessage();

private:
    ServoControl myServoControl;
    canManager myCanManager;
};
