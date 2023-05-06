#ifndef FILE_CHANNELER_H
#define FILE_CHANNELER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <time.h>

#define MIN_ARGUMENTS 3
#define BITS 8

/*Work patterns:
* Program read the input file and create the output file.
* Data from the encoded input should be readed per character/per word until the end of the file.
* One of every nibbles from each byte in the input should be interrupted (changed).
* The transmitted bytes should be fully written into the output file.
*/

uint8_t transmitByte(uint8_t, uint8_t*);
int channelFile(char *, char *, uint8_t *, uint8_t *);
int writeOutput(uint8_t, uint8_t *, FILE*);


#endif