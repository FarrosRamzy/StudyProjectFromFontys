/**
 * @file node_manager_core.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.6
 * @date 2026-04-15
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_manager.h"

/**
 * @brief
 *
 */
NodeManager *NodeManager::active_instance = nullptr;

/**
 * @brief Construct a new Node Manager:: Node Manager object
 *
 */
NodeManager::NodeManager(IMyNodeWiFi &wifi, IMyNodeNetworkConfig &net_cfg, IMyNodeMQTTConnector &mqtt, IMyNodeRFID &rfid,
                         INodeStatusLED &stat_leds, INodeClock &clock, INodeBoardControl &board)
    : my_node_wi_fi(wifi), my_node_mqtt(mqtt), my_node_rfid(rfid), my_node_net_config(net_cfg),
      my_node_status_led(stat_leds), my_clock(clock), my_board(board), my_node_id(""),
      my_node_role(""), my_node_hospital(""), my_hospital_id(""), my_node_room(""),
      my_node_client_id(""), my_node_msg(""), my_node_stat(""), last_heartbeat_time(0),
      my_time_sync_start_ms(0), my_last_time_sync_check_ms(0), my_last_remote_check_ms(0),
      heartbeat_interval(HEARTBEAT_INTERVAL_MS), reset_button_press_start(0),
      reset_button_was_pressed(false), reset_button_triggered(false), last_mqtt_connected(false),
      my_node_is_provisioned(false), my_commands_subscribed(false), my_time_synced(false), last_command_subs_attempt(0),
      my_time_sync_started(false), last_tag_time(0), duplicate_suppress_ms(RFID_DUPLICATE_SUPPRESS_MS)
{
  active_instance = this;
  my_node_mqtt.setMessageCallback(NodeManager::myNodeMQTTCallback);
  last_tag_id[0] = '\0';
}

/**
 * @brief Destroy the Node Manager:: Node Manager object
 *
 */
NodeManager::~NodeManager()
{
}

/**
 * @brief
 *
 */
void NodeManager::beginNodeSystem()
{
  my_node_status_led.beginMyLEDs();
  setupNetConfigResetButton();

  my_node_net_config.beginMyNetConfig();

  if (my_node_net_config.isSetupMode())
  {
    Serial.println("[SYSTEM] Setup mode active.");
    return;
  }
  const myNodeBootstrapConfig &cfg_boot = my_node_net_config.getBootstrapConfig();
  const myNodeRemoteConfig &cfg_remote = my_node_net_config.getRemoteConfig();

  my_node_id = cfg_boot.device_id;
  my_node_is_provisioned = cfg_remote.is_provisioned;

  my_node_client_id = my_node_id;

  my_node_wi_fi.setCredentials(cfg_boot.wifi_ssid.c_str(), cfg_boot.wifi_password.c_str());
  my_node_wi_fi.startWiFi();

  beginTimeSync();

  if (my_node_is_provisioned)
  {
    applyRemoteConfig();

    my_node_rfid.beginMyNodeRFID(RFID_BAUDRATE);
    my_node_rfid.clearBuffer();
    my_node_rfid.configureRFID();
  }
  else
  {
    Serial.println("[SYSTEM] Node is not provisioned yet.");
    return;
  }
}
