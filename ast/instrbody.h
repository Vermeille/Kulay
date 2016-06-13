#pragma once

#include "defaultvisitor.h"

class InstrBody {
    public:
        virtual void PrettyPrint() const = 0;
        virtual void Accept(DefaultVisitor& v) {
            v.Visit(*this);
        }
};

