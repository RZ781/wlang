#pragma once
#include <vector>
#include <memory>
#include "ir.hpp"
#include "type.hpp"

class Statement {
        public:
        virtual void print(int indent) = 0;
	virtual void compile(Module& module) = 0;
};
class Expression {
        public:
        virtual void print(void)  = 0;
	virtual int compile(Module& module) = 0;
};

// expressions
class IntExpr: public Expression {
        private:
        int value;
        public:
        IntExpr(int x);
        void print(void) override;
	int compile(Module& module) override;
};
class StrExpr: public Expression {
        private:
        std::string value;
        public:
        StrExpr(std::string x);
        void print(void) override;
	int compile(Module& module) override;
};
class VarExpr: public Expression {
        private:
        std::string id;
        public:
        VarExpr(std::string x);
        void print(void) override;
	int compile(Module& module) override;
};
class CallExpr: public Expression {
        private:
        std::unique_ptr<Expression> func;
        std::vector<std::unique_ptr<Expression>> args;
        public:
        CallExpr(std::unique_ptr<Expression> f);
        void print(void) override;
	int compile(Module& module) override;
        void push(std::unique_ptr<Expression> e);
};

// statements
class ExprStmt: public Statement {
        private:
        std::unique_ptr<Expression> expr;
        public:
        ExprStmt(std::unique_ptr<Expression> e);
        void print(int indent) override;
	void compile(Module& module) override;
};
class Block: public Statement {
        private:
        std::vector<std::unique_ptr<Statement>> body;
        public:
        Block(void);
        void print(int indent) override;
	void compile(Module& module) override;
        void append(std::unique_ptr<Statement> stmt);
};
class Function: public Statement {
        private:
        std::string name;
        std::unique_ptr<Type> type;
        std::unique_ptr<Statement> body;
        public:
        Function(std::string f, std::unique_ptr<Type> t, std::unique_ptr<Statement> stmt);
        void print(int indent) override;
	void compile(Module& module) override;
};
