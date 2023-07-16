#include <iostream>
#include <vector>
#include "lexer.hpp"
#include "parser.hpp"

// expressions
class IntExpr: public Expression {
        private:
        int value;
        public:
        IntExpr(int x) {
                value = x;
        }
        void print(void) {
                std::cout << value;
        }
        int eval(void) {
                return value;
        }
};
class StrExpr: public Expression {
        private:
        std::string value;
        public:
        StrExpr(std::string x) {
                value = x;
        }
        void print(void) {
                std::cout << '"' << value << '"';
        }
        int eval(void) {
                return 574136;
        }
};
class VarExpr: public Expression {
        private:
        std::string id;
        public:
        VarExpr(std::string x) {
                id = x;
        }
        void print(void) {
                std::cout << id;
        }
        int eval(void) {
                return 44414813;
        }
};

// statements
class ExprStmt: public Statement {
        private:
        Expression* expr;
        public:
        ExprStmt(Expression* e) {
                expr = e;
        }
        void print(void) {
                expr->print();
                std::cout << ';';
        }
        void eval(void) {
                std::cout << expr->eval() << std::endl;
        }
};
class Block: public Statement {
        private:
        std::vector<Statement*> body;
        public:
        Block(void) {}
        void print(void) {
                std::cout << '{';
                for (Statement* stmt: body)
                        stmt->print();
                std::cout << '}';
        }
        void eval(void) {
                for (Statement* stmt: body)
                        stmt->eval();
        }
        void append(Statement* stmt) {
                body.push_back(stmt);
        }
};
class Function: public Statement {
        private:
        std::string name;
        Statement* body;
        public:
        Function(std::string f, Statement* stmt) {
                name = f;
                body = stmt;
        }
        void print(void) {
                std::cout << name << "() ";
                body->print();
        }
        void eval(void) {
                if (name == "main")
                        body->eval();
        }
};

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
        if (token.type == Id && token.data == "func") {
                eat(Token {Id, "func"});
                Token name = eat(Id);
                eat(Token {Symbol, "("});
                eat(Token {Symbol, ")"});
                eat(Token {Symbol, ":"});
                eat(Id);
                Statement* body = stmt();
                return new Function(name.data, body);
        } else if (token.type == Symbol && token.data == "{") {
                auto block = new Block();
                eat(Token {Symbol, "{"});
                while (!(peek().type == Symbol && peek().data == "}"))
                        block->append(stmt());
                eat(Token {Symbol, "}"});
                return block;
        } else if (token.type == Int || token.type == Str || token.type == Id) {
                auto stmt = new ExprStmt(expr());
                eat(Token {Symbol, ";"});
                return stmt;
        }
        std::cerr << "unexpected token " << token.type << std::endl;
        throw;
}
