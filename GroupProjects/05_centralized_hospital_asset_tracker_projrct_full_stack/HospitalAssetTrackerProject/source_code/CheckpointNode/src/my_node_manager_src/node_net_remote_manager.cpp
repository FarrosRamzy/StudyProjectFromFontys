/**
 * @file node_net_remote_manager.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 2.0
 * @date 2026-04-30
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_manager.h"

/**
 * @brief
 *
 */
void NodeManager::checkRemoteConfigPeriodically()
{
  uint32_t now = my_clock.millisNow();

  if ((uint32_t)(now - my_last_remote_check_ms) < HEARTBEAT_INTERVAL_MS)
  {
    return; // every 30s
  }

  my_last_remote_check_ms = now;

  if (!my_node_wi_fi.amIConnected())
  {
    return;
  }

  if (!my_node_is_provisioned)
  {
    /* code */
    return;
  }

  Serial.println("[REMOTE] Checking config update...");

  // Save current config before fetch
  String old_role = my_node_role;
  String old_hospital = my_node_hospital;
  String old_room = my_node_room;

  if (!fetchRemoteConfig())
  {
    Serial.println("[SYSTEM] remote config not fetched!");
    return;
  }

  const myNodeRemoteConfig &cfg = my_node_net_config.getRemoteConfig();

  String new_room = cfg.room_name;
  String new_role = cfg.role;
  String new_hospital = cfg.hospital_name;

  Serial.print("[SYSTEM] old hospital name: ");
  Serial.println(old_hospital);
  Serial.print("[SYSTEM] new hospital name: ");
  Serial.println(new_hospital);
  Serial.print("[SYSTEM] hospital id: ");
  Serial.println(my_hospital_id);

  if (new_role == MY_ROLE_IS_REGISTRATION)
  {
    /* code */
    new_room = "";
  }

  bool changed = new_role != old_role ||
                 new_hospital != old_hospital ||
                 new_room != old_room;

  if (!changed)
  {
    /* code */
    Serial.println("[REMOTE] Config unchanged.");
    return;
  }

  Serial.println("[REMOTE] Config changed, applying ...");
  applyRemoteConfig();
}