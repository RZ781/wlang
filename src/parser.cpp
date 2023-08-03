#include <iostream>
#include <vector>
#include <memory>
#include "lexer.hpp"
#include "parser.hpp"
#include "nodes.hpp"
#include "type.hpp"

std::unique_ptr<Type> Parser::type(void) {
	auto base = std::make_unique<ClassType>(ClassType(eat(Id).data));
	if (peek().type == Symbol && peek().data == "<") { // template
		eat(Token {Symbol, "<"});
		while (peek().type != Symbol) {
			base->append(type());
			if (!(peek().type == Symbol && peek().data == ">"))
				eat(Token {Symbol, ","});
		}
		eat(Token {Symbol, ">"});
	}
	std::unique_ptr<Type> t = std::move(base);
	while (peek().type == Symbol && peek().data == "[") {
		eat(Token {Symbol, "["});
		int length = 0;
		if (peek().type == Int)
			length = std::stoi(eat(Int).data);
		eat(Token {Symbol, "]"});
		t = std::unique_ptr<Type>(new ArrayType(std::move(t), length));
	}
	return t;
}

std::unique_ptr<Expression> Parser::expr(void) {
	Token token = next();
	std::unique_ptr<Expression> e;
	switch (token.type) {
		case Id:
			e = std::make_unique<VarExpr>(VarExpr(token.data));
			break;
		case Int:
			e = std::make_unique<IntExpr>(IntExpr(std::stoi(token.data)));
			break;
		case Str:
			e = std::make_unique<StrExpr>(StrExpr(token.data));
			break;
		default:
			std::cerr << "unexpected token " << token.type << std::endl;
			throw;
	}
	while (peek().type == Symbol && peek().data == "(") {
		auto call = std::make_unique<CallExpr>(CallExpr(std::move(e)));
		eat(Token {Symbol, "("});
		while (1) {
			call->push(expr());
			if (peek().type == Symbol && peek().data == ",")
				eat(Token {Symbol, ","});
			else
				break;
		}
		eat(Token {Symbol, ")"});
		e = std::move(call);
	};
	return e;
}

std::unique_ptr<Statement> Parser::stmt(void) {
	Token token = peek();
	if (token.type == Id && token.data == "func") { // function
		eat(Token {Id, "func"});
		Token name = eat(Id);
		eat(Token {Symbol, "("});
		eat(Token {Symbol, ")"});
		eat(Token {Symbol, ":"});
		std::unique_ptr<Type> t = type();
		std::unique_ptr<Statement> body = stmt();
		return std::make_unique<Function>(Function(name.data, std::move(t), std::move(body)));
	} else if (token.type == Symbol && token.data == "{") { // block
		auto block = std::make_unique<Block>(Block());
		eat(Token {Symbol, "{"});
		while (!(peek().type == Symbol && peek().data == "}"))
			block->append(stmt());
		eat(Token {Symbol, "}"});
		return block;
	} else if (token.type == Int || token.type == Str || token.type == Id) { // expression
		auto stmt = std::make_unique<ExprStmt>(ExprStmt(expr()));
		eat(Token {Symbol, ";"});
		return stmt;
	}
	std::cerr << "unexpected token " << token.type << std::endl;
	throw;
}
