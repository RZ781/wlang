#include <iostream>
#include <memory>
#include "parser.hpp"
#include "ir.hpp"

int main() {
	Parser parser("main.w");
	Module module;
	while (parser.more()) {
		std::unique_ptr<Statement> stmt = parser.stmt();
		stmt->print(0);
		stmt->compile(module);
	}
	for (std::unique_ptr<Op>& op: module.code)
		op->print();
}
