#pragma once

#include "defaultvisitor.h"

class Expr {
    public:
        virtual void PrettyPrint() const = 0;

        virtual void Accept(DefaultVisitor& v) = 0;
        //virtual void Accept(DefaultVisitor& v) const = 0;
        virtual ~Expr() {}
};

