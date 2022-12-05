#ifndef LOW_LEX_H
#define LOW_LEX_H
#include <istream>
#include <vector>
#include <sstream>
#include <exception>
#include <cctype>

namespace low {
	enum token {
		END_OF_FILE = -1,
		START = 0,
		IDENTIFIER,
		NUMBER,
		STRING,
		KW_USE, // use
		KW_LET, // let
		OP_MINUS, // -
		OP_EQUAL, // =
		OP_COMMA, // ,
		OP_SEMICOLON,// ; 
		OP_LESS, // <
		OP_GREATER, // >
		OP_BRACE_L, // {
		OP_BRACE_R, // }
		OP_PARENTHESE_L, // (
		OP_PARENTHESE_R, // )
		OP_ARROW, // ->

	};
	
	struct lexeme {
		int row;
		int column;
		token token;

		lexeme(int r, int c, low::token t) : row(r), column(c), token(t) {}
		lexeme(low::token t) : lexeme(0, 0, t) {}
	};

	class lexer {
		int row;
		int column;
		std::istream &stream;

		int pop_char() {
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

		int skip_space() {
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

		lexeme pop_number() {
			int c = stream.peek();
			std::stringstream buffer;
			while (std::isdigit(c) || c == '.') {
				pop_char();
				buffer << (char32_t)c;
				c = stream.peek();
			}

			return lexeme(row, column, token::NUMBER);
		}

		inline lexeme new_one(token t) {
			return lexeme(row, column, t);
		}

		lexeme pop_string() {
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
				buffer << (char32_t)c;
				c = pop_char();
			}
			return new_one(token::STRING);
		}

		lexeme pop_operator() {
			int c = pop_char();
			switch (c) {
			case '=':
				return new_one(token::OP_EQUAL);
			case ';':
				return new_one(token::OP_SEMICOLON);
			case '-':
				c = stream.peek();
				if (c == '>') {
					pop_char();
					return new_one(token::OP_ARROW);
				}
				return new_one(token::OP_MINUS);
			case '{':
				return new_one(token::OP_BRACE_L);
			case '}':
				return new_one(token::OP_BRACE_R);
			case '(':
				return new_one(token::OP_PARENTHESE_L);
			case ')':
				return new_one(token::OP_PARENTHESE_R);
			case '<':
				return new_one(token::OP_LESS);
			case '>':
				return new_one(token::OP_GREATER);
			}

			throw std::exception("invalid operator");
		}

		lexeme pop_identifier() {
			int c = stream.peek();
			std::stringstream buffer;
			while(std::isalnum(c)) {
				pop_char();
				buffer << (char32_t)c;
				c = stream.peek();
			}
			std::string id = buffer.str();
			return new_one(token::IDENTIFIER);
		}
	public:
		lexer(std::istream& s) :
			stream(s),
			row(1),
			column(1)
		{

		}

		std::vector<lexeme> lex() {
			std::vector<lexeme> result;

			lexeme i(token::START);
			while (i.token != token::END_OF_FILE) {
				i = pop();
				result.push_back(i);
			}

			return result;
		}

		lexeme pop() {
			int c = skip_space();
			if (std::isdigit(c)) {
				return pop_number();
			}

			if (c == '"') {
				return pop_string();
			}

			if (std::ispunct(c)) {
				return pop_operator();
			}

			if (std::isalpha(c)) {
				return pop_identifier();
			}

			if (c == -1) {
				return new_one(token::END_OF_FILE);
			}

			throw std::exception("unknown lexeme");
		}
	};
}

#endif
