/**
 * @file my_node_mqtt_config.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2026-05-13
 * 
 * @copyright Copyright (c) 2026
 * 
 */

 #include "my_node_mqtt_lib/my_node_mqtt.h"

/**
 * @brief
 *
 */
void MyNodeMQTT::startMyMQTT()
{
  updateServerConfig();
  my_node_mqtt_client.setKeepAlive(45);
  my_node_mqtt_client.setSocketTimeout(5);
  my_node_mqtt_client.setBufferSize(1024);
  my_node_mqtt_client.setCallback(MyNodeMQTT::myMQTTCallbackRouter);
}

/**
 * @brief
 *
 * @param net_port
 */
void MyNodeMQTT::setNodeMQTTPort(int net_port)
{
  my_node_net_port = net_port;
  updateServerConfig();
}

/**
 * @brief
 *
 * @param net_server
 */
void MyNodeMQTT::setNodeMQTTServer(const char *net_server)
{
  my_node_net_server = net_server;
  updateServerConfig();
}

/**
 * @brief
 *
 * @param client_id
 */
void MyNodeMQTT::setNodeMQTTClientId(const char *client_id)
{
  my_node_net_id = client_id;
}

/**
 * @brief
 *
 */
void MyNodeMQTT::updateServerConfig()
{
  my_node_mqtt_client.setServer(my_node_net_server, my_node_net_port);
}