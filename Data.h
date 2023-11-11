#pragma once

#define MAX_TOKENS 1000
#define MAX_IDENTIFIER 10

// �������������, ��� ����� �� ������ ���� ������
enum TypeOfTokens
{
    Startprogram,   // Startprogram
    Int32,   		// Int32
    Startblok,      // Startblok 
    Endblok,		// Endblok 
    Scan,			// Scan
    Print,			// Print
    If,	    		// If
    Else,           // Else
    For,            // For--
    To,             // To--
    Do,
    Down,           // Down--
    While,          // While--
    Endwhile,       // Endwhile
    Repeat,         // Repeatuntil -- 
    Until,          // Repeatuntil --
    Goto,           // Goto



    Identifier,	    // Identifier

    Number,		    // Number

    Assign,		    // =>
    Add,			// ++
    Sub,			// --
    Mul,			// **
    Div,			// Div
    Mod,            // Mod

    Equality,		// Eq
    NotEquality,	// Neq
    Greate,		    // Gr
    Less,			// Ls
    Not,			// Not
    And,			// And
    Or,			    // Or

    LBraket,		// (
    RBraket,		// )
    Semicolon,		// ;
    Comma,			// ,
    Lcomment,       // {
    Rcomment,       // }
    Commentar,
    Unknown
};

// ��������� ��� ��������� ���������� ��� �������
struct Token
{
    char name[16];      // ��'� �������
    int value;          // �������� ������� (��� ����� ��������)
    int line;           // ����� �����
    int stan = 0;
    TypeOfTokens type;  // ��� �������
};

typedef  char Id[5];

// �������������, ��� ����� ����� ���������� ����������
enum States
{
    Start,      // ������� �������� ������� �������    
    Finish,     // ����� �������� ������� �������
    Letter,     // ����������� ��� (������ ����� � ��������������)
    Digit,      // ����������� �����
    Separators, // ��������� ������, ������� ��������� � �������� �� ����� �����
    Another,    // ����������� ����� �������
    Comments
};

// ������� ������ ������� � �������� ����� F � ������ �� � ������� ������ TokenTable 
// ��������� ������� - ������� ������
unsigned int GetTokens(FILE* F, Token TokenTable[]);

void PrintTokens(Token TokenTable[], unsigned int TokensNum);

void PrintTokensToFile(char* FileName, Token TokenTable[], unsigned int TokensNum);

void PrintWarningToFile(char* FileName, Token TokenTable[], unsigned int TokensNum);

