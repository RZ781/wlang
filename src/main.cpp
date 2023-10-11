#include <iostream>
#include <memory>
#include "parser.hpp"
#include "nodes.hpp"
#include "ir.hpp"
 
int main() {
	Parser parser("main.w");
	Scope module;
	while (parser.more()) {
		std::unique_ptr<Declaration> decl = parser.decl();
		decl->print(0);
		decl->compile(module);
	}
	CGenerator c_gen("out.c");
	int n = 0;
	for (std::unique_ptr<Op>& op: module.code)
		op->visit(c_gen, n++);
}
