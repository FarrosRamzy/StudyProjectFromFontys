#include <bitHandler.h>

//////////////////////////////////////////////////////////////////////
//<assignment 1.1 bit handler>
//
//Course	    : C Programming (PRC)
//Assignment	: Basic uint8_t Return Functions
//Date		    : 21-03-2022
//Student		: Farros Ramzy(3767353)
//
//////////////////////////////////////////////////////////////////////

int main()
{
	char operatorChoices[MAX_CHAR_ARRAY_SIZE];
	uint8_t inputValue = 0;
	uint8_t position = 0;
	uint8_t byteOne = 0;
	uint8_t byteTwo = 0;
	uint8_t size = 0;
	uint8_t shift = 0;
	uint8_t mask = 0;

	uint8_t maskedValue = NULL;
	uint8_t swappedValue = 0;
	uint8_t toggledValue = 0;
	uint8_t numberOfBits = 0;

	uint16_t word = 0;

	uint8_t lowByte;
	uint8_t highByte;

	int choice = -1;

	printf("Hello World!\n");
	while (choice != 0)
	{
		printf("Menu:\n");
		printf("1: Create Mask Value.\n");
		printf("2: Apply Mask With Operator.\n");
		printf("3: Make A Word From Nibbles.\n");
		printf("4: Swap The Value's Nibbles.\n");
		printf("5: Is The Value Powered by 2?\n");
		printf("6: Toggle Value With Position.\n");
		printf("7: Compare bits value with 2 inputs.\n");
		printf("0: To quit\n");
		printf("\n");
		printf("Please enter your choice: ");
		scanf("%d", &choice);
		printf("\n");
		switch (choice)
		{
		case 1:
			printf("Create Mask Value.\n");
			printf("Set The Size:\n");
			scanf("%hhu", &size);
			printf("Set The Shift:\n");
			scanf("%hhu", &shift);
			mask = createMaskForByte(size, shift);
			printf("Your Mask is: ");
			printf("%hhu\n", mask);
			printf("Your Mask in Binary is ");
			convertByteToBinary(mask);
			printf("\n");
			break;
		case 2:
			printf("Apply Mask With Operator.\n");
			printf("Give Your Input:\n");
			scanf("%hhu", &inputValue);
			printf("Your Input Value in Binary is ");
			convertByteToBinary(inputValue);
			printf("Your Mask Value in Binary is ");
			convertByteToBinary(mask);
			printf("Please Type One of These Operators:\n");
			printf("- Set\n");
			printf("- Clear\n");
			scanf("%s", operatorChoices);
			maskedValue = applyMaskToByte(inputValue, mask, operatorChoices);
			if (maskedValue != NULL)
			{
				printf("Your Masked Value in Decimal is: ");
				printf("%hhu\n", maskedValue);
				printf("Your Masked Value in Hexadecimal is: ");
				printf("%hhX\n", maskedValue);
				printf("Your Masked Value in Binary is ");
				convertByteToBinary(maskedValue);
				printf("\n");
			}
			printf("\n");
			break;
		case 3:
			printf("Make A Word From Nibbles.\n");
			printf("Give Your High Byte:\n");
			scanf("%hhu", &highByte);
			printf("Give Your Low Byte:\n");
			scanf("%hhu", &lowByte);
			printf("Your High Byte in Hexadecimal is: ");
			printf("%hhX\n", highByte);
			printf("Your High Byte in Binary is ");
			convertByteToBinary(highByte);
			printf("Your Low Byte in Hexadecimal is: ");
			printf("%hhX\n", lowByte);
			printf("Your Low Byte in Binary is ");
			convertByteToBinary(lowByte);
			printf("\n");
			word = combineBytesToWord(lowByte, highByte);
			printf("Your Word in Decimal is: ");
			printf("%u\n", word);
			printf("Your Word in Hexadecimal is: ");
			printf("%X\n", word);
			printf("Your Word in Binary is ");
			convertWordToBinary(word);
			printf("\n");
			break;
		case 4:
			printf("Swap The Value's Nibbles.\n");
			printf("Give Your Input:\n");
			scanf("%hhu", &inputValue);
			swappedValue = swapNibblesInByte(inputValue);
			printf("Your Input in Hexadecimal is: ");
			printf("%hhX\n", inputValue);
			printf("Your Input in Binary is ");
			convertByteToBinary(inputValue);
			printf("\n");
			printf("Your Input after It Swapped is: ");
			printf("%hhu\n", swappedValue);
			printf("The Swapped Value in Hexadecimal is: ");
			printf("%hhX\n", swappedValue);
			printf("The Swapped Value in Binary is ");
			convertByteToBinary(swappedValue);
			printf("\n");
			break;
		case 5:
			printf("Is The Value Powered by 2?\n");
			printf("Give Your Input:\n");
			scanf("%hhu", &inputValue);
			printf("\n");
			printf("Your Input Value in Binary is ");
			convertByteToBinary(inputValue);
			printf("\n");
			if (isBytePowerOfTwo(inputValue) == true)
			{
				printf("%hhu is the power of two.\n", inputValue);
			}
			else
			{
				printf("%hhu is not the power of two.\n", inputValue);
			}
			printf("\n");
			break;
		case 6:
			printf("Toggle Value With Position.\n");
			printf("Give Your Input:\n");
			scanf("%hhu", &inputValue);
			printf("Your Input in Binary is ");
			convertByteToBinary(inputValue);
			printf("\n");
			printf("Give Your Desired Bit Position:\n");
			scanf("%hhu", &position);
			toggledValue = toggleBitInByte(inputValue, position);
			printf("Your Toggled bit by position %hhu is: ", position);
			printf("%hhu\n", toggledValue);
			printf("Your Toggled Result in Binary is ");
			convertByteToBinary(toggledValue);
			printf("\n");
			break;
		case 7:
			printf("Compare bits value with 2 inputs.\n");
			printf("Give Your First Value:\n");
			scanf("%hhu", &byteOne);
			printf("Give Your Second Value:\n");
			scanf("%hhu", &byteTwo);
			numberOfBits = compareBytes(byteOne, byteTwo);
			printf("Your First Byte in Binary is ");
			convertByteToBinary(byteOne);
			printf("Your Second Byte in Binary is ");
			convertByteToBinary(byteTwo);
			printf("\n");
			printf("From both values, you have %hhu number of bits.\n", numberOfBits);
			printf("\n");
			break;
		case 0:
			printf("Quit the Operator\n");
			return 0;
			break;
		default:
			printf("Sorry! %d is not one of the choices\n", choice);
			printf("\n");
			break;
		}
	}
	return (0);
}