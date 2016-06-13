#pragma once

#include "defaultvisitor.h"
#include "expr.h"
#include "identifier.h"

class VarGet : public Expr {
    private:
        Identifier var_;

    public:
        VarGet(const std::string& var) : var_(var) {}

        virtual void PrettyPrint() const { std::cout << var_.str(); }

        std::string name() const {
            return var_.str();
        }
        virtual void Accept(DefaultVisitor& v) {
            v.Visit(*this);
        }
};

