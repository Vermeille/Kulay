#pragma once

#include "binop.h"
#include "defaultvisitor.h"

class Add : public Binop {
    public:
        Add(Expr* lhs, Expr* rhs) : Binop(lhs, rhs) {}

        virtual void PrettyPrint() const;

        Value Eval(Context& ctx) const;

        void Accept(DefaultVisitor& v) {
            v.Visit(*this);
        }
};

