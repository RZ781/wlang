#include <iostream>
#include "parser.hpp"

int main() {
        Parser parser("main.w");

        while (parser.more()) {
                parser.stmt()->print();
        }
}
