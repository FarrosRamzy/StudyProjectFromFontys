#include <file_channeler.h>

/**
 * @brief interrupt the input byte by flipping a bit from it on a random position
 * between 0 and 7. Return the interrupt position.
 *  
 * @param inputByte a byte which received from read file.
 * @param outputByte the interrupted byte.
 * @return uint8_t 
 */
uint8_t transmitByte(uint8_t inputByte, uint8_t *outputByte)
{
    uint8_t position = rand() % BITS;
    *outputByte = inputByte ^ (1 << position);
    return position;
}

/**
 * @brief A function to write all transmitted data to the output file.
 * This function returns 0 if it succeed, and returns 1 if it not succeed.
 * 
 * @param transmittedByte the transmitted data from the transmitByte function.
 * @param writeCounter a counter to keep track the writing data process.
 * @param outputFile the file where the data should be written to.
 * @return int 
 */
int writeOutput(uint8_t transmittedByte, uint8_t *writeCounter, FILE *outputFile)
{
    int bytesWritten = fwrite(&transmittedByte, sizeof(uint8_t), 1, outputFile);

    if (bytesWritten != 1) {
        printf("An error occurred while writing to output file.\n");
        return 1;
    }

    (*writeCounter)++;
    
    return 0;
}

/**
 * @brief This function is a recursion to read the input file's data, change
 * or interrupt the byte during the transmission, and write the data to the
 * output file. This function is actually act as the main program. It will
 * return 0 if the process succeed. And return 1 if the process failed.
 * 
 * @param inputDataName the char argument file of the input file.
 * @param outputDataName the char argument file of the output file.
 * @param readCounter a counter to keep track on the reading process.
 * @param transmitCounter a counter to keep track on the transmit process.
 * @return int 
 */
int channelFile(char *inputDataName, char *outputDataName, uint8_t *readCounter, uint8_t *transmitCounter)
{
    FILE *inputFile = NULL;
    FILE *outputFile = NULL;

    int outputWritten = 0;
    uint8_t interruptPosition = 0;

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

    uint8_t transmittedChar;
    uint8_t inputChar;

    while (fread(&inputChar, sizeof(uint8_t), 1, inputFile) != 0)
    {
        (*readCounter)++;
        interruptPosition = transmitByte(inputChar, &transmittedChar);
        outputWritten = writeOutput(transmittedChar, transmitCounter, outputFile);
    }

    printf("Last interrupt position is: %hhd\n", interruptPosition);

    fclose(inputFile);
    fclose(outputFile);

    if (outputWritten == 1)
    {
        return 1;
    }

    return 0;
}