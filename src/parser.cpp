#include <iostream>
#include <vector>
#include "lexer.hpp"
#include "parser.hpp"
#include "nodes.hpp"

Type* Parser::type(void) {
        ClassType* base = new ClassType(eat(Id).data);
        if (peek().type == Symbol && peek().data == "<") { // template
                eat(Token {Symbol, "<"});
                while (peek().type != Symbol) {
                        base->append(type());
                        if (!(peek().type == Symbol && peek().data == ">"))
                                eat(Token {Symbol, ","});
                }
                eat(Token {Symbol, ">"});
        }
        Type* t = base;
        while (peek().type == Symbol && (peek().data == "*" || peek().data == "[")) {
                if (peek().data == "*") { // pointer
                        eat(Token {Symbol, "*"});
                        t = new PointerType(t);
                } else if (peek().data == "[") { // array
                        eat(Token {Symbol, "["});
                        int length = 0;
                        if (peek().type == Int)
                                length = std::stoi(eat(Int).data);
                        eat(Token {Symbol, "]"});
                        t = new ArrayType(t, length);
                }
        }
        return t;
}

Expression* Parser::expr(void) {
        Token token = next();
        switch (token.type) {
                case Id:
                        return new VarExpr(token.data);
                case Int:
                        return new IntExpr(std::stoi(token.data));
                case Str:
                        return new StrExpr(token.data);
                default:
                        std::cerr << "unexpected token " << token.type << std::endl;
        }
        throw;
}

Statement* Parser::stmt(void) {
        Token token = peek();
        if (token.type == Id && token.data == "func") { // function
                eat(Token {Id, "func"});
                Token name = eat(Id);
                eat(Token {Symbol, "("});
                eat(Token {Symbol, ")"});
                eat(Token {Symbol, ":"});
                Type* t = type();
                Statement* body = stmt();
                return new Function(name.data, t, body);
        } else if (token.type == Symbol && token.data == "{") { // block
                auto block = new Block();
                eat(Token {Symbol, "{"});
                while (!(peek().type == Symbol && peek().data == "}"))
                        block->append(stmt());
                eat(Token {Symbol, "}"});
                return block;
        } else if (token.type == Int || token.type == Str || token.type == Id) { // expression
                auto stmt = new ExprStmt(expr());
                eat(Token {Symbol, ";"});
                return stmt;
        }
        std::cerr << "unexpected token " << token.type << std::endl;
        throw;
}
