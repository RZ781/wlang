#include <iostream>
#include "parser.hpp"

int main() {
        Parser parser("main.w");
        try {
                while (parser.more()) {
                        parser.stmt()->eval();
                }
        } catch (std::string err) {
                std::cerr << "error: " << err << std::endl;
        }
}
