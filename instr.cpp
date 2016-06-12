#include "ast.h"

Instr::Instr(Decls* let, InstrBody* body, Decls* where)
    : let_(let), body_(body), where_(where) {
}

void Instr::PrettyPrint() const {
    if (let_) {
        std::cout << "let ";
        let_->PrettyPrint();
        std::cout << " in ";
    }
    body_->PrettyPrint();
    if (where_) {
        std::cout << " where ";
        where_->PrettyPrint();
    }
    std::cout << ";\n";
}

Value Instr::Eval(Context& ctx) const {
    if (where_) {
        where_->Eval(ctx);
    }

    if (let_) {
        let_->Eval(ctx);
    }

    return body_->Eval(ctx);
}

