#pragma once

#include "defaultvisitor.h"
#include "expr.h"

class IntLit : public Expr {
    private:
        int val_;

    public:
        IntLit(int val) : val_(val) {}

        virtual void PrettyPrint() const { std::cout << val_; }

        virtual void Accept(DefaultVisitor& v) {
            v.Visit(*this);
        }

        int value() const {
            return val_;
        }
};

