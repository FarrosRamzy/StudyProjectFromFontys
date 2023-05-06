#ifndef BITHANDLER_H
#define BITHANDLER_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CHAR_ARRAY_SIZE 20
#define NIBBLES_IN_LONG_WORD 8
#define LONG_WORD_NIBBLE_ARRAY_SIZE 8

/* 
 * A function to returns an 8-bit 'mask' with a given 'size' and 'shift'.
 */
void createMaskForByte(uint8_t, uint8_t, uint8_t *);

/* 
 * A function to applies 'mask' to 'byte' depending on the 'mode'. Input 'mode' is a character that can be a "Set" or a "Clear". This function returns 'maskedValue'.
 */
void applyMaskToByte(uint8_t, uint8_t, char[], uint8_t *);

/* 
 * A function to swap nibble values within a byte. This function returns 'swapped'.
 */
void swapNibblesInByte(uint8_t, uint8_t *);

/* 
 * A function to toggles a bit in a 'byte'. The index of the toggled bit is given by ‘position’. This function returns ‘toggledByte’.
 */
void toggleBitInByte(uint8_t, uint8_t, uint8_t *);

/* 
 * A function to compare two bytes by toggling bits between 'byteOne' and 'byteTwo'. This function returns the number of toggled bits as 'numberOfBits'.
 */
void compareBytes(uint8_t, uint8_t, uint8_t *);

/* 
 * A function to combine the 8-bit 'highByte' and a 'lowByte' into a 16-bit 'word'.
 */
void combineBytesToWord(uint8_t, uint8_t, uint16_t *);

/* 
 * A function to check if the 'byte' is a power of two. This function returns 'True' or 'False' due to the 'byte' value.
 */
bool isBytePowerOfTwo(uint16_t);



/*-----------------------Additional Challenges--------------------------*/

/* 
 * A function to reverse the order of bits inside a 32-bit 'longWord' input value by using a shifting method. This function returns a 32-bit 'reversedLongWord'.
 */
void reverseByte(uint32_t, uint32_t *);

/* 
 * A function to sorts the nibbles within a 32-bit 'longWord' input into a 32-bit 'sortedLongWord'.
 */
void sortNibbles(uint32_t, uint32_t *);

/* 
 * A function too swaps the odd and even bits position within the 32-bit 'longWord' input and return it as 'swappedLongWordBits'.
 */
void swapOddAndEvenBits(uint32_t, uint32_t *);



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