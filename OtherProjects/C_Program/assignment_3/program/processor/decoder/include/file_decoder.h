#ifndef FILE_DECODER_H
#define FILE_DECODER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define MIN_ARGUMENTS 3
#define SIZE_OF_BYTES 2
#define BITS 8

#define FIRST_PARITY_MASK 0b00111001
#define SECOND_PARITY_MASK 0b01011010
#define THIRD_PARITY_MASK 0b01110100

/*Work patterns:
* Program read the transmitted input file and create the output file.
* Data from the input should be readed per character/per word until the end of the file.
* Every nibbles from each byte in the input should be decoded.
* The decode should find the corrupted bytes from the transmitted data and repair it as per nibble.
* The decode should add each nibbles from high and low and combine them into a new byte.
* The decoded bytes should be fully written into the output file. 
*/

void decodeByte(uint8_t, uint8_t, uint8_t *);
int decodeFile(char *, char *, uint8_t *, uint8_t *);
uint8_t getNibble(uint8_t);
bool checkInterrupt(uint8_t, uint8_t);
int writeOutput(uint8_t, uint8_t *, FILE *);

#endif