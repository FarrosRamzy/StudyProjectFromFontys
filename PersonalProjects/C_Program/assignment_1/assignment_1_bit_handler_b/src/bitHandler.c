#include <bitHandler.h>

void createMaskForByte(uint8_t size, uint8_t shift, uint8_t *mask)
{
    *mask = 0;
    uint8_t i = 0;

    while (i < size)
    {
        *mask |= (1 << i);
        i++;
    }

    *mask = *mask << shift;
}

void applyMaskToByte(uint8_t byte, uint8_t mask, char mode[], uint8_t *maskedValue)
{
    if (strcmp(mode, "Clear") == 0)
    {
        *maskedValue = byte & ~mask;
    }
    else if (strcmp(mode, "Set") == 0)
    {
        *maskedValue = byte | mask;
    }
    else
    {
        *maskedValue = NULL;
    }
}

void combineBytesToWord(uint8_t lowByte, uint8_t highByte, uint16_t *word)
{
    *word = (highByte << 8) | lowByte;
}

void swapNibblesInByte(uint8_t byte, uint8_t *swapped)
{
    uint8_t highNibble = byte >> 4;
    uint8_t lowNibble = byte << 4;

    *swapped = lowNibble | highNibble;
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

void toggleBitInByte(uint8_t byte, uint8_t position, uint8_t *toggledByte)
{
    *toggledByte = byte ^ (1 << position);
}

void compareBytes(uint8_t byteOne, uint8_t byteTwo, uint8_t *numberOfBits)
{
    uint8_t bitsCount = 0;
    uint8_t mask = 1;
    uint8_t sizeOfByte = 0;
    uint8_t byte = byteOne ^ byteTwo;
    uint8_t savedByte = byte;
    uint8_t i = 0;

    while (byte != 0)
    {
        sizeOfByte++;
        byte = (byte >> 1);
    }

    while (i < sizeOfByte)
    {
        if ((savedByte & mask) != 0)
        {
            bitsCount = bitsCount + 1;
        }
        mask = (mask << 1);
        i++;
    }

    *numberOfBits = bitsCount;
}



/*-----------------------Additional Challenges--------------------------*/

void reverseByte(uint32_t longWord, uint32_t *reversedLongWord)
{
    uint32_t sizeOfLongWord = sizeof(longWord) * 8 - 1;
    uint32_t value = longWord;

    longWord = longWord >> 1;
    while (longWord)
    {
        value = value << 1;
        value = value | (longWord & 1);
        longWord = longWord >> 1;
        sizeOfLongWord--;
    }
    value = value << sizeOfLongWord;
    *reversedLongWord = value;
}

void sortNibbles(uint32_t longWord, uint32_t *sortedLongWord)
{
    uint32_t longWordArray[LONG_WORD_NIBBLE_ARRAY_SIZE];
    uint32_t temp = 0;
    uint8_t counter = 0;
    uint32_t newLongWord = 0;

    for (uint32_t i = 0; i < NIBBLES_IN_LONG_WORD; i++)
    {
        if (longWord != 0)
        {
            longWordArray[i] = longWord & 0X0F;
            longWord = longWord >> 4;
            counter++;
        }
    }

    for (uint32_t j = 0; j < counter; j++)
    {
        for (uint32_t k = j + 1; k < counter; k++)
        {
            if (longWordArray[j] > longWordArray[k])
            {
                temp = longWordArray[j];
                longWordArray[j] = longWordArray[k];
                longWordArray[k] = temp;
            }
        }
    }

    for (uint32_t l = 0; l < counter; l++)
    {
        newLongWord = newLongWord | longWordArray[l];
        if (l < counter - 1)
        {
            newLongWord = newLongWord << 4;
        }
    }
    *sortedLongWord = newLongWord;
}

void swapOddAndEvenBits(uint32_t longWord, uint32_t *swappedLongWordBits)
{
    uint32_t oddBits = longWord & 0X55555555;
    uint32_t evenBits = longWord & 0XAAAAAAAA;

    oddBits = oddBits << 1;
    evenBits = evenBits >> 1;

    *swappedLongWordBits = (oddBits | evenBits);
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