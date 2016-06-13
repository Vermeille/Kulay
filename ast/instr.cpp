#include "ast.h"

Instr::Instr(Decls* let, InstrBody* body, Decls* where)
    : let_(let), body_(body), where_(where) {
}

void Instr::PrettyPrint() const {
    std::cout << "{";
    if (let_) {
        std::cout << "let [";
        let_->PrettyPrint();
        std::cout << "] in ";
    }
    body_->PrettyPrint();
    if (where_) {
        std::cout << " where [";
        where_->PrettyPrint();
        std::cout << "]";
    }
    std::cout << ";}";
}

