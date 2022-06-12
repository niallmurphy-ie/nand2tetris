#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void readFile(FILE *file, FILE *temp);
void removeComments(char *line);
void assemble(FILE *temp, FILE *hack);
char *decimalToBinary(char *decimal);
char *leftPad(char *binary);
int dest(char *line, char *binary);
void comp(char *line, char *binary);
void jump(char *line, char *binary);
void ainstruction(char *line, FILE *hack);
void cinstruction(char *line, FILE *hack);

// main function with one file argument
int main(int argc, char *argv[])
{
	// check if there is one file argument
	if (argc != 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return 1;
	}
	// open file
	FILE *file = fopen(argv[1], "r");
	// check file exists
	if (file == NULL)
	{
		printf("File %s not found\n", argv[1]);
		return 1;
	}
	// create temporary file to write stripped lines to to
	FILE *temp = fopen("temp.txt", "w");
	// create temp file that can be worked on.
	readFile(file, temp);
	fclose(file);
	fclose(temp);
	// create new .hack file to write to with same name as argument filename while removing .asm
	FILE *hack = fopen(strcat(strtok(argv[1], "."), ".hack"), "w");
	// send temp and hack to function to translate to binary code
	// reopen temp so reading works
	temp = fopen("temp.txt", "r");
	assemble(temp, hack);
	// close files
	fclose(temp);
	fclose(hack);
}

void assemble(FILE *temp, FILE *hack)
{
	printf("Assembling...\n");
	// read line from temp file
	char line[100];
	// line isn't empty
	while (fgets(line, 100, temp) != NULL)
	{
		printf("%s", line);
		// if first character is @
		if (line[0] == '@')
		{
			ainstruction(line, hack);
		}
		else
		{
			cinstruction(line, hack);
		}
	}
}

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

void ainstruction(char *line, FILE *hack)
{
	// get rest of line
	char *rest = line + 1;
	// convert to binary and leftpad rest of line to 15 characters
	char *binary = decimalToBinary(rest);
	char *leftpad = leftPad(binary);
	free(binary);
	// // write leftpad to hack file
	fprintf(hack, "%s\n", leftpad);
	free(leftpad);
}

// leftpad binary with 0s to 16 characters
char *leftPad(char *binary)
{
	printf("Binary - %s\n", binary);
	// create new string of 16 length to hold padded binary
	char *paddedBinary = malloc(17);
	// get length of binary
	int length = strlen(binary);
	printf("Length: %d\n", length);
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
	// add null terminator
	paddedBinary[16] = '\0';
	return paddedBinary;
}

// decimalToBinary
char *decimalToBinary(char *decimal)
{
	// convert decimal to int k
	int k = atoi(decimal);
	char *buffer = malloc(16);
	itoa(k, buffer, 2);
	printf("%s\n", buffer);
	return buffer;
}

// function to read file
void readFile(FILE *file, FILE *temp)
{
	// read line by line
	char line[100];
	while (fgets(line, 100, file) != NULL)
	{
		// remove comments
		removeComments(line);
		// if line is not null or blank, write to temp file
		if (strlen(line) > 1)
		{
			fprintf(temp, "%s", line);
		}
	}
}

// remove comments that start with "//" and whitespace from each line
void removeComments(char *line)
{
	// remove comments
	char *comment = strstr(line, "//");
	if (comment != NULL)
	{
		*comment = '\0';
	}
	// remove whitespace
	char *whitespace = strstr(line, " ");
	if (whitespace != NULL)
	{
		*whitespace = '\0';
	}
}
