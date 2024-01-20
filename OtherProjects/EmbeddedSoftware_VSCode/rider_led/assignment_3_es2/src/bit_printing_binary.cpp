#include <led_mask.h>

/**
 * @brief This function prints the BINARY representation
 *        of any U8BIT number that it is given.
 * 
 * @param binNo The desired number to be printed in BINARY representation.
 */
void BIT8_BinaryPrintf (uint8_t binNo)
{
    uint8_t i;
    for(i = (1<<7); i > 0; i = i / 2)
    {
        if((binNo & i) != 0)
            Serial.print("1");
        else
            Serial.print("0");
    }
    Serial.println("");
}

/**
 * @brief This function prints the BINARY representation
 *        of any U16BIT number that it is given.
 * 
 * @param binNo The desired number to be printed in BINARY representation.
 */
void BIT16_BinaryPrintf (uint16_t binNo)
{
    uint16_t i;
    for(i = (1<<15); i > 0; i = i / 2)
    {
        if((binNo & i) != 0)
            Serial.print("1");
        else
            Serial.print("0");
    }
    Serial.println("");
}