#include "decls.h"

#include <iostream>

void Decls::PrettyPrint() const {
    for (auto& d : decls_) {
        d->PrettyPrint();
        std::cout << ", ";
    }
}

