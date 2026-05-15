/**
 * @file node_timestamp_manager.cpp
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-14
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "my_node_manager_lib/node_manager.h"

/**
 * @brief
 *
 */
void NodeManager::beginTimeSync()
{
  configTime(7 * 3600, 0, PRIMARY_NTP_SERVER, BACKUP_NTP_SERVER);

  my_time_synced = false;
  my_time_sync_started = true;
  my_time_sync_start_ms = my_clock.millisNow();
  my_last_time_sync_check_ms = 0;

  Serial.println("[TIME] WIB sync started...");
}

/**
 * @brief
 *
 * @param buffer
 * @param buffer_size
 * @return true
 * @return false
 */
bool NodeManager::getCurrentTimestampWIB(char *buffer, size_t buffer_size)
{
  if (buffer == nullptr || buffer_size < 26)
  {
    return false;
  }

  time_t now;
  struct tm time_info;

  time(&now);
  localtime_r(&now, &time_info);

  if (time_info.tm_year <= (LATEST_YEAR_LIMIT - EARLIEST_YEAR_LIMIT))
  {
    return false;
  }

  return strftime(buffer, buffer_size, "%Y-%m-%dT%H:%M:%S+07:00", &time_info) > 0;
}

/**
 * @brief
 *
 */
void NodeManager::updateTimeSync()
{
  if (!my_time_sync_started || my_time_synced)
  {
    return;
  }

  uint32_t now_ms = my_clock.millisNow();

  // Check every 500 ms
  if ((uint32_t)(now_ms - my_last_time_sync_check_ms) < CLOCK_TIME_CHECK_MS)
  {
    return;
  }

  my_last_time_sync_check_ms = now_ms;

  time_t now = 0;
  struct tm time_info = {};

  time(&now);
  localtime_r(&now, &time_info);

  if (time_info.tm_year > (LATEST_YEAR_LIMIT - EARLIEST_YEAR_LIMIT))
  {
    my_time_synced = true;
    my_time_sync_started = false;
    Serial.println("[TIME] WIB synced!");
    return;
  }
  
  // Optional timeout after 10 seconds.
  if ((uint32_t)(now_ms - my_time_sync_start_ms) > MY_CLOCK_TIMEOUT_LIMIT)
  {
    Serial.println("[TIME] WIB sync timeout.");
    my_time_sync_started = false;
  }
  
}