#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cinstruction.h"
#include "ainstruction.h"
#include "symbols.h"

void readFile(FILE *file, FILE *temp);
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
	char *fileName = strtok(argv[1], ".");
	// Symbols
	createSymbols();
	// Create hack file
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
void readFile(FILE *file, FILE *temp)
{
	// read line by line
	char line[100];
	while (fgets(line, 100, file) != NULL)
	{
		removeComments(line);
		// if line is not null or blank, write to temp file
		if (strlen(line) > 0)
		{
			fprintf(temp, "%s\n", line);
		}
	}
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
