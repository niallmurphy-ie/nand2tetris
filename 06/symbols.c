#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbols.h"

void predefinedSymbols();
void readFileSymbols();
void insertSymbols();
void parseAndInsert(char *line, FILE *withSymbols);
char isNumber(char *text);

// array of structs with symbol and value
struct symbol
{
	char *name;
	int value;
};
struct symbol symbols[50000];

int memoryLocation = 16;
int symbolsCount = 0;

void createSymbols()
{
	predefinedSymbols();
	readFileSymbols();
	insertSymbols();
}

void insertSymbols()
{
	// open file
	FILE *file = fopen("temp.txt", "r");
	FILE *withSymbols = fopen("symbols.txt", "w");
	// read line from temp file
	char line[100];
	// line isn't empty
	while (fgets(line, 100, file) != NULL)
	{
		if (line[0] == '@')
		{
			parseAndInsert(line, withSymbols);
		}
		else if (line[0] != '(')
		{
			fprintf(withSymbols, "%s", line);
		}
	}
	fclose(file);
	fclose(withSymbols);
}

void parseAndInsert(char *line, FILE *withSymbols)
{
	// Check if everything after @ is a valid integer
	// remove \n from name
	char *sname = strtok(line, "\n");
	if (isNumber(sname + 1) != 0)
	{
		fprintf(withSymbols, "%s\n", line);
		return;
	}
	for (int i = 0; i < symbolsCount; i++)
	{
		if (strcmp(sname, symbols[i].name) == 0)
		{
			fprintf(withSymbols, "@%d\n", symbols[i].value);
			return;
		}
	}
	// if symbol is not in symbols array, add to array
	char *name = malloc(strlen(sname));
	strcpy(name, sname);
	name[strlen(name)] = '\0';
	// add symbol to array
	symbols[symbolsCount].name = name;
	symbols[symbolsCount].value = memoryLocation;
	fprintf(withSymbols, "@%d\n", memoryLocation);
	memoryLocation++;
	symbolsCount++;
	return;
}

void readFileSymbols()
{
	// open file
	FILE *file = fopen("temp.txt", "r");
	// check file exists
	if (file == NULL)
	{
		printf("File temp.txt not found\n");
		return;
	}
	// Find all occurances of symbols in file
	char line[100];
	int lineNumber = 0;
	while (fgets(line, 100, file) != NULL)
	{
		// if first character is @
		if (line[0] == '(')
		{
			// add symbol in between "(" and ")" to symbols array
			// find index of ) character in line
			int index = 0;
			while (line[index] != ')')
			{
				index++;
			}
			char *symbolName = malloc(index + 1);
			strncpy(symbolName, line, index);
			symbolName[index] = '\0';
			symbolName[0] = '@'; // Replace ( with @
			symbols[symbolsCount].name = symbolName;
			symbols[symbolsCount].value = lineNumber;
			symbolsCount++;
			lineNumber--; // Will be removed when symbols substituted in.
		}
		lineNumber++;
	}
	fclose(file);
}

void predefinedSymbols()
{
	symbols[symbolsCount].name = "@R0";
	symbols[symbolsCount].value = 0;
	symbolsCount++;
	symbols[symbolsCount].name = "@R1";
	symbols[symbolsCount].value = 1;
	symbolsCount++;
	symbols[symbolsCount].name = "@R2";
	symbols[symbolsCount].value = 2;
	symbolsCount++;
	symbols[symbolsCount].name = "@R3";
	symbols[symbolsCount].value = 3;
	symbolsCount++;
	symbols[symbolsCount].name = "@R4";
	symbols[symbolsCount].value = 4;
	symbolsCount++;
	symbols[symbolsCount].name = "@R5";
	symbols[symbolsCount].value = 5;
	symbolsCount++;
	symbols[symbolsCount].name = "@R6";
	symbols[symbolsCount].value = 6;
	symbolsCount++;
	symbols[symbolsCount].name = "@R7";
	symbols[symbolsCount].value = 7;
	symbolsCount++;
	symbols[symbolsCount].name = "@R8";
	symbols[symbolsCount].value = 8;
	symbolsCount++;
	symbols[symbolsCount].name = "@R9";
	symbols[symbolsCount].value = 9;
	symbolsCount++;
	symbols[symbolsCount].name = "@R10";
	symbols[symbolsCount].value = 10;
	symbolsCount++;
	symbols[symbolsCount].name = "@R11";
	symbols[symbolsCount].value = 11;
	symbolsCount++;
	symbols[symbolsCount].name = "@R12";
	symbols[symbolsCount].value = 12;
	symbolsCount++;
	symbols[symbolsCount].name = "@R13";
	symbols[symbolsCount].value = 13;
	symbolsCount++;
	symbols[symbolsCount].name = "@R14";
	symbols[symbolsCount].value = 14;
	symbolsCount++;
	symbols[symbolsCount].name = "@R15";
	symbols[symbolsCount].value = 15;
	symbolsCount++;

	symbols[symbolsCount].name = "@SCREEN";
	symbols[symbolsCount].value = 16384;
	symbolsCount++;
	symbols[symbolsCount].name = "@KBD";
	symbols[symbolsCount].value = 24576;
	symbolsCount++;
	symbols[symbolsCount].name = "@SP";
	symbols[symbolsCount].value = 0;
	symbolsCount++;
	symbols[symbolsCount].name = "@LCL";
	symbols[symbolsCount].value = 1;
	symbolsCount++;
	symbols[symbolsCount].name = "@ARG";
	symbols[symbolsCount].value = 2;
	symbolsCount++;
	symbols[symbolsCount].name = "@THIS";
	symbols[symbolsCount].value = 3;
	symbolsCount++;
	symbols[symbolsCount].name = "@THAT";
	symbols[symbolsCount].value = 4;
	symbolsCount++;
}

char isNumber(char *text)
{
	int j;
	j = strlen(text);
	while (j--)
	{
		if (text[j] > 47 && text[j] < 58)
			continue;

		return 0;
	}
	return 1;
}