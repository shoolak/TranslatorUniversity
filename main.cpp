#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Data.h"


int main(int argc, char* argv[])
{
	// таблиц€ лесем
	//Token TokenTable[MAX_TOKENS];

	Token* TokenTable = new Token[MAX_TOKENS];

	// к≥льк≥сть лексем
	unsigned int TokensNum;
	// таблиц€ ≥дентиф≥катор≥в
	Id IdTable[MAX_IDENTIFIER];
	// к≥льк≥сть ≥дентиф≥катор≥в
	unsigned int IdNum;

	char InputFile[32] = "";
	FILE* InFile;

	printf("---------------------------------------------------------------------------\n");
	printf("|         TRANSLATOR ( M -> ASSEMBLER )                                   |\n");
	printf("---------------------------------------------------------------------------\n\n");


	if (argc != 2)
	{
		printf("Input file name: ");
		gets_s(InputFile);
	}
	else
	{
		strcpy_s(InputFile, argv[1]);
	}

	if ((fopen_s(&InFile, InputFile, "rt")) != 0)
	{
		printf("Error: Can not open file: %s\n", InputFile);
		return 1;
	}

	TokensNum = GetTokens(InFile, TokenTable);

	char TokenFile[32];
	char TokenFileW[32];
	

	int i = 0;
	while (InputFile[i] != '.')
	{
		TokenFile[i] = InputFile[i];
		i++;
	}
	TokenFile[i] = '\0';
	strcat_s(TokenFile, "Leksem.t18");
	PrintTokensToFile(TokenFile, TokenTable, TokensNum);
	fclose(InFile);
	int j = 0;
	while (InputFile[j] != '.')
	{
		TokenFileW[j] = InputFile[j];
		j++;
	}
	TokenFileW[j] = '\0';
	strcat_s(TokenFileW, "Warnings.t18");
	PrintWarningToFile(TokenFileW, TokenTable, TokensNum);
	fclose(InFile);
	
	printf("\nLexical analysis completed. List of tokens in the file %s\n", TokenFile);
	PrintTokens(TokenTable, TokensNum);

	delete[]TokenTable;
	return 0;
}