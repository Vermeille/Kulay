#pragma once

#include <memory>

#include "expr.h"
#include "instrbody.h"

class Print : public InstrBody {
    std::unique_ptr<Expr> e_;

    public:
        Print(Expr* e) : e_(e) {}

        void PrettyPrint() const {
            std::cout << "print ";
            e_->PrettyPrint();
        }

        Expr* expr() const {
            return e_.get();
        }

        virtual void Accept(DefaultVisitor& v) {
            v.Visit(*this);
        }
};

