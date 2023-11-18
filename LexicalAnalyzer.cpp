#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include "Data.h"
#include <unordered_map>
#include <cstring>

using namespace std;


// функція отримує лексеми з вхідного файлу F і записує їх у таблицю лексем TokenTable 
// результат функції - кількість лексем

unsigned int GetTokens(FILE* F, Token TokenTable[])
{
	States state = Start;
	Token TempToken;
	// кількість лексем
	unsigned int NumberOfTokens = 0;
	char ch, buf[16];
	int line = 1;
	/////////////////////////

	std::unordered_map<std::string, TypeOfTokens> tokenLetterMap =
	{
		{"Commentar", Commentar},
		{ "Startprogram", Startprogram },
		{ "Int32", Int32 },
		{ "Startblok", Startblok },
		{ "Endblok", Endblok },
		{ "Scan", Scan },
		{ "Print", Print },
		{ "If", If },
		{ "Else", Else },
		{ "For", For },
		{ "To", To },
		{ "Do", Do },
		{ "Down", Down },
		{ "While", While },
		{ "Endwhile", Endwhile },
		{ "Repeat", Repeat },
		{ "Until", Until },
		{ "Goto", Goto },
		{ "Div", Div },
		{ "Mod", Mod },
		{ "Eq", Equality },
		{ "Neq", NotEquality },
		{ "Gr", Greate },
		{ "Ls", Less },
		{ "Not", Not },
		{ "And", And },
		{ "Or", Or },
		
	};
	std::unordered_map<std::string, TypeOfTokens> tokenAnotherMap =
	{
		{"=>", Assign},
		{"++", Add},
		{"--", Sub},
		{"**", Mul},
		{"(", LBraket},
		{")", RBraket},
		{";", Semicolon},
		{",", Comma},
		{"{", Lcomment},
		{"}", Rcomment},
	};
	/////////////////////////
	// читання символів з файлу і пошук лексем
	ch = getc(F);
	while (ch != EOF)
	{
		switch (state)
		{
		// початок виділення чергової лексеми 
		// якщо поточний символ маленька літера, то переходимо до стану Letter
		// якщо поточний символ цифра, то переходимо до стану Digit
		// якщо поточний символ пробіл, символ табуляції або переходу на новий рядок, то переходимо до стану Separators
		// якщо поточний символ відмінний від попередніх, то переходимо до стану Another
		case Start:
		{
			if (ch <= 'z' && ch >= 'a' || ch <= 'Z' && ch >= 'A')
				state = Letter;
			else
				if (ch <= '9' && ch >= '0')
					state = Digit;
				else
					if (ch == ' ' || ch == '\t' || ch == '\n')
						state = Separators;
					else
						state = Another;
							break;
		}
		case Finish:
		{
			if (NumberOfTokens < MAX_TOKENS)
			{
				TokenTable[NumberOfTokens++] = TempToken;
				ch = getc(F);
				state = Start;
			}
			else 
			{
				printf("\n\t\t\ttoo many tokens !!!\n");
				return NumberOfTokens - 1;
			}
			break;
		}
		case Letter:
		{
			buf[0] = ch;
			int j = 1;
			ch = getc(F);
			while (((ch <= 'z' && ch >= 'a')||( ch <= 'Z' && ch >= 'A') || (ch <= '9' && ch >= '0')) && j < 15)
			{
				buf[j++] = ch;
				ch = getc(F);
			}
			buf[j] = '\0';
			ungetc(ch, F);
			
			TypeOfTokens temp_type;
			if (TempToken.stan == 1)
			{
				temp_type = Commentar;
			}
			else if (tokenLetterMap.count(buf))
			{
				temp_type = tokenLetterMap[buf];
			}
			else
				temp_type = Unknown;

			strcpy_s(TempToken.name, buf);
			TempToken.type = temp_type;
			TempToken.value = 0;
			TempToken.line = line;
			state = Finish;
			break;
		}
		// поточний символ - цифра, поточна лексема - число
		case Digit:
		{
			buf[0] = ch;
			int j = 1;
			ch = getc(F);
			while (ch != '(' && ch != ')' && ch != '*' && ch != '+' && ch != ',' && ch != '-' &&
				ch != ';' && ch != '=' && ch != '>' && ch != '_' && ch != '{' && ch != '}' &&
				ch != ' ' && ch != '\n' && ch != '\t' && j < 15)
			{
				buf[j++] = ch;
				ch = getc(F);
			}
			buf[j] = '\0';
			ungetc(ch, F);

			strcpy_s(TempToken.name, buf);
			int temp = 0;
			for (int i = 0; i < buf[i] != '\0'; i++)
			{
				if (isdigit(buf[i])) {
					temp++;
				}
			}
			if (strlen(buf) == temp)
			{
				TempToken.type = Number;
				TempToken.value = atoi(buf);
			}
			else
			{
				TempToken.type = Unknown;
				TempToken.value = 0;
			}
			CheckComments(TempToken);
			TempToken.line = line;
			state = Finish;
			break;
		}
		// поточний символ пробіл, символ табуляції або переходу на новий рядок - видаляємо їх
		case Separators:
		{
			if (ch == '\n')
				line++;
			ch = getc(F);
			state = Start;
			break;
		}
		// поточний символ - символ, відмінний від попередніх
		case Another:
		{
			switch (ch)
			{
			case '(':
			{
				strcpy_s(TempToken.name, "(");
				TempToken.type = LBraket;
				TempToken.value = 0;
				CheckComments(TempToken);
				TempToken.line = line;
				state = Finish;
				break;
			}
			
			case  ')':
			{
				strcpy_s(TempToken.name, ")");
				TempToken.type = RBraket;
				TempToken.value = 0;
				CheckComments(TempToken);
				TempToken.line = line;
				state = Finish;
				break;
			}

			case ';':
			{
				strcpy_s(TempToken.name, ";");
				TempToken.type = Semicolon;
				TempToken.value = 0;
				CheckComments(TempToken);
				TempToken.line = line;
				state = Finish;
				break;
			}
			case  ',':
			{
				strcpy_s(TempToken.name, ",");
				TempToken.type = Comma;
				TempToken.value = 0;
				if (TempToken.stan == 1)
				CheckComments(TempToken);
				TempToken.line = line;
				state = Finish;
				break;
			}
			case  '{':
			{
				strcpy_s(TempToken.name, "{");
				TempToken.type = Lcomment;
				TempToken.value = 0;

				TempToken.line = line;
				TempToken.stan = 1;
				state = Finish;
				break;
			}
			case  '}':
			{
				strcpy_s(TempToken.name, "}");
				TempToken.type = Rcomment;
				TempToken.value = 0;
				TempToken.line = line;
				TempToken.stan = 0;
				state = Finish;
				break;
			}
			 //арифм вирази
			case  '*':
			{
				
				ch = getc(F);
				if (ch == '*')
				{
					
					strcpy_s(TempToken.name, "**");
					TempToken.type = Mul;
					TempToken.value = 0;
					CheckComments(TempToken);
					TempToken.line = line;
					state = Finish;
					break;
				}
				else
				{
					strcpy_s(TempToken.name, "*");
					TempToken.type = Unknown;
					TempToken.value = 0;
					CheckComments(TempToken);
					TempToken.line = line;
					state = Finish;
					break;
				}
				
			}
		
			case '+':
			{
				
				ch = getc(F);
				if (ch == '+')
				{
					strcpy_s(TempToken.name, "++");
					TempToken.type = Add;
					TempToken.value = 0;
					CheckComments(TempToken);
					TempToken.line = line;
					state = Finish;

					break;
				}
				else
				{
					strcpy_s(TempToken.name, "+");
					TempToken.type = Unknown;
					TempToken.value = 0;
					CheckComments(TempToken);
					TempToken.line = line;
					state = Finish;
					break;
				}
				
			}
			
			case '-':
			{
				
				ch = getc(F);

				if (ch >= '0' && ch <= '9')
				{
					sprintf_s(TempToken.name, "-%c", ch);
					TempToken.type = Number;
					TempToken.value = stoi(TempToken.name);
					CheckComments(TempToken);
					TempToken.line = line;
					state = Finish;
					break;
				}
				if (ch == '-')
				{
					strcpy_s(TempToken.name, "--");
					TempToken.type = Sub;
					TempToken.value = 0;
					CheckComments(TempToken);
					TempToken.line = line;
					state = Finish;
					break;

				}
				else
				{
					strcpy_s(TempToken.name, "-");
					TempToken.type = Unknown;
					TempToken.value = 0;
					CheckComments(TempToken);
					TempToken.line = line;
					state = Finish;
					break;
				}
				
			}

			case '=':
			{
				
				ch = getc(F);
				if (ch == '>')
				{

					strcpy_s(TempToken.name, "=>");
					TempToken.type = Assign;
					TempToken.value = 0;
					CheckComments(TempToken);
					TempToken.line = line;
					state = Finish;
					break;
				}
				else
				{
					strcpy_s(TempToken.name, "+");
					TempToken.type = Unknown;
					TempToken.value = 0;
					CheckComments(TempToken);
					TempToken.line = line;
					state = Finish;
					break;
					
				}
			}
			case '_':
			{
				buf[0] = '_';
				int j = 1;
				ch = getc(F);
				if (ch >= 'a' && ch <= 'z')
				{
					while ((ch != ' ' && ch != '\t' && ch != '\n') && (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z'))
					{
						buf[j++] = ch;
						ch = getc(F);
					}
					buf[j] = '\0';
					ungetc(ch, F);
					if (strlen(buf) <= 2)
					{


						strcpy_s(TempToken.name, buf);
						TempToken.type = Identifier;
						TempToken.value = 0;
						CheckComments(TempToken);
						TempToken.line = line;
						state = Finish;
						break;
					}
					else
					{
						strcpy_s(TempToken.name, buf);
						TempToken.type = Unknown;
						TempToken.value = 0;
						CheckComments(TempToken);
						TempToken.line = line;
						state = Finish;
						break;
					}
					
				}
				else
				{
					strcpy_s(TempToken.name, "_");
					TempToken.type = Unknown;
					TempToken.value = 0;
					CheckComments(TempToken);
					TempToken.line = line;
					state = Finish;
					break;
				}
				break;
			}
			default:
			{
				TempToken.name[0] = ch;
				TempToken.name[1] = '\0';
				TempToken.type = Unknown;
				TempToken.value = 0;
				CheckComments(TempToken);
				TempToken.line = line;
				state = Finish;
				break;
			}
			}
		}
		}
	}
	return NumberOfTokens;
}
void CheckComments(Token& TempToken)
{
	if (TempToken.stan == 1)
	{
		TempToken.type = Commentar;
		TempToken.value = 0;
	}
}
void PrintTokens(Token TokenTable[], unsigned int TokensNum)
{
	char type_tokens[16];
	printf("\n\n--------------------------------------------------------------------------------------\n");
	printf("|             TOKEN TABLE                                                            |\n");
	printf("--------------------------------------------------------------------------------------\n");
	printf("| line number |      token      |    stan    |    Value   | token code | type of token |\n");
	printf("-------------------------------------------------------------------------------------");
	for (unsigned int i = 0; i < TokensNum; i++)
	{
		switch (TokenTable[i].type)
		{
		case Startprogram: 
			strcpy_s(type_tokens, "Startprogram"); 
			break;
		case Int32:
			strcpy_s(type_tokens, "Int32"); 
			break;
		case Startblok:
			strcpy_s(type_tokens, "Startblok"); 
			break;
		case Endblok: 
			strcpy_s(type_tokens, "Endblok"); 
			break;
		case Scan:
			strcpy_s(type_tokens, "Scan"); 
			break;
		case Print:
			strcpy_s(type_tokens, "Print"); 
			break;
		case If: 
			strcpy_s(type_tokens, "If"); 
			break;
		case Else: 
			strcpy_s(type_tokens, "Else"); 
			break;
		case For:
			strcpy_s(type_tokens, "For");
			break;
		case Down:
			strcpy_s(type_tokens, "Down");
			break;
		case To:
			strcpy_s(type_tokens, "To");
			break;
		case Do:
			strcpy_s(type_tokens, "Do");
			break;
		case While:
			strcpy_s(type_tokens, "While");
			break;
		case Endwhile:
			strcpy_s(type_tokens, "Endwhile");
			break;
		case Repeat:
			strcpy_s(type_tokens, "Repeat");
			break;
		case Until:
			strcpy_s(type_tokens, "Until");
			break;
		case Goto:
			strcpy_s(type_tokens, "Goto");
			break;
		case Assign: 
			strcpy_s(type_tokens, "Assign"); 
			break;
		case Add: 
			strcpy_s(type_tokens, "Add"); 
			break;
		case Sub: 
			strcpy_s(type_tokens, "Sub"); 
			break;
		case Mul: 
			strcpy_s(type_tokens, "Mul"); 
			break;
		case Div: 
			strcpy_s(type_tokens, "Div"); 
			break;
		case Mod:
			strcpy_s(type_tokens, "Mod");
			break;
		case Equality: 
			strcpy_s(type_tokens, "Equality"); 
			break;
		case NotEquality: 
			strcpy_s(type_tokens, "NotEquality"); 
			break;
		case Greate: 
			strcpy_s(type_tokens, "Greater"); 
			break;
		case Less: 
			strcpy_s(type_tokens, "Less"); 
			break;
		case Not: 
			strcpy_s(type_tokens, "Not"); 
			break;
		case And: 
			strcpy_s(type_tokens, "And"); 
			break;
		case Or: 
			strcpy_s(type_tokens, "Or"); 
			break;
		case LBraket: 
			strcpy_s(type_tokens, "LBraket"); 
			break;
		case RBraket: 
			strcpy_s(type_tokens, "RBraket"); 
			break;
		case Number: 
			strcpy_s(type_tokens, "Number"); 
			break;
		case Semicolon:
			strcpy_s(type_tokens, "Semicolon"); 
			break;
		case Lcomment:
			strcpy_s(type_tokens, "Lcomment");
			break;
		case Rcomment:
			strcpy_s(type_tokens, "Rcomment");
			break;
		case Comma: 
			strcpy_s(type_tokens, "Comma"); 
			break;
		case Commentar:
			strcpy_s(type_tokens, "Commentar");
			break;
		case Identifier:
			strcpy_s(type_tokens, "Identifier");
			break;
		case Unknown: 
			strcpy_s(type_tokens, "Unknown"); 
			break;
		}
		
		printf("\n|%12d |%16s |%11d |%11d |%11d | %-13s |\n", 
			TokenTable[i].line,
			TokenTable[i].name, 
			TokenTable[i].stan,
			TokenTable[i].value, 
			TokenTable[i].type, 
			type_tokens);
		printf("--------------------------------------------------------------------------------------");
	}
}
void PrintWarningToFile(char* FileName, Token TokenTable[], unsigned int TokensNum)
{
	FILE* F;
	if ((fopen_s(&F, FileName, "wt")) != 0)
	{
		printf("Error: Can not create file: %s\n", FileName);
		return;
	}
		for (unsigned int i = 0; i < TokensNum; i++)
		{
			if (TokenTable[i].type == Unknown)
			{
				fprintf(F,"In %d line Unknown Leksem\n",TokenTable[i].line);
			}
		}
	
}
void PrintTokensToFile(char* FileName, Token TokenTable[], unsigned int TokensNum)
{
	FILE* F;
	if ((fopen_s(&F, FileName, "wt")) != 0)
	{
		printf("Error: Can not create file: %s\n", FileName);
		return;
	}
	char type_tokens[16];
	fprintf(F, "--------------------------------------------------------------------------------------\n");
	fprintf(F, "|             TOKEN TABLE                                                            |\n");
	fprintf(F, "--------------------------------------------------------------------------------------\n");
	fprintf(F, "| line number |      token      |    stan    |    value   | token code | type of token |\n");
	fprintf(F, "--------------------------------------------------------------------------------------");
	for (unsigned int i = 0; i < TokensNum; i++)
	{
		switch (TokenTable[i].type)
		{
		case Startprogram:
			strcpy_s(type_tokens, "Startprogram");
			break;
		case Int32:
			strcpy_s(type_tokens, "Int32");
			break;
		case Startblok:
			strcpy_s(type_tokens, "Startblok");
			break;
		case Endblok:
			strcpy_s(type_tokens, "Endblok");
			break;
		case Scan:
			strcpy_s(type_tokens, "Scan");
			break;
		case Print:
			strcpy_s(type_tokens, "Print");
			break;
		case If:
			strcpy_s(type_tokens, "If");
			break;
		case Else:
			strcpy_s(type_tokens, "Else");
			break;
		case For:
			strcpy_s(type_tokens, "For");
			break;
		case Down:
			strcpy_s(type_tokens, "Down");
			break;
		case To:
			strcpy_s(type_tokens, "To");
			break;
		case Do:
			strcpy_s(type_tokens, "Do");
			break;
		case While:
			strcpy_s(type_tokens, "While");
			break;
		case Endwhile:
			strcpy_s(type_tokens, "Endwhile");
			break;
		case Repeat:
			strcpy_s(type_tokens, "Repeat");
			break;
		case Until:
			strcpy_s(type_tokens, "Until");
			break;
		case Goto:
			strcpy_s(type_tokens, "Goto");
			break;
		case Assign:
			strcpy_s(type_tokens, "Assign");
			break;
		case Add:
			strcpy_s(type_tokens, "Add");
			break;
		case Sub:
			strcpy_s(type_tokens, "Sub");
			break;
		case Mul:
			strcpy_s(type_tokens, "Mul");
			break;
		case Div:
			strcpy_s(type_tokens, "Div");
			break;
		case Mod:
			strcpy_s(type_tokens, "Mod");
			break;
		case Equality:
			strcpy_s(type_tokens, "Equality");
			break;
		case NotEquality:
			strcpy_s(type_tokens, "NotEquality");
			break;
		case Greate:
			strcpy_s(type_tokens, "Greater");
			break;
		case Less:
			strcpy_s(type_tokens, "Less");
			break;
		case Not:
			strcpy_s(type_tokens, "Not");
			break;
		case And:
			strcpy_s(type_tokens, "And");
			break;
		case Or:
			strcpy_s(type_tokens, "Or");
			break;
		case LBraket:
			strcpy_s(type_tokens, "LBraket");
			break;
		case RBraket:
			strcpy_s(type_tokens, "RBraket");
			break;
		case Number:
			strcpy_s(type_tokens, "Number");
			break;
		case Semicolon:
			strcpy_s(type_tokens, "Semicolon");
			break;
		case Lcomment:
			strcpy_s(type_tokens, "Lcomment");
			break;
		case Rcomment:
			strcpy_s(type_tokens, "Rcomment");
			break;
		case Comma:
			strcpy_s(type_tokens, "Comma");
			break;
		case Identifier:
			strcpy_s(type_tokens, "Identifier");
			break;
		case Unknown:
			strcpy_s(type_tokens, "Unknown");
			break;
		}

		fprintf(F, "\n|%12d |%16s |%11d |%11d |%11d | %-13s |\n",
			TokenTable[i].line,
			TokenTable[i].name,
			TokenTable[i].stan,
			TokenTable[i].value,
			TokenTable[i].type,
			type_tokens);
		fprintf(F, "--------------------------------------------------------------------------------------");
	}
	fclose(F);
}
void UnknowForAnother(Token& TempToken,int line,const char *element)
{

	strcpy_s(TempToken.name, element);
	TempToken.type = Unknown;
	TempToken.value = 0;
	CheckComments(TempToken);
	TempToken.line = line;
}
