#include <iostream>
#include <vector>
#include <memory>
#include "lexer.hpp"
#include "parser.hpp"
#include "nodes.hpp"
#include "type.hpp"

Parser::Parser(std::string filename): lexer(filename) {}

bool Parser::more(void) {
	return lexer.more();
}

std::unique_ptr<Type> Parser::type(void) {
	auto base = std::make_unique<ClassType>(ClassType(lexer.eat(Id).data));
	if (lexer.peek().type == Symbol && lexer.peek().data == "<") { // template
		lexer.eat(Token {Symbol, "<"});
		while (lexer.peek().type != Symbol) {
			base->append(type());
			if (!(lexer.peek().type == Symbol && lexer.peek().data == ">"))
				lexer.eat(Token {Symbol, ","});
		}
		lexer.eat(Token {Symbol, ">"});
	}
	std::unique_ptr<Type> t = std::move(base);
	while (lexer.peek().type == Symbol && lexer.peek().data == "[") {
		lexer.eat(Token {Symbol, "["});
		int length = 0;
		if (lexer.peek().type == Int)
			length = std::stoi(lexer.eat(Int).data);
		lexer.eat(Token {Symbol, "]"});
		t = std::unique_ptr<Type>(new ArrayType(std::move(t), length));
	}
	return t;
}

std::unique_ptr<Expression> Parser::expr(void) {
	Token token = lexer.next();
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
	while (lexer.peek().type == Symbol && lexer.peek().data == "(") {
		auto call = std::make_unique<CallExpr>(CallExpr(std::move(e)));
		lexer.eat(Token {Symbol, "("});
		while (1) {
			call->push(expr());
			if (lexer.peek().type == Symbol && lexer.peek().data == ",")
				lexer.eat(Token {Symbol, ","});
			else
				break;
		}
		lexer.eat(Token {Symbol, ")"});
		e = std::move(call);
	};
	return e;
}

std::unique_ptr<Declaration> Parser::decl(void) {
	Token token = lexer.peek();
	if (token.type == Id  && token.data == "func") { // function	
		lexer.eat(Token {Id, "func"});
		Token name = lexer.eat(Id);
		lexer.eat(Token {Symbol, "("});
		lexer.eat(Token {Symbol, ")"});
		lexer.eat(Token {Symbol, ":"});
		std::unique_ptr<Type> t = type();
		std::unique_ptr<Statement> body = stmt();
		return std::make_unique<FuncDecl>(FuncDecl(name.data, std::move(t), std::move(body)));
	}
	std::cerr << "unexpected token " << token.type << std::endl;
	throw;
}

std::unique_ptr<Statement> Parser::stmt(void) {
	Token token = lexer.peek();
	if (token.type == Id && token.data == "func") { // function
		return std::make_unique<DeclStmt>(decl());
	} else if (token.type == Symbol && token.data == "{") { // block
		auto block = std::make_unique<BlockStmt>(BlockStmt());
		lexer.eat(Token {Symbol, "{"});
		while (!(lexer.peek().type == Symbol && lexer.peek().data == "}"))
			block->append(stmt());
		lexer.eat(Token {Symbol, "}"});
		return block;
	} else if (token.type == Int || token.type == Str || token.type == Id) { // expression
		auto stmt = std::make_unique<ExprStmt>(ExprStmt(expr()));
		lexer.eat(Token {Symbol, ";"});
		return stmt;
	}
	std::cerr << "unexpected token " << token.type << std::endl;
	throw;
}
