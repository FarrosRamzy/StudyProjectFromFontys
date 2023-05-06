#include <BitHelper.h>


/**
 * Combine 2 bytes and 1 nibble to form a 20-bit integer
 * @param byteMsb The left-most byte, containing the Msb
 * @param byteLsb The byte in the middle
 * @param byteMsb Format: 0x0N, where N is a number between 0 and F. The right-most byte, containing the LSB
 * @returns The 20 bit number, contained in a signed 32-bit integer
*/
int32_t get20BitNumberFromBytes(uint8_t byteMsb, uint8_t byteLsb, uint8_t byteXLsb) // TODO: rename?
{
    int32_t result = byteMsb;
    result <<= 8;
    result |= byteLsb;
    result <<= 4;
    result |= byteXLsb;

    return result;
}

/**
 * Combine 2 bytes to create an unsigned short
 * @param byteMsb The left byte of the short
 * @param byteLsb The right byte of the short
 * @returns The resulting unsigned short
*/
uint16_t getUnsignedShortFromBytes(uint8_t byteMsb, uint8_t byteLsb)
{
    uint16_t result = byteMsb;
    result <<= 8;
    result |= byteLsb;

    return result;
}