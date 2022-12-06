#ifndef LOW_LEX_H
#define LOW_LEX_H
#include <istream>
#include <vector>
#include <sstream>
#include <exception>
#include <cctype>
#include <unordered_map>

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
		OP_COLON, // :
		OP_SEMICOLON, // ; 
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
		std::string content;

		lexeme(int r, int c, low::token t,const std::string &ct) : row(r), column(c), token(t), content(ct) {}
		lexeme(low::token t) : lexeme(0, 0, t, "") {}
	};

	class lexer {
		int row;
		int column;
		std::istream &stream;
		static std::unordered_map<std::string, token> keywords;

		int pop_char();
		int skip_space();
		inline lexeme new_one(token t, const std::string &c = "") {
			return lexeme(row, column, t, c);
		}

		lexeme pop_number();
		lexeme pop_string();
		lexeme pop_operator();
		lexeme pop_identifier();
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
