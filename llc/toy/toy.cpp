#include <string>

enum Token_Type {
    EOF_TOKEN = 0,
    NUMERIC_TOKEN,
    IDENTIFIER_TOKEN,
    PARAN_TOKEN,
    DEF_TOKEN
};

static int Numberic_Val;
static std::string Identifier_String;
static FILE *file;

static int get_token() {
    static int LastChar = ' ';
    while (isspace(LastChar)) {
        LastChar = fgetc(file);
    }
    if (isalpha(LastChar)) {
        Identifier_String = LastChar;
        while (isalnum((LastChar = fgetc(file)))) {
            Identifier_String += LastChar;
            if (Identifier_String == "def") {
                return DEF_TOKEN;
            }
            return IDENTIFIER_TOKEN;
        }
    }
    if (isdigit(LastChar)) {
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = fgetc(file);
        } while (isdigit(LastChar));

        Numberic_Val = strtod(NumStr.c_str(), 0);
        return NUMERIC_TOKEN;
    }
    if (LastChar == '#') {
        do {
            LastChar = fgetc(file);
        } while (LastChar != EOF &&
            LastChar != '\n' &&
            LastChar != '\r');
        if (LastChar != EOF) {
            return get_token();
        }
    }
    if (LastChar == EOF) {
        return EOF_TOKEN;
    }

    int ThisChar = LastChar;
    LastChar = fgetc(file);
    return ThisChar;
}