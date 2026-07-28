/**
 * @file my_node_mqtt_publisher.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief MQTT publishing helpers for node telemetry.
 * @version 0.4
 * @date 2026-04-23
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <ArduinoJson.h>
#include "my_node_mqtt_lib/my_node_mqtt.h"

/**
 * @brief
 *
 * @param my_net_topic
 * @param my_message
 * @return true
 * @return false
 */
bool MyNodeMQTT::publishToMyNodeNetMQTT(const char *my_net_topic,
                                        const char *my_message)
{
  if (!amIConnected())
  {
    Serial.println("[MQTT] Publish skipped: MQTT is not connected.");
    return false;
  }

  if (!hasRequiredText(my_net_topic) || !hasRequiredText(my_message))
  {
    Serial.println("[MQTT] Publish skipped: topic or payload is empty.");
    return false;
  }

  bool ok = my_node_mqtt_client.publish(my_net_topic, my_message, MQTT_PUBLISH_RETAIN);

  Serial.print("[MQTT] TX topic: ");
  Serial.println(my_net_topic);
  Serial.print("[MQTT] TX payload: ");
  Serial.println(my_message);
  Serial.print("[MQTT] TX result: ");
  Serial.println(ok ? "OK" : "FAILED");

  return ok;
}
