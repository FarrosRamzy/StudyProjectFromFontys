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
    /* code */
    room_name = my_node_room;
  }

  return room_name;
}

/**
 * @brief
 *
 * @param topic
 * @param payload
 * @param length
 */
void NodeManager::myNodeMQTTCallback(char *topic, uint8_t *payload, unsigned int length)
{
  (void)topic;
  (void)payload;
  (void)length;
}

template <typename PublishMQTTmsg>
bool NodeManager::publishWithTimestamp(PublishMQTTmsg publish_mqtt)
{
  if (!my_node_mqtt.amIConnected())
  {
    return false;
  }

  char time_stamp[32] = {0};

  if (!getCurrentTimestampWIB(time_stamp, sizeof(time_stamp)))
  {
    /* code */
    Serial.println("[TIME] Failed to get WIB timestamp.");
    return false;
  }
  // publish_mqtt(time_stamp);
  return publish_mqtt(time_stamp);
}

/**
 * @brief
 *
 * @param tag_id
 */
void NodeManager::publishCheckpoint(const char *tag_id)
{

  String room_name = checkRole(my_node_role);

  bool ok = publishWithTimestamp([&](const char *time_stamp)
                                 { return my_node_mqtt.publishDetection(my_hospital_id.c_str(), my_node_hospital.c_str(),
                                                                        my_node_id.c_str(),
                                                                        room_name.c_str(),
                                                                        tag_id,
                                                                        time_stamp); });
  if (!ok)
  {
    Serial.println("[MQTT] Detection publish failed.");
  }
}

/**
 * @brief
 *
 * @param tag_id
 */
void NodeManager::publishRegistration(const char *tag_id)
{
  bool ok = publishWithTimestamp([&](const char *time_stamp)
                                 { return my_node_mqtt.publishRegistration(my_hospital_id.c_str(), my_node_hospital.c_str(),
                                                                           my_node_id.c_str(),
                                                                           tag_id,
                                                                           time_stamp); });
  if (!ok)
  {
    Serial.println("[MQTT] Registration publish failed.");
  }
}

/**
 * @brief
 *
 */
void NodeManager::handleHeartbeat()
{
  uint32_t now = my_clock.millisNow();

  if ((uint32_t)(now - last_heartbeat_time) < heartbeat_interval)
  {
    return;
  }

  String room_name = checkRole(my_node_role);

  // Serial.print("[MQTT] Room: ");
  // Serial.println(room_name);

  if (publishWithTimestamp([&](const char *time_stamp)
                           { return my_node_mqtt.publishHeartbeat(my_hospital_id.c_str(), my_node_hospital.c_str(),
                                                                  my_node_id.c_str(),
                                                                  room_name.c_str(),
                                                                  time_stamp); }))
  {
    /* code */
    last_heartbeat_time = now;
  }
  else
  {
    /* code */
    Serial.println("[MQTT] Heartbeat publish failed.");
  }
}

/**
 * @brief
 *
 */
void NodeManager::sayHello()
{
  my_node_msg = MY_DEFAULT_GREET_IN_MSG;
  my_node_stat = MY_ONLINE_STAT;
  handleGreetings(my_node_msg.c_str(), my_node_stat.c_str());
}

/**
 * @brief
 *
 */
void NodeManager::sayGoodbye()
{
  my_node_msg = MY_DEFAULT_GREET_OUT_MSG;
  my_node_stat = MY_OFFLINE_STAT;
  handleGreetings(my_node_msg.c_str(), my_node_stat.c_str());
}

/**
 * @brief
 *
 * @param msg
 * @param stat
 */
void NodeManager::handleGreetings(const char *msg, const char *stat)
{
  String room_name = checkRole(my_node_role);

  bool ok = publishWithTimestamp([&](const char *time_stamp)
                                 { return my_node_mqtt.publishGreeting(my_hospital_id.c_str(), my_node_hospital.c_str(),
                                                                       my_node_id.c_str(),
                                                                       room_name.c_str(),
                                                                       msg,
                                                                       stat,
                                                                       time_stamp); });
  if (!ok)
  {
    Serial.println("[MQTT] Status publish failed.");
  }
}