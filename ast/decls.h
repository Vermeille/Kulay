#pragma once

#include <vector>
#include <memory>

#include "varset.h"

class Decls {
    std::vector<std::unique_ptr<VarSet>> decls_;
    public:
        void Append(VarSet* vs) {
            decls_.emplace_back(vs);
        }

        void PrettyPrint() const;

        void Accept(DefaultVisitor& v) {
            return v.Visit(*this);
        }

        auto begin() { return decls_.begin(); }
        auto end() { return decls_.end(); }
};
