#pragma once

#define MAX_TOKENS 1000
#define MAX_IDENTIFIER 10

// перерахування, яке описує всі можливі типи лексем
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

// структура для зберігання інформації про лексему
struct Token
{
    char name[16];      // ім'я лексеми
    int value;          // значення лексеми (для цілих констант)
    int line;           // номер рядка
    int stan = 0;
    TypeOfTokens type;  // тип лексеми
};

typedef  char Id[5];

// перерахування, яке описує стани лексичного аналізатора
enum States
{
    Start,      // початок виділення чергової лексеми    
    Finish,     // кінець виділення чергової лексеми
    Letter,     // опрацювання слів (ключові слова і ідентифікатори)
    Digit,      // опрацювання цифри
    Separators, // видалення пробілів, символів табуляції і переходу на новий рядок
    Another,    // опрацювання інших символів
    Comments
};

// функція отримує лексеми з вхідного файлу F і записує їх у таблицю лексем TokenTable 
// результат функції - кількість лексем
unsigned int GetTokens(FILE* F, Token TokenTable[]);

void PrintTokens(Token TokenTable[], unsigned int TokensNum);

void PrintTokensToFile(char* FileName, Token TokenTable[], unsigned int TokensNum);

void PrintWarningToFile(char* FileName, Token TokenTable[], unsigned int TokensNum);

