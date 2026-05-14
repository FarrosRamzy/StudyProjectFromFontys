#ifndef BIT_HELPER_H
#define BIT_HELPER_H

#include <Arduino.h>

// TODO: rename?
int32_t get20BitNumberFromBytes(uint8_t byteMsb, uint8_t byteLsb, uint8_t byteXLsb);

uint16_t getUnsignedShortFromBytes(uint8_t byteMsb, uint8_t byteLsb);

#endif