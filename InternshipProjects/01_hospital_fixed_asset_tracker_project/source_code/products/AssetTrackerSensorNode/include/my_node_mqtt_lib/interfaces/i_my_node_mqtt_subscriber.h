/**
 * @file i_my_node_mqtt_subscriber.h
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

class IMyNodeMQTTSubscriber
{
public:
    virtual ~IMyNodeMQTTSubscriber() {};
    
    virtual bool subscribeToMyNodeNetMQTT(const char *) = 0;
    virtual void unsubscribeMyNodeNetMQTT(const char *) = 0;
};
