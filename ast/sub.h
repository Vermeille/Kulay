#pragma once

#include "defaultvisitor.h"
#include "binop.h"

class Sub : public Binop {
    public:
        Sub(Expr* lhs, Expr* rhs) : Binop(lhs, rhs) {}

        virtual void PrettyPrint() const;

        virtual void Accept(DefaultVisitor& v) {
            v.Visit(*this);
        }
};

