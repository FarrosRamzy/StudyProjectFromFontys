/**
 * @file node_mqtt_manager.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 1.5
 * @date 2026-04-30
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <ArduinoJson.h>
#include "my_node_manager_lib/node_manager.h"

/**
 * @brief
 *
 * @param my_role
 * @return String
 */
String NodeManager::checkRole(String my_role)
{
  String room_name = "";

  Serial.print("[MQTT] Role: ");
  Serial.println(my_role);

  if (my_role == String(MY_ROLE_IS_REGISTRATION))
  {
    room_name = "";
  }
  else if (my_role == String(MY_ROLE_IS_CHECKPOINT))
  {
    room_name = my_node_room;
  }

  return room_name;
}

/**
 * @brief 
 * 
 * @param time_stamp 
 * @param buffer_size 
 * @return true 
 * @return false 
 */
bool NodeManager::prepareMQTTTimestamp(char *time_stamp, size_t buffer_size)
{
  if (!my_node_mqtt.amIConnected())
  {
    return false;
  }

  if (time_stamp == nullptr || buffer_size == 0)
  {
    return false;
  }

  time_stamp[0] = '\0';

  if (!getCurrentTimestampWIB(time_stamp, buffer_size))
  {
    // Do not block MQTT operation while NTP is still syncing.
    // The backend already falls back to its receive time when timestamp is empty.
    Serial.println("[TIME] WIB timestamp unavailable; publishing with backend timestamp fallback.");
    time_stamp[0] = '\0';
  }

  return true;
}
