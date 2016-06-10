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
            return vars_.find(name)->second;
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

class Expr {
    public:
        virtual void PrettyPrint() const = 0;
        virtual Value Eval(Context& ctx) const = 0;
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

class VarSet : public Expr {
    private:
        Identifier var_;
        std::unique_ptr<Expr> expr_;

    public:
        VarSet(const std::string& vg, Expr* e) : var_(vg), expr_(e) {}

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

class Block {
    std::vector<std::unique_ptr<Expr>> instrs_;

    public:
        void Append(Expr* e) {
            instrs_.emplace_back(e);
        }

        void PrettyPrint() const {
            for (auto& i : instrs_) {
                i->PrettyPrint();
                std::cout << ";\n";
            }
        }

        void Eval(Context& ctx) const {
            for (auto& i : instrs_) {
                i->Eval(ctx);
            }
        }
};

