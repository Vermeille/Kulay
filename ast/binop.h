#pragma once

#include <memory>

#include "expr.h"
#include "defaultvisitor.h"

class Binop : public Expr {
    private:
        std::unique_ptr<Expr> lhs_;
        std::unique_ptr<Expr> rhs_;

    public:
        Binop(Expr* lhs, Expr* rhs) : lhs_(lhs), rhs_(rhs) {}

        Expr* lhs() const {
            return lhs_.get();
        }

        Expr* rhs() const {
            return rhs_.get();
        }

        virtual void Accept(DefaultVisitor& v) = 0;
};

