#include <file_decoder.h>

/**
 * @brief A function to handle the incoming bytes and extract the nibbles.
 * 
 * @param firstByte the first read byte that might contains the low nibble.
 * @param secondByte the second read byte that might contains the high nibble.
 * @param outputCharacter a combined nibbles from the extracted first byte and second byte.
 */
void decodeByte(uint8_t firstByte, uint8_t secondByte, uint8_t *outputCharacter)
{
    uint8_t firstNibble = getNibble(firstByte);
    uint8_t secondNibble = getNibble(secondByte);

    uint8_t highNibble = (firstNibble & 0b01111000) << 1;
    uint8_t lowNibble = (secondNibble & 0b01111000) >> 3;

    uint8_t byte = highNibble | lowNibble;
    *outputCharacter = byte;
}

/**
 * @brief a function to check the data validality by looking at the parity value.
 * 
 * @param value the input byte parameter.
 * @param parityMask the mask from the parity diagram.
 * @return true 
 * @return false 
 */
bool checkInterrupt(uint8_t value, uint8_t parityMask)
{
    uint8_t checkedValue = value & parityMask;
    uint8_t mask = 0b10000000;
    uint8_t counter = 0;

    for (uint8_t i = 0; i < BITS; i++)
    {
        if (checkedValue & mask)
        {
            counter++;
        }
        mask = mask >> 1;
    }

    return counter % 2 != 0; 
}

/**
 * @brief Get the real nibble value from the high or low input byte.
 * 
 * @param inputByte the input parameter which is going to be extracted.
 * @return uint8_t 
 */
uint8_t getNibble(uint8_t inputByte)
{
    bool firstCircleCorrupted = checkInterrupt(inputByte, FIRST_PARITY_MASK);
    bool secondCircleCorrupted = checkInterrupt(inputByte, SECOND_PARITY_MASK);
    bool thirdCircleCorrupted = checkInterrupt(inputByte, THIRD_PARITY_MASK);

    if (firstCircleCorrupted)
    {
        if (secondCircleCorrupted)
        {
            if (thirdCircleCorrupted)
            {
                inputByte = inputByte ^ 0b00010000;
            }
            else
            {
                inputByte = inputByte ^ 0b00001000;
            }
        }
        else
        {
            if (thirdCircleCorrupted)
            {
                inputByte = inputByte ^ 0b00100000;
            }
            else
            {
                inputByte = inputByte ^ 0b00000001;
            }
        }
    }
    else
    {
        if (secondCircleCorrupted)
        {
            if (thirdCircleCorrupted)
            {
                inputByte = inputByte ^ 0b01000000;
            }
            else
            {
                inputByte = inputByte ^ 0b00000010;
            }
        }
        else
        {
            if (thirdCircleCorrupted)
            {
                inputByte = inputByte ^ 0b00000100;
            }
        }        
    }
    return inputByte;
}

/**
 * @brief A function to write the decoded values from the decodeByte function
 * to the output file. This function returns 0 if the process is succeed, and
 * returns 1 if the process is not succeed.
 * 
 * @param decodedByte the data that is going to be written to the output file.
 * @param decodeCounter a counter to keeptrack the writing decoded data process.
 * @param outputFile the file where the data should be written to.
 * @return int 
 */
int writeOutput(uint8_t decodedByte, uint8_t *decodeCounter, FILE *outputFile)
{
    int bytesWritten = fwrite(&decodedByte, sizeof(uint8_t), 1, outputFile);

    if (bytesWritten != 1) {
        printf("An error occurred while writing to output file.\n");
        return 1;
    }

    (*decodeCounter)++;
    
    return 0;

}

/**
 * @brief The main function of the decoder file. This function should check the
 * input and output files' availability, then run the decodeByte function before
 * writing the results to the output file.
 * 
 * @param inputDataName the input file char argument, where the data should be received.
 * @param outputDataName the output file char argument, where the data should be written.
 * @param readCounter a counter to keep track on the reading process.
 * @param decodeCounter a counter to keep track on the decoding process.
 * @return int 
 */
int decodeFile(char *inputDataName, char *outputDataName, uint8_t *readCounter, uint8_t *decodeCounter)
{
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;

    int decodedData = 0;

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

    uint8_t decodedByte;
    uint8_t bytes[SIZE_OF_BYTES];

    while (fread(&bytes, SIZE_OF_BYTES, 1, inputFile) == 1)
    {
        (*readCounter)++;
        decodeByte(bytes[0],bytes[1], &decodedByte);
        decodedData = writeOutput(decodedByte, decodeCounter, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    if (decodedData == 1)
    {
        return 1;
    }
    
    return 0;
}