#include "varset.h"

#include <iostream>

void VarSet::PrettyPrint() const {
    std::cout << "(" << var_.str() << ") = (";
    expr_->PrettyPrint();
    std::cout << ")";
}
