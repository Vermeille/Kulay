#pragma once

#include <stdexcept>

#define NODES \
    X(Add) \
    X(Value) \
    X(Context) \
    X(Binop) \
    X(Block) \
    X(Decls) \
    X(Expr) \
    X(ExprInstr) \
    X(Identifier) \
    X(InstrBody) \
    X(Instr) \
    X(IntLit) \
    X(Mul) \
    X(Print) \
    X(Sub) \
    X(VarGet) \
    X(VarSet) \

#define X(A) class A;
    NODES
#undef X

class DefaultVisitor {
    public:
#define X(A) virtual void Visit(A&) { \
        throw std::invalid_argument("No implementation for Visit("#A")"); \
    }
    NODES
#undef X

    virtual ~DefaultVisitor() {}
};
