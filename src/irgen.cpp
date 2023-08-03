#include <vector>
#include <memory>
#include "ir.hpp"
#include "nodes.hpp"

Module::Module(void) {
	length = 0;
}
int Module::push_op(std::unique_ptr<Op> op) {
	code.push_back(std::move(op));
	length++;
	return length - 1;
}

int IntExpr::compile(Module& mod) {
	LoadInt op(value);
	return mod.push_op(std::make_unique<LoadInt>(op));
}

int StrExpr::compile(Module& mod) {
	LoadStr op(value);
	return mod.push_op(std::make_unique<LoadStr>(op));
}

int VarExpr::compile(Module& mod) {
	LoadGlobal op(id);
	return mod.push_op(std::make_unique<LoadGlobal>(op));
}

int CallExpr::compile(Module& mod) {
	int f = func->compile(mod);
	FuncCall op(f);
	for (std::unique_ptr<Expression>& arg: args)
		op.push(arg->compile(mod));
	return mod.push_op(std::make_unique<FuncCall>(op));
}

void ExprStmt::compile(Module& mod) {
	expr->compile(mod);
}
void Block::compile(Module& mod) {
	for (std::unique_ptr<Statement>& stmt: body)
		stmt->compile(mod);
}
void Function::compile(Module& mod) {
	body->compile(mod);
}
