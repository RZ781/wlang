#include <vector>
#include <memory>
#include "ir.hpp"
#include "nodes.hpp"

Scope::Scope(void) {
	length = 0;
}
int Scope::push_op(std::unique_ptr<Op> op) {
	code.push_back(std::move(op));
	length++;
	return length - 1;
}

int IntExpr::compile(Scope& mod) {
	LoadInt op(value);
	return mod.push_op(std::make_unique<LoadInt>(op));
}

int StrExpr::compile(Scope& mod) {
	LoadStr op(value);
	return mod.push_op(std::make_unique<LoadStr>(op));
}

int VarExpr::compile(Scope& mod) {
	LoadGlobal op(id);
	return mod.push_op(std::make_unique<LoadGlobal>(op));
}

int CallExpr::compile(Scope& mod) {
	int f = func->compile(mod);
	FuncCall op(f);
	for (std::unique_ptr<Expression>& arg: args)
		op.push(arg->compile(mod));
	return mod.push_op(std::make_unique<FuncCall>(op));
}

void ExprStmt::compile(Scope& mod) {
	expr->compile(mod);
}
void BlockStmt::compile(Scope& mod) {
	for (std::unique_ptr<Statement>& stmt: body)
		stmt->compile(mod);
}
void DeclStmt::compile(Scope& mod) {
	decl->compile(mod);
}

void FuncDecl::compile(Scope& mod) {
	body->compile(mod);
}
