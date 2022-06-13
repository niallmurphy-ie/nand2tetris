#include <stdio.h>
#include "ainstruction.h"
#include <string.h>
#include <stdlib.h>

char *decimalToBinary(char *decimal);
char *leftPad(char *binary);

void ainstruction(char *line, FILE *hack)
{
	// get rest of line
	char *rest = line + 1;
	// convert to binary and leftpad rest of line to 15 characters
	char *binary = decimalToBinary(rest);
	char *leftpad = leftPad(binary);
	free(binary);
	fprintf(hack, "%s\n", leftpad);
	free(leftpad);
}

char *leftPad(char *binary)
{
	// create new string of 16 length to hold padded binary
	char *paddedBinary = malloc(17);
	// get length of binary
	int length = strlen(binary);
	// convert char *binary to 16 digits starting with 0s
	int j = 0;
	for (int i = 0; i < 16; i++)
	{
		if (i < 16 - length)
		{
			paddedBinary[i] = '0';
		}
		else
		{
			paddedBinary[i] = binary[j];
			j++;
		}
	}
	paddedBinary[16] = '\0';
	return paddedBinary;
}

// decimalToBinary
char *decimalToBinary(char *decimal)
{
	int k = atoi(decimal);
	char *buffer = malloc(16);
	itoa(k, buffer, 2);
	return buffer;
}