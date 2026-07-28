/**
 * @file node_manager.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.5
 * @date 2026-04-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <WiFi.h>
#include <stdint.h>
#include <stddef.h>
#include <time.h>

#include "my_node_network_lib/interfaces/i_my_node_wifi.h"
#include "my_node_network_lib/interfaces/i_my_node_network_config.h"
#include "my_node_mqtt_lib/interfaces/i_my_node_mqtt_connector.h"
#include "my_node_rfid_lib/interfaces/i_my_node_rfid.h"
#include "my_node_led_lib/interfaces/i_node_status_led.h"
#include "my_node_manager_lib/interfaces/i_node_clock.h"
#include "my_node_manager_lib/interfaces/i_node_board_control.h"

#include "node_config.h"

class NodeManager
{
private:
    IMyNodeWiFi &my_node_wi_fi;
    IMyNodeNetworkConfig &my_node_net_config;
    IMyNodeMQTTConnector &my_node_mqtt;
    IMyNodeRFID &my_node_rfid;
    INodeStatusLED &my_node_status_led;
    INodeClock &my_clock;
    INodeBoardControl &my_board;

    String my_node_id;
    String my_node_role;
    String my_node_hospital;
    String my_hospital_id;
    String my_node_room;
    String my_node_client_id;
    String my_node_msg;
    String my_node_stat;

    uint32_t last_heartbeat_time;
    uint32_t heartbeat_interval;

    char last_tag_id[RFID_BUFFER_SIZE];
    uint32_t last_tag_time;
    uint32_t duplicate_suppress_ms;

    uint32_t reset_button_press_start;
    bool reset_button_was_pressed;
    bool reset_button_triggered;

    bool last_mqtt_connected;
    bool my_node_is_provisioned;
    bool my_commands_subscribed;
    uint32_t last_command_subs_attempt;

    bool my_time_synced;
    bool my_time_sync_started;
    uint32_t my_time_sync_start_ms;
    uint32_t my_last_time_sync_check_ms;
    uint32_t my_last_remote_check_ms;

    static NodeManager *active_instance;

public:
    NodeManager(IMyNodeWiFi &, IMyNodeNetworkConfig &, IMyNodeMQTTConnector &, IMyNodeRFID &,
                INodeStatusLED &, INodeClock &, INodeBoardControl &);
    ~NodeManager();

    void beginNodeSystem();
    void runNodeSystem();

private:
    static void myNodeMQTTCallback(char *, uint8_t *, unsigned int);
    void handleMqttMessage(char *, uint8_t *, unsigned int);
    void subscribeToCommandTopics();
    void handleBlinkCommand(const char *, const char *, unsigned int);
    void publishCommandAck(const char *, const char *, const char *);

    void handleRFID();

    void publishCheckpoint(const char *);
    void publishRegistration(const char *);
    void handleHeartbeat();
    bool isDuplicateTag(const char *);

    void applyRemoteConfig();
    bool fetchRemoteConfig();

    void beginTimeSync();
    bool getCurrentTimestampWIB(char *, size_t);
    void updateTimeSync();

    void setupNetConfigResetButton();
    void handleConfigResetButton();

    void sayHello();
    void sayGoodbye();
    void handleGreetings(const char *, const char *);

    void checkRemoteConfigPeriodically();

    bool prepareMQTTTimestamp(char *, size_t);
    String checkRole(String);
    String hospitalNameToID(String);
};
