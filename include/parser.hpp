#pragma once
#include "lexer.hpp"

class Statement {
        public:
        virtual void print(void) = 0;
        virtual void eval(void) = 0;
};
class Expression {
        public:
        virtual void print(void) = 0;
        virtual std::string eval(void) = 0;
};
class Type {
        public:
        virtual void print(void) = 0;
};

class Parser: public Lexer {
        private:
        Expression* expr(void);
        Type* type(void);
        public:
        using Lexer::Lexer;
        Statement* stmt(void);
};
