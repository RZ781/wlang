#pragma once
#include <memory>
#include "lexer.hpp"
#include "type.hpp"
#include "nodes.hpp"

class Parser: public Lexer {
	private:
	std::unique_ptr<Expression> expr(void);
	std::unique_ptr<Type> type(void);
	public:
	using Lexer::Lexer;
	std::unique_ptr<Statement> stmt(void);
};
