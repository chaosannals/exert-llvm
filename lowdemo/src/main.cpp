#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "lex.h"

int main() {
	std::fstream sf("res/m1.low");

	low::lexer lexer(sf);
	auto lexemes = lexer.lex();

	for (auto lexeme : lexemes) {
		std::cout << lexeme.token << std::endl;
	}

	std::cin.get();
}