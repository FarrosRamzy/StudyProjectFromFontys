/**
 * @file my_node_mqtt.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-08
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_mqtt_lib/my_node_mqtt.h"

/**
 * @brief
 *
 */
MyNodeMQTT *MyNodeMQTT::my_active_instance = nullptr;

/**
 * @brief Construct a new My Node M Q T T:: My Node M Q T T object
 * 
 * @param net_client 
 * @param net_server 
 * @param net_port 
 * @param net_id 
 * @param my_node_callback 
 */
MyNodeMQTT::MyNodeMQTT(WiFiClient &net_client, const char *net_server, int net_port,
                       const char *net_id, void (*my_node_callback)(char *, uint8_t *, unsigned int))
    : my_node_mqtt_client(net_client), node_esp_client(net_client),
      my_node_net_server(net_server), my_node_net_port(net_port),
      my_node_net_id(net_id), my_mqtt_callback(my_node_callback),
      last_reconnect_attempt(FIRST_RECONNECT_ATTEMPT),
      reconnect_interval(NET_RECONNECT_INTERVAL_MS)
{
  my_active_instance = this;
}

/**
 * @brief Destroy the My Node M Q T T:: My Node M Q T T object
 *
 */
MyNodeMQTT::~MyNodeMQTT() {}