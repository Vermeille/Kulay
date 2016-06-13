#pragma once

#include <vector>
#include <memory>

#include "defaultvisitor.h"
#include "instr.h"
#include "instrbody.h"

class Block : public InstrBody {
    std::vector<std::unique_ptr<Instr>> instrs_;

    public:
        void Append(Instr* e) {
            instrs_.emplace_back(e);
        }

        size_t size() const { return instrs_.size(); }
        auto begin() { return instrs_.begin(); }
        auto end() { return instrs_.end(); }

        void PrettyPrint() const {
            for (auto& i : instrs_) {
                i->PrettyPrint();
                std::cout << ";\n";
            }
        }

        void Accept(DefaultVisitor& v) {
            v.Visit(*this);
        }
};

