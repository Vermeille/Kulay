#pragma once

#include "binop.h"
#include "expr.h"
#include "defaultvisitor.h"

class Mul : public Binop {
    public:
        Mul(Expr* lhs, Expr* rhs) : Binop(lhs, rhs) {}

        virtual void PrettyPrint() const;

        virtual void Accept(DefaultVisitor& v) {
            v.Visit(*this);
        }
};

