#pragma once
#include <string>
#include <istream>

//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
    tok_eof = -1,

    // commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5
};

/// gettok - Return the next token from standard input.

int gettok();

namespace ktoy {

    class lexer {
        int last_char;
        double number_store;
        std::string identifier_store;
    public:
        int get_token(std::istream &input);
        double get_number() { return number_store; }
        const std::string& get_identifier() { return identifier_store; }
    };
}