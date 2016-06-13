#include "sub.h"

#include <iostream>

void Sub::PrettyPrint() const {
    std::cout << "(";
    lhs()->PrettyPrint();
    std::cout << ") - (";
    rhs()->PrettyPrint();
    std::cout << ")";
}
