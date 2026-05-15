/**
 * @file node_config.h
 * @author Farros Ramzy (you@domain.com)
 * @brief 
 * @version 0.5
 * @date 2026-04-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#pragma once

////////////////////////////////////////////////////////////////
//NOTE - to upload the program to the modules:
//       1. Go to terminal, type pio run --target buildfs
//       2. type pio run --target uploadfs
//       3. upload program normally
////////////////////////////////////////////////////////////////

//NOTE - Web Server credentials
#define MY_WEB_SERVER_PORT 80
#define MY_WEB_HTTP_RESERVE 4000
#define MY_DEFAULT_ACCESS_POINT_PASSWORD "nodeSetup252!"
#define MY_ACCESS_POINT_SIZE 24

#define MY_BOOTSTRAP_BASE_URL "https://rfid-hospital-item-tracker-backend.onrender.com"
#define MY_BOOTSTRAP_BASE_FILE "/esp_index.html"
#define MY_BOOTSTRAP_RESULT_FILE "/esp_boot_result.html"
#define MY_BOOTSTRAP_BASE_PORT 8000

#define MY_FIRMWARE_VERSION "1.0.0"

//NOTE - Clock Timer
#define CLOCK_TIME_CHECK_MS 500
#define LATEST_YEAR_LIMIT 2024
#define EARLIEST_YEAR_LIMIT 1900
#define MY_CLOCK_TIMEOUT_LIMIT 10000

#define MY_NODE_NETWORK_TIMER_MS 10000
#define MY_NODE_NETWORK_TEST_TIMER_MS 250

//NOTE - Clock server
#define PRIMARY_NTP_SERVER "pool.ntp.org"
#define BACKUP_NTP_SERVER "time.nist.gov"

//NOTE - MQTT network credentials
#define MY_NET_MQTT_BROKER_TEST "broker.hivemq.com"
#define MY_NET_MQTT_PORT_TEST 1883
#define MY_NET_MQTT_MIN_PORT 0
#define MY_NET_MQTT_MAX_PORT 65535

//NOTE - Network button
#define CONFIG_RESET_BUTTON_PIN 14
#define CONFIG_RESET_HOLD_MS 3000

#define MY_DEFAULT_DEVICE_ID_FORMAT "IH-MED-NODE"
#define MY_DEFAULT_NODE_ID "node-a"

#define MY_DEFAULT_GREET_IN_MSG "Hello!"
#define MY_DEFAULT_GREET_OUT_MSG "Goodbye!"

#define MY_ONLINE_STAT "ONLINE"
#define MY_OFFLINE_STAT "OFFLINE"

#define MY_ROLE_IS_CHECKPOINT "CHECKPOINT"
#define MY_ROLE_IS_REGISTRATION "REGISTRATION"

//NOTE - MQTT network message type
#define DEFAULT_REGISTRATION_TABLE_TOPIC "imh-hospital/registration-table"
#define DEFAULT_DETECTION_TOPIC "imh-hospital/checkpoint/detection"
#define DEFAULT_HEARTBEAT_TOPIC "imh-hospital/checkpoint/heartbeat"

#define MQTT_TOPIC_ROOT "hospital"
#define MQTT_TOPIC_NODES "nodes"
#define MQTT_TOPIC_RFID "rfid"
#define MQTT_TOPIC_DETECTION "detected"
#define MQTT_TOPIC_HEARTBEAT "heartbeat"
#define MQTT_TOPIC_STATUS "status"
#define MQTT_TOPIC_REGISTRATION_SCAN "asset-registration"

#define MY_DEFAULT_HOSPITAL_ID "imh-hospital"

//NOTE - Node's heartbeat counter values
#define FIRST_HEARTBEAT_MS 0
#define HEARTBEAT_INTERVAL_MS 30000
#define MAX_HEARTBEAT_TIMEOUT 3

#define FIRST_RECONNECT_ATTEMPT 0
#define NET_RECONNECT_INTERVAL_MS 5000

//NOTE - LEDs' pins
#define DETECTION_LED_PIN 13
#define CONNECTION_LED_PIN 12

//NOTE - LEDs' counter values
#define LED_START_TIMER 0
#define BLINK_DURATION_MS 200

//NOTE - RFID pins
#define RFID_RX_PIN 16
#define RFID_TX_PIN 17
#define RFID_EN_PIN 4

#define RFID_BAUDRATE 115200

//NOTE - System payload data sizes
#define SIZE_OF_TOPIC 192
#define SIZE_OF_PAYLOAD 512
#define RFID_BUFFER_SIZE 100
#define RFID_FRAME_BUFFER_SIZE 128
#define RFID_START_BUFFER_VAL 0
#define RFID_MIN_BUFFER_LEN 8
#define RFID_MAX_BUFFER_LEN 32

#define RFID_READER_READY_DELAY_MS 500
#define RFID_AFTER_STOP_DELAY_MS 200
#define RFID_CONFIG_RESPONSE_TIMEOUT_MS 1500

#define RFID_START_TAG_TIMER 0
#define RFID_TIMEOUT_MS 500
#define RFID_DUPLICATE_SUPPRESS_MS 2500
#define MQTT_PUBLISH_RETAIN false
#define MQTT_PUBLISH_QOS 0

//NOTE - RFID set transmit power
#define RFID_POWER_TRANSMIT_0 0
#define RFID_POWER_TRANSMIT_2 200
#define RFID_POWER_TRANSMIT_6 600
#define RFID_POWER_TRANSMIT_8 800
#define RFID_POWER_TRANSMIT_10 1000
#define RFID_POWER_TRANSMIT_12 1200
#define RFID_POWER_TRANSMIT_15 1500
#define RFID_POWER_TRANSMIT_18 1800
#define RFID_POWER_TRANSMIT_20 2000
#define RFID_POWER_TRANSMIT_26 2600


#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>