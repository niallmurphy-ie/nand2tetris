#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cinstruction.h"

int dest(char *line, char *binary);
void comp(char *line, char *binary);
void jump(char *line, char *binary);

void cinstruction(char *line, FILE *hack)
{
	// create binary string that is 16 characters long
	char *binary = malloc(17);
	for (int i = 0; i < 16; i++)
	{
		if (i < 3)
		{
			binary[i] = '1';
		}
		else
		{
			binary[i] = '0';
		}
	}
	printf("BINARY TO START WITH: %s\n", binary);
	// modify binary directly and return how many characters should be removed before comp
	int removeDest = dest(line, binary);
	// removeDest characters before comp
	comp(line + removeDest, binary);
	jump(line, binary);
	binary[16] = '\0';
	fprintf(hack, "%s\n", binary);
}

void jump(char *line, char *binary)
{
	if (strstr(line, ";JGT") != NULL)
	{
		binary[13] = '0';
		binary[14] = '0';
		binary[15] = '1';
	}
	else if (strstr(line, ";JEQ") != NULL)
	{
		binary[13] = '0';
		binary[14] = '1';
		binary[15] = '0';
	}
	else if (strstr(line, ";JGE") != NULL)
	{
		binary[13] = '0';
		binary[14] = '1';
		binary[15] = '1';
	}
	else if (strstr(line, ";JLT") != NULL)
	{
		binary[13] = '1';
		binary[14] = '0';
		binary[15] = '0';
	}
	else if (strstr(line, ";JNE") != NULL)
	{
		binary[13] = '1';
		binary[14] = '0';
		binary[15] = '1';
	}
	else if (strstr(line, ";JLE") != NULL)
	{
		binary[13] = '1';
		binary[14] = '1';
		binary[15] = '0';
	}
	else if (strstr(line, ";JMP") != NULL)
	{
		binary[13] = '1';
		binary[14] = '1';
		binary[15] = '1';
	}
}

void comp(char *line, char *binary)
{
	// Do long a=0 first
	if (strstr(line, "D|A") != NULL)
	{
		binary[4] = '0';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '1';
		binary[8] = '0';
		binary[9] = '1';
	}
	else if (strstr(line, "D&A") != NULL)
	{
		binary[4] = '0';
		binary[5] = '0';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '0';
		binary[9] = '0';
	}
	else if (strstr(line, "A-D") != NULL)
	{
		binary[4] = '0';
		binary[5] = '0';
		binary[6] = '0';
		binary[7] = '1';
		binary[8] = '1';
		binary[9] = '1';
	}
	else if (strstr(line, "D-A") != NULL)
	{
		binary[4] = '0';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '1';
		binary[9] = '1';
	}
	else if (strstr(line, "D+A") != NULL)
	{
		binary[4] = '0';
		binary[5] = '0';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '1';
		binary[9] = '0';
	}
	else if (strstr(line, "A-1") != NULL)
	{
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '1';
		binary[9] = '0';
	}
	else if (strstr(line, "D-1") != NULL)
	{
		binary[4] = '0';
		binary[5] = '0';
		binary[6] = '1';
		binary[7] = '1';
		binary[8] = '1';
		binary[9] = '0';
	}
	else if (strstr(line, "A+1") != NULL)
	{
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '1';
		binary[8] = '1';
		binary[9] = '1';
	}
	else if (strstr(line, "D+1") != NULL)
	{
		binary[4] = '0';
		binary[5] = '1';
		binary[6] = '1';
		binary[7] = '1';
		binary[8] = '1';
		binary[9] = '1';
	}
	// a=1 instructions
	else if (strstr(line, "D|M") != NULL)
	{
		binary[3] = '1';
		binary[4] = '0';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '1';
		binary[8] = '0';
		binary[9] = '1';
	}
	else if (strstr(line, "D&M") != NULL)
	{
		binary[3] = '1';
		binary[4] = '0';
		binary[5] = '0';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '0';
		binary[9] = '0';
	}
	else if (strstr(line, "M-D") != NULL)
	{
		binary[3] = '1';
		binary[4] = '0';
		binary[5] = '0';
		binary[6] = '0';
		binary[7] = '1';
		binary[8] = '1';
		binary[9] = '1';
	}
	else if (strstr(line, "D-M") != NULL)
	{
		binary[3] = '1';
		binary[4] = '0';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '1';
		binary[9] = '1';
	}
	else if (strstr(line, "D+M") != NULL)
	{
		binary[3] = '1';
		binary[4] = '0';
		binary[5] = '0';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '1';
		binary[9] = '0';
	}
	else if (strstr(line, "M-1") != NULL)
	{
		binary[3] = '1';
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '1';
		binary[9] = '0';
	}
	else if (strstr(line, "M+1") != NULL)
	{
		binary[3] = '1';
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '1';
		binary[8] = '1';
		binary[9] = '1';
	}
	else if (strstr(line, "-M") != NULL)
	{
		binary[3] = '1';
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '1';
		binary[9] = '1';
	}
	else if (strstr(line, "!M") != NULL)
	{
		binary[3] = '1';
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '0';
		binary[9] = '1';
	}
	else if (line[0] == 'M') // Special because of JMP
	{
		binary[3] = '1';
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '0';
		binary[9] = '0';
	}
	// Back to a=0 for the rest of the instructions
	else if (strstr(line, "-A") != NULL)
	{
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '0';
		binary[9] = '1';
	}
	else if (strstr(line, "-D") != NULL)
	{
		binary[4] = '0';
		binary[5] = '0';
		binary[6] = '1';
		binary[7] = '1';
		binary[8] = '1';
		binary[9] = '1';
	}
	else if (strstr(line, "!A") != NULL)
	{
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '0';
		binary[9] = '1';
	}
	else if (strstr(line, "!D") != NULL)
	{
		binary[4] = '0';
		binary[5] = '0';
		binary[6] = '1';
		binary[7] = '1';
		binary[8] = '0';
		binary[9] = '1';
	}
	else if (strstr(line, "A") != NULL)
	{
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '0';
		binary[7] = '0';
		binary[8] = '0';
		binary[9] = '0';
	}
	else if (strstr(line, "D") != NULL)
	{
		binary[4] = '0';
		binary[5] = '0';
		binary[6] = '1';
		binary[7] = '1';
		binary[8] = '0';
		binary[9] = '0';
	}
	else if (strstr(line, "-1") != NULL)
	{
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '1';
		binary[7] = '0';
		binary[8] = '1';
		binary[9] = '0';
	}
	else if (strstr(line, "1") != NULL)
	{
		binary[4] = '1';
		binary[5] = '1';
		binary[6] = '1';
		binary[7] = '1';
		binary[8] = '1';
		binary[9] = '1';
	}
	else if (strstr(line, "0") != NULL)
	{
		binary[4] = '1';
		binary[5] = '0';
		binary[6] = '1';
		binary[7] = '0';
		binary[8] = '1';
		binary[9] = '0';
	}
}

int dest(char *line, char *binary)
{
	int remove = 0;
	// if line contains AMD=
	if (strstr(line, "AMD=") != NULL)
	{
		binary[10] = '1';
		binary[11] = '1';
		binary[12] = '1';
		remove = 4;
	}
	else if (strstr(line, "MD=") != NULL)
	{
		binary[10] = '0';
		binary[11] = '1';
		binary[12] = '1';
		remove = 3;
	}
	else if (strstr(line, "AM=") != NULL)
	{
		binary[10] = '1';
		binary[11] = '0';
		binary[12] = '1';
		remove = 3;
	}
	else if (strstr(line, "AD=") != NULL)
	{
		binary[10] = '1';
		binary[11] = '1';
		binary[12] = '0';
		remove = 3;
	}
	else if (strstr(line, "M=") != NULL)
	{
		binary[10] = '0';
		binary[11] = '0';
		binary[12] = '1';
		remove = 2;
	}
	else if (strstr(line, "D=") != NULL)
	{
		binary[10] = '0';
		binary[11] = '1';
		binary[12] = '0';
		remove = 2;
	}
	else if (strstr(line, "A=") != NULL)
	{
		binary[10] = '1';
		binary[11] = '0';
		binary[12] = '0';
		remove = 2;
	}
	else
	{
		binary[10] = '0';
		binary[11] = '0';
		binary[12] = '0';
	}
	return remove;
}