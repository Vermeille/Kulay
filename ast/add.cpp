#include "add.h"

#include <iostream>

void Add::PrettyPrint() const {
    std::cout << "(";
    lhs()->PrettyPrint();
    std::cout << ") + (";
    rhs()->PrettyPrint();
    std::cout << ")";
}

