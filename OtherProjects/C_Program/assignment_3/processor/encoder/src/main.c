#include <file_encoder.h>

//////////////////////////////////////////////////////////////////////
//<encoder_file>
//
// Course	    : C Programming (PRC)
// Assignment	: C Assignment 3 ADIDAS -Advanced Development for Internet where Data Arrives Safely.
// Date		    : 14-06-2022
// Student		: Farros Ramzy(3767353)
//
//////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	int fileEncoded = 0;

	if (argc < MIN_ARGUMENTS)
	{
		printf("Argument Status: Error\n");
		exit(EXIT_FAILURE);
	}

	printf("Executable file name: %s\n", argv[0]);
	printf("Input file name: %s\n", argv[1]);
	printf("Output file name: %s\n", argv[2]);
	printf("Number of arguments: %d\n", argc);
	printf("Argument Status: OK\n");

	uint8_t readCounter = 0;
	uint8_t encodeCounter = 0;

	fileEncoded = encodeFile(argv[1], argv[2], &readCounter, &encodeCounter);

	printf("Read: %d\n", readCounter);
	printf("Write: %d\n", encodeCounter);

	if (fileEncoded == 1)
	{
		printf("Encode Status: FAIL.\n");
		exit(EXIT_FAILURE);
	}

	printf("Encode Status: SUCCESS.\n");
	
	exit(EXIT_SUCCESS);
}