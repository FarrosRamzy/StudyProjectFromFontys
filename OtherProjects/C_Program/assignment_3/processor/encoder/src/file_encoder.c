#include <file_encoder.h>

/**
 * @brief a function to split-up a byte into two nibbles for the encoding.
 * 
 * @param inputByte is an input byte or character.
 * @param encodedByteHigh a result char of the high nibble after the encoding.
 * @param encodedByteLow a result char of the low nibble after the encoding.
 */
void encodeByte(uint8_t inputByte, uint8_t *encodedByteHigh, uint8_t *encodedByteLow)
{
    uint8_t lowNibble = inputByte & 0b00001111;
    uint8_t highNibble = (inputByte & 0b11110000) >> 4;
    *encodedByteLow = addNibbleParity(lowNibble);
    *encodedByteHigh = addNibbleParity(highNibble);
}

/**
 * @brief a function to create parities and add them to the input nibbles.
 *        This function returns a new byte with 3 parity digits in front of the input nibble.
 * 
 * @param inputNibble a 4 bits value that was received from the inputByte.
 *                    Can be a high or low nibble, depending on the encodeByte function.
 * @return uint8_t 
 */
uint8_t addNibbleParity(uint8_t inputNibble)
{
    uint8_t d0 = (inputNibble & (1 << 0)) >> 0;
    uint8_t d1 = (inputNibble & (1 << 1)) >> 1;
    uint8_t d2 = (inputNibble & (1 << 2)) >> 2;
    uint8_t d3 = (inputNibble & (1 << 3)) >> 3;

    uint8_t p0 = d0 ^ d1 ^ d2;
    uint8_t p1 = d0 ^ d1 ^ d3;
    uint8_t p2 = d1 ^ d2 ^ d3;

    inputNibble = inputNibble << 3;

    if (p0 == 1)
    {
        inputNibble = inputNibble | (1 << 0);
    }

    if (p1 == 1)
    {
        inputNibble = inputNibble | (1 << 1);
    }

    if (p2 == 1)
    {
        inputNibble = inputNibble | (1 << 2);
    }

    return inputNibble;
}

/**
 * @brief A function to write all of the encoded data to the output file.
 * This function is returning value 0 and 1, depends if the write data is success or not.
 * 
 * @param encodedNibble a byte of the encoded nibble from encodeByte function.
 * @param encodeCounter a counter to count the number written data.
 * @param outputFile the file where the data should be written to.
 * @return int 
 */
int writeEncodedNibbles(uint8_t encodedNibble, uint8_t *encodeCounter, FILE *outputFile)
{
    int bytesWritten = fwrite(&encodedNibble, sizeof(uint8_t), 1, outputFile);

    if (bytesWritten != 1) {
        printf("An error occurred while writing to output file.\n");
        return 1;
    }
    (*encodeCounter)++;
    return 0;
}

/**
 * @brief This function is a recursion to read the input file's data, encode, and write the data
 * to the output file. This function is actually act as the main of the program. It will return value 0
 * if the encoding has succeed, and return 1 if it has failed.
 * 
 * @param inputDataName the char argument file of the input file.
 * @param outputDataName the char argument file of the output file.
 * @param readCounter a counter to keep track the reading process.
 * @param encodeCounter a counter to keep track the encode process.
 * @return int 
 */
int encodeFile(char *inputDataName, char *outputDataName, uint8_t *readCounter, uint8_t *encodeCounter)
{
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;

    int encodedHighByte = 0;
    int encodedLowByte = 0;

    inputFile = fopen(inputDataName, "r");
    if (inputFile == NULL)
    {
        printf("input file is not available.\n");
        return 1;
    }

    outputFile = fopen(outputDataName, "w+");
    if (outputFile == NULL)
    {
        printf("output file is not available.\n");
        return 1;
    }

    uint8_t encodeByteHigh = 0;
    uint8_t encodeByteLow = 0;
    uint8_t inputChar;

    while (fread(&inputChar, sizeof(uint8_t), 1, inputFile) != 0)
    {
        (*readCounter)++;
        encodeByte(inputChar, &encodeByteHigh, &encodeByteLow);
        encodedHighByte = writeEncodedNibbles(encodeByteHigh, encodeCounter, outputFile);
        encodedLowByte = writeEncodedNibbles(encodeByteLow, encodeCounter, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    if ((encodedHighByte == 1) || (encodedLowByte == 1))
    {
        return 1;
    }

    return 0;
}