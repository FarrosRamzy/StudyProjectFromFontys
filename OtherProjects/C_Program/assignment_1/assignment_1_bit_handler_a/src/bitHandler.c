#include <bitHandler.h>

uint8_t createMaskForByte(uint8_t size, uint8_t shift)
{
    //initialize mask to be 0xffffffff.
    uint8_t mask = -1;

    //Size up the mask by using the size value.
    uint8_t leftShift = 8 - size; 
    uint8_t rightShift = leftShift - shift;

    //positioning the mask by using its shift value.
    mask = mask << leftShift;
    mask = mask >> rightShift;

    //return the mask value.
    return mask;
}

uint8_t applyMaskToByte(uint8_t byte, uint8_t mask, char mode[])
{
    //initialize the output value.
    uint8_t maskedByte;

    //compare the char input and execute the value masking.
    if (strcmp(mode, "Clear") == 0)
    {
        maskedByte = byte & ~mask;
    }
    else if (strcmp(mode, "Set") == 0)
    {
        maskedByte = byte | mask;
    }
    else
    {
        printf("Typo detected!! Please Try Again, But Type The Command Correctly!\n");
        maskedByte = NULL;
    }

    //return the masked value.
    return maskedByte;
}

uint16_t combineBytesToWord(uint8_t lowByte, uint8_t highByte)
{
    //initialize the output value.
    uint16_t word;
    
    //insert the lowByte value after push the highByte value by 8 to the left to complete the word.
    word = (highByte << 8) | lowByte;

    //return the output value.
    return word;
}

uint8_t swapNibblesInByte(uint8_t byte)
{
    //initialize the output value.
    uint8_t swappedNibbles;

    //initialize the high and low nibbles from the input value.
    uint8_t highNibble = byte >> 4;
    uint8_t lowNibble = byte << 4;

    //swap the nibble position.
    swappedNibbles = lowNibble | highNibble;

    //return the output.
    return swappedNibbles;
}

bool isBytePowerOfTwo(uint16_t byte)
{
    if (byte == 0)
    {
        return false;
    }  
    while (byte != 1)
    {
        if (byte % 2 != 0)
        {
            return false;
        }
        byte = byte / 2;
    }

    return true;
}

uint8_t toggleBitInByte(uint8_t byte, uint8_t position)
{
    //initialize the output.
    uint8_t outputByte;

    //toggle a bit from the byte through a position using XOR.
    outputByte = byte ^ (1 << position);
    return outputByte;
}

uint8_t compareBytes(uint8_t byteOne, uint8_t byteTwo)
{
    //initialize the output.
    uint8_t numberOfBits = 0;

    //initialize the values of the function.
    uint8_t mask = 1;
    uint8_t sizeOfByte = 0;
    uint8_t byte = byteOne ^ byteTwo;
    uint8_t savedByte = byte;
    uint8_t i = 0;

    //counting the size of the byte.
    while (byte != 0)
    {
        sizeOfByte++;
        byte = (byte >> 1);
    }

    //counting the difference values from the byte.
    while (i < sizeOfByte)
    {
        if ((savedByte & mask) != 0)
        {
            numberOfBits = numberOfBits + 1;
        }
        mask = (mask << 1);
        i++;
    }

    //return the counted output.
    return numberOfBits;
}



/*------------------------- Extra Functions -----------------------------*/

void convertLongWordToBinary(uint32_t inputVal)
{
    for (uint32_t i = 1 << 31; i > 0; i = i / 2)
    {
        if (inputVal & i)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}

void convertWordToBinary(uint16_t inputVal)
{
    for (uint16_t i = 1 << 15; i > 0; i = i / 2)
    {
        if (inputVal & i)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}

void convertByteToBinary(uint8_t inputVal)
{
    for (uint8_t i = 1 << 7; i > 0; i = i / 2)
    {
        if (inputVal & i)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");
}