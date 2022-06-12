#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cinstruction.h"
#include "ainstruction.h"

void readFile(FILE *file, FILE *temp);
void removeComments(char *line);
void assemble(FILE *temp, FILE *hack);

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
