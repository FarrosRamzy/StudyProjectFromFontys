/**
 * @file node_rfid_manager.cpp
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
void NodeManager::handleRFID()
{
  my_node_rfid.runRFIDConfiguration();
  if (!my_node_rfid.isRFIDConfigurationFinished())
  {
    return;
  }
  

  char tag_buffer[RFID_BUFFER_SIZE] = {0};

  if (!my_node_rfid.readDetectedTag(tag_buffer, sizeof(tag_buffer)))
  {
    my_node_status_led.setRedDetecting(false);
    return;
  }

  my_node_status_led.setRedDetecting(true);

  if (isDuplicateTag(tag_buffer))
  {
    return;
  }

  if (!my_node_is_provisioned)
  {
    return;
  }

  if (my_node_role == MY_ROLE_IS_CHECKPOINT)
  {
    publishCheckpoint(tag_buffer);
  }
  else if (my_node_role == MY_ROLE_IS_REGISTRATION)
  {
    publishRegistration(tag_buffer);
  }
  else
  {
    Serial.println("[RFID] Unknown node role. Ignoring scan.");
  }
}

/**
 * @brief
 *
 * @param tag_id
 * @return true
 * @return false
 */
bool NodeManager::isDuplicateTag(const char *tag_id)
{
  uint32_t now = my_clock.millisNow();

  if (strcmp(last_tag_id, tag_id) == 0)
  {
    if ((uint32_t)(now - last_tag_time) < duplicate_suppress_ms)
    {
      return true;
    }
  }

  strncpy(last_tag_id, tag_id, RFID_BUFFER_SIZE - 1);
  last_tag_id[RFID_BUFFER_SIZE - 1] = '\0';
  last_tag_time = now;

  return false;
}
