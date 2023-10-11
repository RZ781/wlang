#pragma once
#include <vector>
#include <memory>
#include "ir.hpp"
#include "type.hpp"

class Expression {
        public:
        virtual void print(void)  = 0;
	virtual int compile(Scope& scope) = 0;
};

class Statement {
        public:
        virtual void print(int indent) = 0;
	virtual void compile(Scope& scope) = 0;
};

class Declaration {
	public:
	virtual void print(int indent) = 0;
	virtual void compile(Scope& scope) = 0;
};

// expressions
class IntExpr: public Expression {
        private:
        int value;
        public:
        IntExpr(int x);
        void print(void) override;
	int compile(Scope& scope) override;
};

class StrExpr: public Expression {
        private:
        std::string value;
        public:
        StrExpr(std::string x);
        void print(void) override;
	int compile(Scope& scope) override;
};

class VarExpr: public Expression {
        private:
        std::string id;
        public:
        VarExpr(std::string x);
        void print(void) override;
	int compile(Scope& scope) override;
};

class CallExpr: public Expression {
        private:
        std::unique_ptr<Expression> func;
        std::vector<std::unique_ptr<Expression>> args;
        public:
        CallExpr(std::unique_ptr<Expression> f);
        void print(void) override;
	int compile(Scope& scope) override;
        void push(std::unique_ptr<Expression> e);
};

// statements
class ExprStmt: public Statement {
        private:
        std::unique_ptr<Expression> expr;
        public:
        ExprStmt(std::unique_ptr<Expression> e);
        void print(int indent) override;
	void compile(Scope& scope) override;
};

class BlockStmt: public Statement {
        private:
        std::vector<std::unique_ptr<Statement>> body;
        public:
        BlockStmt(void);
        void print(int indent) override;
	void compile(Scope& scope) override;
        void append(std::unique_ptr<Statement> stmt);
};

class DeclStmt: public Statement {
	private:
	std::unique_ptr<Declaration> decl;
	public:
	DeclStmt(std::unique_ptr<Declaration> decl);
	void print(int indent) override;
	void compile(Scope& scope) override;
};

// declarations
class FuncDecl: public Declaration {
        private:
        std::string name;
        std::unique_ptr<Type> type;
        std::unique_ptr<Statement> body;
        public:
        FuncDecl(std::string f, std::unique_ptr<Type> t, std::unique_ptr<Statement> stmt);
        void print(int indent) override;
	void compile(Scope& scope) override;
};
