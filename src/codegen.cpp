#include <fstream>
#include "ir.hpp"

CGenerator::CGenerator(const char* filename) {
	out = std::ofstream(filename);
}

void CGenerator::visit_int(LoadInt& op, int n) {
	(void) op;
	(void) n;
}

void CGenerator::visit_str(LoadStr& op, int n) {
	(void) op;
	(void) n;
}

void CGenerator::visit_global(LoadGlobal& op, int n) {
	(void) op;
	(void) n;
}

void CGenerator::visit_func_call(FuncCall& op, int n) {
	(void) op;
	(void) n;
}
