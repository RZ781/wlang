#pragma once

// expressions
class IntExpr: public Expression {
        private:
        int value;
        public:
        IntExpr(int x);
        void print(void) override;
        std::string eval(void) override;
};
class StrExpr: public Expression {
        private:
        std::string value;
        public:
        StrExpr(std::string x);
        void print(void) override;
        std::string eval(void) override;
};
class VarExpr: public Expression {
        private:
        std::string id;
        public:
        VarExpr(std::string x);
        void print(void) override;
        std::string eval(void) override;
};

// types
class ClassType: public Type {
        private:
        std::string name;
        std::vector<Type*> args;
        public:
        ClassType(std::string id);
        void print(void) override;
        void append(Type* type);
};
class PointerType: public Type {
        private:
        Type* inner;
        public:
        PointerType(Type* type);
        void print(void) override;
};
class ArrayType: public Type {
        private:
        Type* element;
        int length;
        public:
        ArrayType(Type* type, int len);
        void print(void) override;
};

// statements
class ExprStmt: public Statement {
        private:
        Expression* expr;
        public:
        ExprStmt(Expression* e);
        void print(void) override;
        void eval(void) override;
};
class Block: public Statement {
        private:
        std::vector<Statement*> body;
        public:
        Block(void);
        void print(void) override;
        void eval(void) override;
        void append(Statement* stmt);
};
class Function: public Statement {
        private:
        std::string name;
        Type* type;
        Statement* body;
        public:
        Function(std::string f, Type* t, Statement* stmt);
        void print(void) override;
        void eval(void) override;
};
