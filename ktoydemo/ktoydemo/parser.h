#pragma once
#include <map>
#include <memory>
#include "ast.h"

int getNextToken();
std::unique_ptr<FunctionAST> ParseDefinition();
std::unique_ptr<PrototypeAST> ParseExtern();
std::unique_ptr<FunctionAST> ParseTopLevelExpr();

namespace ktoy {
	class parser {
		int current_token;
		std::map<char, int> op_precedence;
	public:

		void set_op_precedence(char c, int i) {
			op_precedence.emplace(c, i);
		}
	};
}