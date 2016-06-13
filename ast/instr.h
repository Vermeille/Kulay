#pragma once

#include <memory>

#include "defaultvisitor.h"
#include "decls.h"
#include "instrbody.h"

class Instr {
    std::unique_ptr<Decls> let_;
    std::unique_ptr<InstrBody> body_;
    std::unique_ptr<Decls> where_;

    public:
        Instr(Decls* let, InstrBody* body, Decls* where);

        virtual void PrettyPrint() const;

        Decls* let() const {
            return let_.get();
        }

        Decls* where() const {
            return where_.get();
        }

        InstrBody* body() const {
            return body_.get();
        }

        virtual void Accept(DefaultVisitor& v) {
            v.Visit(*this);
        }

        virtual ~Instr() {}
};

