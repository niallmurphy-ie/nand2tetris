#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cinstruction.h"
#include "ainstruction.h"
#include "symbols.h"

int readFile(char *fileName);
void removeComments(char *line);
void assemble(char *fileName);

// main function with one file argument
int main(int argc, char *argv[])
{
	// check if there is one file argument
	if (argc != 2)
	{
		printf("Usage: %s <file>\n", argv[0]);
		return 1;
	}
	char *fileName = strtok(argv[1], ".");
	// Create temp file with formatted asm code
	if (readFile(fileName) != 0)
	{
		printf("Error reading file\n");
		return 1;
	}
	// Add symbols to temp file's code and create symbols.txt file
	createSymbols();
	// Create hack file from symbols.txt file
	assemble(fileName);
	// Clean up
	remove("temp.txt");
	remove("symbols.txt");
}

void assemble(char *fileName)
{
	FILE *hack = fopen(strcat(fileName, ".hack"), "w");
	FILE *temp = fopen("symbols.txt", "r");
	printf("Assembling...\n");
	char line[100];
	while (fgets(line, 100, temp) != NULL)
	{
		if (line[0] == '@')
		{
			ainstruction(line, hack);
		}
		else
		{
			cinstruction(line, hack);
		}
	}
	// close files
	fclose(temp);
	fclose(hack);
}

// function to read file
int readFile(char *fileName)
{
	// copy fileName
	char *tempName = malloc(strlen(fileName));
	strcpy(tempName, fileName);
	FILE *file = fopen(strcat(tempName, ".asm"), "r");
	free(tempName);
	// check file exists
	if (file == NULL)
	{
		printf("File %s not found\n");
		return 1;
	}
	// create temporary file to write stripped lines to to
	FILE *temp = fopen("temp.txt", "w");
	char line[100];
	while (fgets(line, 100, file) != NULL)
	{
		// Strip whitespace and comments
		removeComments(line);
		// if line is not null or blank, write to temp file
		if (strlen(line) > 0)
		{
			fprintf(temp, "%s\n", line);
		}
	}
	// close files
	fclose(file);
	fclose(temp);
	return 0;
}

// remove comments that start with "//" and whitespace from each line
void removeComments(char *line)
{
	char newLine[100];
	int charNumber = 0;
	// remove whitespace
	for (int i = 0; i < strlen(line); i++)
	{
		if (line[i] != ' ' && line[i] != '\n')
		{
			newLine[charNumber] = line[i];
			charNumber++;
		}
	}
	newLine[charNumber] = '\0';
	// remove comments
	char *comment = strstr(newLine, "//");
	if (comment != NULL)
	{
		*comment = '\0';
	}
	// replace line with new line
	strcpy(line, newLine);
}
