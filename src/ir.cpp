#include <iostream>
#include "ir.hpp"
#include "type.hpp"

const ClassType LoadInt::type("int");
LoadInt::LoadInt(int x) {
	value = x;
}
const Type& LoadInt::get_type(void) {
	return type;
}
void LoadInt::print(void) {
	std::cout << "load_int " << value << std::endl;
}
void LoadInt::visit(IRVisitor& visitor, int n) {
	visitor.visit_int(*this, n);
}

const ClassType LoadStr::type("str");
LoadStr::LoadStr(std::string x) {
	value = x;
}
const Type& LoadStr::get_type(void) {
	return type;
}
void LoadStr::print(void) {
	std::cout << "load_str \"" << value << '"' << std::endl;
}
void LoadStr::visit(IRVisitor& visitor, int n) {
	visitor.visit_str(*this, n);
}

LoadGlobal::LoadGlobal(std::string x) {
	name = x;
}
const Type& LoadGlobal::get_type(void) {
	auto type = new ClassType("global");
	return *type;
}
void LoadGlobal::print(void) {
	std::cout << "load_gl " << name << std::endl;
}
void LoadGlobal::visit(IRVisitor& visitor, int n) {
	visitor.visit_global(*this, n);
}

FuncCall::FuncCall(int f) {
	func = f;
}
const Type& FuncCall::get_type(void) {
	auto type = new ClassType("func");
	return *type;
}
void FuncCall::print(void) {
	std::cout << "call " << func << "(";
	for (int x: args)
		std::cout << x << ";";
	std::cout << ")" << std::endl;
}
void FuncCall::push(int arg) {
	args.push_back(arg);
}
void FuncCall::visit(IRVisitor& visitor, int n) {
	visitor.visit_func_call(*this, n);
}
