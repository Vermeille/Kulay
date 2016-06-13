#pragma once

#include <memory>

#include "instrbody.h"
#include "identifier.h"
#include "instr.h"
#include "defaultvisitor.h"

class VarSet : public InstrBody {
    private:
        Identifier var_;
        std::unique_ptr<InstrBody> expr_;

    public:
        VarSet(const std::string& vg, InstrBody* e) : var_(vg), expr_(e) {}

        virtual void PrettyPrint() const;

        virtual void Accept(DefaultVisitor& v) override {
            v.Visit(*this);
        }

        Identifier& var() { return var_; }
        InstrBody* expr() const { return expr_.get(); }
};

