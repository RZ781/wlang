#include <iostream>
#include <vector>
#include "type.hpp"

ClassType::ClassType(std::string id) {
	name = id;
}
void ClassType::print(void) {
	std::cout << name;
	if (args.size() != 0) {
		std::cout << '<';
		for (std::unique_ptr<Type>& type: args) {
			type->print();
			std::cout << ';';
		}
		std::cout << '>';
	}
}
void ClassType::append(std::unique_ptr<Type> type) {
	args.push_back(std::move(type));
}

PointerType::PointerType(Type* type) {
	inner = std::unique_ptr<Type>(type);
}
void PointerType::print(void) {
	inner->print();
	std::cout << '*';
}

ArrayType::ArrayType(std::unique_ptr<Type> type, int len) {
	element = std::move(type);
	length = len;
}
void ArrayType::print(void) {
	element->print();
	std::cout << '[';
	if (length != 0)
		std::cout << length;
	std::cout << ']';
}
