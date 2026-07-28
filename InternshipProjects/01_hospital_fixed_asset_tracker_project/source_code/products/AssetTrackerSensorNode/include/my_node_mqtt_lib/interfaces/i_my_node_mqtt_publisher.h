/**
 * @file i_my_node_mqtt_publisher.h
 * @author Farros Ramzy (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-04-07
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <stdint.h>
#include "node_config.h"

class IMyNodeMQTTPublisher
{
public:
    virtual ~IMyNodeMQTTPublisher() {};
    
    virtual bool publishToMyNodeNetMQTT(const char *, const char *) = 0;
};
