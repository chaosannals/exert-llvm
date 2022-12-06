#include "lex.h"

using namespace low;

std::unordered_map<std::string, token> lexer::keywords = {
	{ "let", token::KW_LET },
	{ "use", token::KW_USE },
};

lexeme lexer::pop_operator() {
	int c = pop_char();
	switch (c) {
	case '=':
		return new_one(token::OP_EQUAL, "=");
	case ',':
		return new_one(token::OP_COMMA, ",");
	case ':':
		return new_one(token::OP_COLON, ":");
	case ';':
		return new_one(token::OP_SEMICOLON, ";");
	case '-':
		c = stream.peek();
		if (c == '>') {
			pop_char();
			return new_one(token::OP_ARROW, "->");
		}
		return new_one(token::OP_MINUS, "-");
	case '{':
		return new_one(token::OP_BRACE_L, "{");
	case '}':
		return new_one(token::OP_BRACE_R, "}");
	case '(':
		return new_one(token::OP_PARENTHESE_L, "(");
	case ')':
		return new_one(token::OP_PARENTHESE_R, ")");
	case '<':
		return new_one(token::OP_LESS, "<");
	case '>':
		return new_one(token::OP_GREATER, ">");
	}

	throw std::exception("invalid operator");
}

lexeme lexer::pop_identifier() {
	int c = stream.peek();
	std::stringstream buffer;
	while (std::isalnum(c)) {
		pop_char();
		buffer << (char)c;
		c = stream.peek();
	}
	std::string id = buffer.str();

	auto kw = keywords.find(id);
	if (kw != keywords.end()) {
		return new_one(kw->second, id);
	}

	return new_one(token::IDENTIFIER, id);
}

lexeme lexer::pop_string() {
	int c = pop_char();
	std::stringstream buffer;
	c = pop_char();
	while (c != '"') {
		if (c == '\\') {
			c = pop_char();
			switch (c) {
			case '0':
				c = '\0';
				break;
			case 't':
				c = '\t';
				break;
			case 'n':
				c = '\n';
				break;
			case 'r':
				c = '\r';
				break;
			default:
				throw std::exception("unknown escape");
			}
		}
		buffer << (char)c;
		c = pop_char();
	}
	return new_one(token::STRING, buffer.str());
}

lexeme lexer::pop_number() {
	int c = stream.peek();
	std::stringstream buffer;
	while (std::isdigit(c) || c == '.') {
		pop_char();
		buffer << (char)c;
		c = stream.peek();
	}

	return new_one(token::NUMBER, buffer.str());
}

int lexer::pop_char() {
	int c = stream.get();

	if (c == '\r') {
		int n = stream.peek();
		c = n == '\n' ? stream.get() : '\n';
	}

	if (c == '\n') {
		++row;
		column = 1;
	}
	else {
		++column;
	}

	return c;
}

int lexer::skip_space() {
	int c = stream.peek();
	while (std::isspace(c)) {
		pop_char();
		c = stream.peek();
	}

	if (c == '#') {
		while (c != '\n') {
			pop_char();
			c = stream.peek();
		}
		return skip_space();
	}
	return c;
}