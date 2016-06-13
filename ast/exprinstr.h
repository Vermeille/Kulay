#pragma once

#include <memory>

#include "defaultvisitor.h"
#include "expr.h"
#include "instrbody.h"

class ExprInstr : public InstrBody {
    std::unique_ptr<Expr> e_;

    public:
        ExprInstr(Expr* e) : e_(e) {}

        virtual void PrettyPrint() const {
            e_->PrettyPrint();
        }

        Expr* expr() const {
            return e_.get();
        }

        virtual void Accept(DefaultVisitor& v) {
            v.Visit(*this);
        }
};

