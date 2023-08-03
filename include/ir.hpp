#pragma once
#include <vector>
#include <memory>
#include <map>
#include "type.hpp"

class Op {
	public:
	virtual const Type& get_type(void) = 0;
	virtual void print(void) = 0;
};
class LoadInt: public Op {
	private:
	int value;
	static const ClassType type;
	public:
	LoadInt(int x);
	const Type& get_type(void) override;
	void print(void) override;
};
class LoadStr: public Op {
	private:
	std::string value;
	static const ClassType type;
	public:
	LoadStr(std::string x);
	const Type& get_type(void) override;
	void print(void) override;
};
class LoadGlobal: public Op {
	private:
	std::string name;
	public:
	LoadGlobal(std::string x);
	const Type& get_type(void) override;
	void print(void) override;
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
};

struct Module {
	Module(void);
	std::vector<std::unique_ptr<Op>> code;
	int length;
	int push_op(std::unique_ptr<Op> op);
};
