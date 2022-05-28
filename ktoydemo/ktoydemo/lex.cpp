#include "lex.h"
#include <string>

std::string IdentifierStr; // Filled in if tok_identifier
double NumVal;             // Filled in if tok_number

/// gettok - Return the next token from standard input.
int gettok() {
    static int LastChar = ' ';

    // Skip any whitespace.
    while (isspace(LastChar))
        LastChar = getchar();

    if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
        IdentifierStr = LastChar;
        while (isalnum((LastChar = getchar())))
            IdentifierStr += LastChar;

        if (IdentifierStr == "def")
            return tok_def;
        if (IdentifierStr == "extern")
            return tok_extern;
        return tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while (isdigit(LastChar) || LastChar == '.');

        NumVal = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }

    if (LastChar == '#') {
        // Comment until end of line.
        do
            LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return gettok();
    }

    // Check for end of file.  Don't eat the EOF.
    if (LastChar == EOF)
        return tok_eof;

    // Otherwise, just return the character as its ascii value.
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}

int ktoy::lexer::get_token(std::istream& input) {
    // Skip any whitespace.
    while (isspace(last_char))
        last_char = input.get();

    if (isalpha(last_char)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
        IdentifierStr = last_char;
        while (isalnum((last_char = input.get())))
            IdentifierStr += last_char;

        if (IdentifierStr == "def")
            return tok_def;
        if (IdentifierStr == "extern")
            return tok_extern;
        return tok_identifier;
    }

    if (isdigit(last_char) || last_char == '.') { // Number: [0-9.]+
        std::string NumStr;
        do {
            NumStr += last_char;
            last_char = input.get();
        } while (isdigit(last_char) || last_char == '.');

        NumVal = strtod(NumStr.c_str(), nullptr);
        return tok_number;
    }

    if (last_char == '#') {
        // Comment until end of line.
        do
            last_char = input.get();
        while (last_char != EOF && last_char != '\n' && last_char != '\r');

        if (last_char != EOF)
            return get_token(input);
    }

    // Check for end of file.  Don't eat the EOF.
    if (last_char == EOF)
        return tok_eof;

    // Otherwise, just return the character as its ascii value.
    int ThisChar = last_char;
    last_char = input.get();
    return ThisChar;
}