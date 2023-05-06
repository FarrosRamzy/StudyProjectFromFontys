#ifndef BITHANDLER_H
#define BITHANDLER_H

#include <stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>

#define MAX_CHAR_ARRAY_SIZE 20

/* 
 * A function to returns an 8-bit value with a given 'size' and 'shift'.
 */
uint8_t createMaskForByte(uint8_t,uint8_t);

/* 
 * A function to applies 'mask' to 'byte' depending on the 'mode'. Input 'mode' is a character that can be a "Set" or a "Clear". This function returns an 8-bit value.
 */
uint8_t applyMaskToByte(uint8_t,uint8_t,char[]);

/* 
 * A function to swap nibble values within a byte. This function returns an 8-bit value.
 */
uint8_t swapNibblesInByte(uint8_t);

/* 
 * A function to toggles a bit in a 'byte'. The index of the toggled bit is given by ‘position’. This function returns an 8-bit value.
 */
uint8_t toggleBitInByte(uint8_t,uint8_t);

/* 
 * A function to compare two bytes by toggling bits between 'byteOne' and 'byteTwo'. This function returns the result as an 8-bit value.
 */
uint8_t compareBytes(uint8_t,uint8_t);

/* 
 * A function to combine the 8-bit 'highByte' and a 'lowByte' into a 'word'. This function returns a 16-bit value.
 */
uint16_t combineBytesToWord(uint8_t,uint8_t);

/* 
 * A function to check if the 'byte' is a power of two. This function returns 'True' or 'False' due to the 'byte' value.
 */
bool isBytePowerOfTwo(uint16_t);



/*--------------------------- Extra Functions ----------------------------*/

/* 
 * A function to convert a 32-bit 'inputVal' into the binary numbers and printing them to the terminal.
 */
void convertLongWordToBinary(uint32_t);

/* 
 * A function to convert a 16-bit 'inputVal' into the binary numbers and printing them to the terminal.
 */
void convertWordToBinary(uint16_t);

/* 
 * A function to convert a 8-bit 'inputVal' into the binary numbers and printing them to the terminal.
 */
void convertByteToBinary(uint8_t);

#endif