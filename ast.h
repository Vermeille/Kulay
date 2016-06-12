#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

class Value {
    int val_;

    public:
        Value() {}
        Value(int x) : val_(x) {}
        int GetInt() const { return val_; }
};

class Context {
    std::unordered_map<std::string, Value> vars_;

    public:
        void SetVar(const std::string& name, Value value) {
            vars_[name] = value;
        }

        Value GetVar(const std::string& name) const {
            auto val = vars_.find(name);

            if (val == vars_.end()) {
                throw std::runtime_error("can't find a value for " + name);
            }

            return val->second;
        }

        void Dump() const {
            for (auto& i : vars_) {
                std::cout << i.first << " = " << i.second.GetInt() << "\n";
            }
        }
};

class Identifier {
    std::string name_;

    public:
        Identifier(const std::string& str) : name_(str) {}
        const std::string& str() const { return name_; }
};

class InstrBody {
    public:
        virtual void PrettyPrint() const = 0;
        virtual Value Eval(Context& ctx) const = 0;
};

class Decls;

class Instr {
    std::unique_ptr<Decls> let_;
    std::unique_ptr<InstrBody> body_;
    std::unique_ptr<Decls> where_;

    public:
        Instr(Decls* let, InstrBody* body, Decls* where);

        virtual void PrettyPrint() const;

        virtual Value Eval(Context& ctx) const;
};

class Expr {
    public:
        virtual void PrettyPrint() const = 0;
        virtual Value Eval(Context& ctx) const = 0;
};

class ExprInstr : public InstrBody {
    std::unique_ptr<Expr> e_;

    public:
        ExprInstr(Expr* e) : e_(e) {}

        virtual void PrettyPrint() const {
            e_->PrettyPrint();
        }

        virtual Value Eval(Context& ctx) const {
            return e_->Eval(ctx);
        }
};

class IntLit : public Expr {
    private:
        int val_;

    public:
        IntLit(int val) : val_(val) {}

        virtual void PrettyPrint() const { std::cout << val_; }

        virtual Value Eval(Context&) const {
            return Value(val_);
        }
};

class VarGet : public Expr {
    private:
        Identifier var_;

    public:
        VarGet(const std::string& var) : var_(var) {}

        virtual void PrettyPrint() const { std::cout << var_.str(); }

        virtual Value Eval(Context& ctx) const {
            return ctx.GetVar(var_.str());
        }
};

class Binop : public Expr {
    private:
        std::unique_ptr<Expr> lhs_;
        std::unique_ptr<Expr> rhs_;

    public:
        Binop(Expr* lhs, Expr* rhs) : lhs_(lhs), rhs_(rhs) {}

        Expr* lhs() const {
            return lhs_.get();
        }

        Expr* rhs() const {
            return rhs_.get();
        }
};

class Add : public Binop {
    public:
        Add(Expr* lhs, Expr* rhs) : Binop(lhs, rhs) {}

        virtual void PrettyPrint() const {
            std::cout << "(";
            lhs()->PrettyPrint();
            std::cout << ") + (";
            rhs()->PrettyPrint();
            std::cout << ")";
        }

        virtual Value Eval(Context& ctx) const {
            return Value(lhs()->Eval(ctx).GetInt() + rhs()->Eval(ctx).GetInt());
        }
};

class Mul : public Binop {
    public:
        Mul(Expr* lhs, Expr* rhs) : Binop(lhs, rhs) {}

        virtual void PrettyPrint() const {
            std::cout << "(";
            lhs()->PrettyPrint();
            std::cout << ") * (";
            rhs()->PrettyPrint();
            std::cout << ")";
        }

        virtual Value Eval(Context& ctx) const {
            return Value(lhs()->Eval(ctx).GetInt() * rhs()->Eval(ctx).GetInt());
        }
};

class Sub : public Binop {
    public:
        Sub(Expr* lhs, Expr* rhs) : Binop(lhs, rhs) {}

        virtual void PrettyPrint() const {
            std::cout << "(";
            lhs()->PrettyPrint();
            std::cout << ") - (";
            rhs()->PrettyPrint();
            std::cout << ")";
        }

        virtual Value Eval(Context& ctx) const {
            return Value(lhs()->Eval(ctx).GetInt() - rhs()->Eval(ctx).GetInt());
        }
};

class VarSet : public InstrBody {
    private:
        Identifier var_;
        std::unique_ptr<Instr> expr_;

    public:
        VarSet(const std::string& vg, Instr* e) : var_(vg), expr_(e) {}

        virtual void PrettyPrint() const {
            std::cout << "(" << var_.str() << ") = (";
            expr_->PrettyPrint();
            std::cout << ")";
        }

        virtual Value Eval(Context& ctx) const {
            Value val = expr_->Eval(ctx);
            ctx.SetVar(var_.str(), val);
            return val;
        }

};

class Block : public InstrBody {
    std::vector<std::unique_ptr<Instr>> instrs_;

    public:
        void Append(Instr* e) {
            instrs_.emplace_back(e);
        }

        void PrettyPrint() const {
            for (auto& i : instrs_) {
                i->PrettyPrint();
                std::cout << ";\n";
            }
        }

        Value Eval(Context& ctx) const {
            for (auto& i : instrs_) {
                i->Eval(ctx);
            }
            return Value();
        }
};

class Print : public InstrBody {
    std::unique_ptr<Expr> e_;

    public:
        Print(Expr* e) : e_(e) {}

        void PrettyPrint() const {
            std::cout << "print ";
            e_->PrettyPrint();
            std::cout << ";\n";
        }

        Value Eval(Context& ctx) const {
            std::cout << e_->Eval(ctx).GetInt() << "\n";
            return Value();
        }
};

class Decls {
    std::vector<std::unique_ptr<VarSet>> decls_;
    public:
        void Append(VarSet* vs) {
            decls_.emplace_back(vs);
        }

        void PrettyPrint() const {
            for (auto& d : decls_) {
                d->PrettyPrint();
            }
        }

        void Eval(Context& ctx) const {
            for (auto& d : decls_) {
                d->Eval(ctx);
            }
        }
};
