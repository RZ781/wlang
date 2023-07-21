#include <iostream>
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
std::string IntExpr::eval(void) {
        return std::to_string(value);
}

StrExpr::StrExpr(std::string x) {
        value = x;
}
void StrExpr::print(void) {
        std::cout << "<\"" << value << "\">";
}
std::string StrExpr::eval(void) {
        return value;
}

VarExpr::VarExpr(std::string x) {
        id = x;
}
void VarExpr::print(void) {
        std::cout << id;
}
std::string VarExpr::eval(void) {
        return id;
}


// types
ClassType::ClassType(std::string id) {
        name = id;
}
void ClassType::print(void) {
        std::cout << name;
        if (args.size() != 0) {
                std::cout << '<';
                for (Type* type: args) {
                        type->print();
                        std::cout << ';';
                }
                std::cout << '>';
        }
}
void ClassType::append(Type* type) {
        args.push_back(type);
}

PointerType::PointerType(Type* type) {
        inner = type;
}
void PointerType::print(void) {
        inner->print();
        std::cout << '*';
}

ArrayType::ArrayType(Type* type, int len) {
        element = type;
        length = len;
}
void ArrayType::print(void) {
        element->print();
        std::cout << '[';
        if (length != 0)
                std::cout << length;
        std::cout << ']';
}

// expressions
ExprStmt::ExprStmt(Expression* e) {
        expr = e;
}
void ExprStmt::print(void) {
        expr->print();
        std::cout << ';';
}
void ExprStmt::eval(void) {
        std::cout << expr->eval() << std::endl;
}

Block::Block(void) {}
void Block::print(void) {
        std::cout << '{';
        for (Statement* stmt: body)
                stmt->print();
        std::cout << '}';
}
void Block::eval(void) {
        for (Statement* stmt: body)
                stmt->eval();
}
void Block::append(Statement* stmt) {
        body.push_back(stmt);
}

Function::Function(std::string f, Type* t, Statement* stmt) {
        name = f;
        type = t;
        body = stmt;
}
void Function::print(void) {
        std::cout << name << "() ";
        type->print();
        std::cout << ' ';
        body->print();
}
void Function::eval(void) {
        if (name == "main")
                body->eval();
}
