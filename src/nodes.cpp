#include <iostream>
#include <memory>
#include <vector>
#include "parser.hpp"
#include "nodes.hpp"

// expressions
IntExpr::IntExpr(int x) {
        value = x;
}
void IntExpr::print(void) {
        std::cout << value;
}

StrExpr::StrExpr(std::string x) {
        value = x;
}
void StrExpr::print(void) {
        std::cout << "<\"" << value << "\">";
}

VarExpr::VarExpr(std::string x) {
        id = x;
}
void VarExpr::print(void) {
        std::cout << id;
}

CallExpr::CallExpr(std::unique_ptr<Expression> f) {
        func = std::move(f);
}
void CallExpr::print(void) {
        func->print();
        std::cout << '(';
        for (std::unique_ptr<Expression>& e: args) {
                e->print();
                std::cout << ';';
        }
        std::cout << ')';
}
void CallExpr::push(std::unique_ptr<Expression> e) {
        args.push_back(std::move(e));
}

// statements
ExprStmt::ExprStmt(std::unique_ptr<Expression> e) {
	expr = std::move(e);
}
void ExprStmt::print(int indent) {
	for (int i=0; i<indent; i++)
		std::cout << '\t';
        expr->print();
        std::cout << ';' << std::endl;
}

Block::Block(void) {}
void Block::print(int indent) {
	for (int i=0; i<indent; i++)
		std::cout << '\t';
        std::cout << '{' << std::endl;
        for (std::unique_ptr<Statement>& stmt: body) {
                stmt->print(indent + 1);
	}
	for (int i=0; i<indent; i++)
		std::cout << '\t';
        std::cout << '}' << std::endl;
}
void Block::append(std::unique_ptr<Statement> stmt) {
        body.push_back(std::move(stmt));
}

Function::Function(std::string f, std::unique_ptr<Type> t, std::unique_ptr<Statement> stmt) {
        name = f;
        type = std::move(t);
        body = std::move(stmt);
}
void Function::print(int indent) {
	for (int i=0; i<indent; i++)
		std::cout << '\t';
        std::cout << name << "(): ";
        type->print();
	std::cout << ' ';
        body->print(indent + 1);
}
