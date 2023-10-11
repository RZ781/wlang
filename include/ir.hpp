#pragma once
#include <fstream>
#include <vector>
#include <map>
#include <memory>
#include "type.hpp"

class IRVisitor;

class Op {
	public:
	virtual const Type& get_type(void) = 0;
	virtual void print(void) = 0;
	virtual void visit(IRVisitor& visitor, int n) = 0;
};

class LoadInt: public Op {
	private:
	int value;
	static const ClassType type;
	public:
	LoadInt(int x);
	const Type& get_type(void) override;
	void print(void) override;
	void visit(IRVisitor& visitor, int n) override;
};

class LoadStr: public Op {
	private:
	std::string value;
	static const ClassType type;
	public:
	LoadStr(std::string x);
	const Type& get_type(void) override;
	void print(void) override;
	void visit(IRVisitor& visitor, int n) override;
};

class LoadGlobal: public Op {
	private:
	std::string name;
	public:
	LoadGlobal(std::string x);
	const Type& get_type(void) override;
	void print(void) override;
	void visit(IRVisitor& visitor, int n) override;
};

class FuncCall: public Op {
	private:
	int func;
	std::vector<int> args;
	public:
	FuncCall(int f);
	const Type& get_type(void) override;
	void print(void) override;
	void push(int arg);
	void visit(IRVisitor& visitor, int n) override;
};

class Scope {
	private:
	int length;
	std::vector<std::unique_ptr<Scope>> scope;
	std::map<std::string, Scope&> funcs;
	public:
	Scope(void);
	std::vector<std::unique_ptr<Op>> code;
	int push_op(std::unique_ptr<Op>);
	Scope& new_scope(void);
	Scope& new_func(std::string name);
};

class IRVisitor {
	public:
	virtual void visit_int(LoadInt& op, int n) = 0;
	virtual void visit_str(LoadStr& op, int n) = 0;
	virtual void visit_global(LoadGlobal& op, int n) = 0;
	virtual void visit_func_call(FuncCall& op, int n) = 0;
};

class CGenerator: public IRVisitor {
	private:
	std::ofstream out;
	public:
	CGenerator(const char* filename);
	void visit_int(LoadInt& op, int n) override;
	void visit_str(LoadStr& op, int n) override;
	void visit_global(LoadGlobal& op, int n) override;
	void visit_func_call(FuncCall& op, int n) override;
};
