#include <file_channeler.h>

//////////////////////////////////////////////////////////////////////
//<channeler_file>
//
// Course	    : C Programming (PRC)
// Assignment	: C Assignment 3 ADIDAS -Advanced Development for Internet where Data Arrives Safely.
// Date		    : 14-06-2022
// Student		: Farros Ramzy(3767353)
//
//////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	int runChannelFile = 0;

	if (argc < MIN_ARGUMENTS)
	{
		printf("Argument Status: Error\n");
		exit(EXIT_FAILURE);
	}

	printf("Executable file name: %s\n", argv[0]);
	printf("Input file name: %s\n", argv[1]);
	printf("Output file name: %s\n", argv[2]);
	printf("Number of arguments: %d\n", argc);

	uint8_t readCounter = 0;
	uint8_t transmitCounter = 0;

	srand((unsigned)time(NULL));
	runChannelFile = channelFile(argv[1], argv[2], &readCounter, &transmitCounter);

	printf("Read: %d\n", readCounter);
	printf("Transmitted: %d\n", transmitCounter);

	if (runChannelFile == 1)
	{
		printf("Transmit Status: FAIL.\n");
		exit(EXIT_FAILURE);
	}

	printf("Transmit Status: SUCCESS.\n");
	
	exit(EXIT_SUCCESS);
}