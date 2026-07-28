/**
 * @file main.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.2
 * @date 2026-04-13
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <Arduino.h>
#include <WiFi.h>

#include "my_node_manager_lib/node_manager.h"
#include "my_node_manager_lib/node_clock.h"
#include "my_node_manager_lib/node_board_control.h"
#include "my_node_network_lib/my_node_wifi.h"
#include "my_node_network_lib/my_node_network_config.h"
#include "my_node_mqtt_lib/my_node_mqtt.h"
#include "my_node_rfid_lib/my_node_rfid.h"
#include "my_node_led_lib/node_status_led.h"
#include "node_config.h"

WiFiClient my_wifi_client;
MyNodeWiFi my_wifi;
MyNodeNetworkConfig my_net_config;
MyNodeMQTT my_mqtt(my_wifi_client, "", MY_NET_MQTT_PORT_TEST, "", nullptr);
MyNodeRFID my_rfid(Serial2, RFID_RX_PIN, RFID_TX_PIN, RFID_EN_PIN);
NodeStatusLED my_led(CONNECTION_LED_PIN, DETECTION_LED_PIN);
NodeClock my_clock;
NodeBoardControl my_board;

NodeManager my_node_manager(my_wifi, my_net_config, my_mqtt, my_rfid, my_led, my_clock, my_board);

void setup()
{
  Serial.begin(RFID_BAUDRATE);
  my_node_manager.beginNodeSystem();
}

void loop()
{
  my_node_manager.runNodeSystem();
}
