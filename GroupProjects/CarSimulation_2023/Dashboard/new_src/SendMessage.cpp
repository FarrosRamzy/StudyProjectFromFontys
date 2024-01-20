#ifndef SEND_MESSAGE_HPP
#define SEND_MESSAGE_HPP

#include "ISendCANMessage.hpp"
#include <Arduino.h>
#include <mcp2515_can.h>

// Assuming CAN is initialized elsewhere
extern mcp2515_can CAN;

class SendMessage : public ISendCANMessage {
public:
    SendMessage() {
        // Constructor can be used for initialization if needed
    }

    void sendHeartbeatPing() override {
        // Implement the logic to send a heartbeat ping
        // For example, sending a specific CAN message
        unsigned long heartbeatID = 0x100; // Example ID for heartbeat
        unsigned char heartbeatValue = 0; // Example value for heartbeat
        sendCANMessage(heartbeatID, heartbeatValue);
    }

    void sendError(const std::string& error_message) override {
        // Implement the logic to send an error message
        // This could be sending a CAN message or simply logging the error
        Serial.println("Error: %d", error_message);
        // Optionally, send a CAN message for the error
    }

    void sendCommand(const std::string& command_message) override {
        // Implement the logic to send a command
        // This will depend on how your commands are structured
        // For demonstration, let's assume command_message is "BRAKE"
        if (command_message == "BRAKE") {
            sendCANMessage(0x001, 1); // Example: Sending BRAKE command
        }
        // Add more commands as needed
    }

private:
    void sendCANMessage(unsigned long id, unsigned char value) {
        unsigned char stmp[1] = {value};
        CAN.sendMsgBuf(id, 0, 1, stmp);
    }
};

#endif // SEND_MESSAGE_HPP