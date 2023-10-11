#pragma once
#include <memory>
#include "lexer.hpp"
#include "type.hpp"
#include "nodes.hpp"

class Parser {
	private:
	std::unique_ptr<Expression> expr(void);
	std::unique_ptr<Statement> stmt(void);
	std::unique_ptr<Type> type(void);
	Lexer lexer;
	public:
	Parser(std::string filename);
	std::unique_ptr<Declaration> decl(void);
	bool more(void);
};
