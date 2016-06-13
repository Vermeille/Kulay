#include "mul.h"

#include <iostream>

void Mul::PrettyPrint() const {
    std::cout << "(";
    lhs()->PrettyPrint();
    std::cout << ") * (";
    rhs()->PrettyPrint();
    std::cout << ")";
}

