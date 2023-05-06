#ifndef FILE_ENCODER_H
#define FILE_ENCODER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define MIN_ARGUMENTS 3

/*Work patterns:
* Program read the input file and create the output file.
* Data from input should be readed per character/per word until the end of the file.
* Every nibbles from each byte in the input should be encoded.
* The encode should be started by creating three parities from each digit in a byte.
* The encoded bytes should be fully written into the output file. 
*/

int encodeFile(char *, char *, uint8_t *, uint8_t *);
void encodeByte(uint8_t, uint8_t *, uint8_t *);
uint8_t addNibbleParity(uint8_t);
int writeEncodedNibbles(uint8_t, uint8_t *, FILE *);

#endif