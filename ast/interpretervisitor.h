#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "ast.h"

class Value {
    enum class Type {
        Int,
        Void
    };
    enum Type type_;
    int val_;

    public:
        Value() : type_(Type::Void) {}
        Value(int x) : type_(Type::Int), val_(x) {}
        int GetInt() const {
            if (type_ != Type::Int) {
                throw std::runtime_error("Not an integer value");
            }
            return val_;
        }
};

class Context {
    std::vector<std::unordered_map<std::string, Value>> vars_;

    public:
        void PushScope() {
            vars_.push_back(std::unordered_map<std::string, Value>());
        }

        void PopScope() {
            vars_.pop_back();
        }

        void DeclNewVar(const std::string& name, Value v) {
            vars_.back()[name] = v;
        }

        Value& FindVar(const std::string& name) {
            auto it = vars_.rbegin();
            while (it != vars_.rend()) {
                auto found = it->find(name);
                if (found != it->end()) {
                    return found->second;
                }
                ++it;
            }
            throw std::runtime_error(std::string("Can't find ") + name);
        }

        const Value& FindVar(const std::string& name) const {
            auto it = vars_.rbegin();
            while (it != vars_.rend()) {
                auto found = it->find(name);
                if (found != it->end()) {
                    return found->second;
                }
                ++it;
            }
            throw std::runtime_error(std::string("Can't find ") + name);
        }

        void SetVar(const std::string& name, Value value) {
            FindVar(name) = value;
        }

        Value GetVar(const std::string& name) const {
            return FindVar(name);
        }

        void Dump() const {
            for (auto& j : vars_) {
                std::cout << "==\n";
                for (auto& i : j) {
                    std::cout << i.first << " = " << i.second.GetInt() << "\n";
                }
            }
        }
};

class InterpreterVisitor : public DefaultVisitor {
    Context ctx_;

    Value ret_;

    public:
        virtual void Visit(Block& b) {
            for (auto& i : b) {
                i->Accept(*this);
            }
        }

        virtual void Visit(Add& add) {
            add.lhs()->Accept(*this);
            Value lhs = ret_;
            add.rhs()->Accept(*this);
            Value rhs = ret_;

            ret_ = lhs.GetInt() + rhs.GetInt();
        }

        virtual void Visit(Decls& ds) {
            for (auto& d : ds) {
                d->expr()->Accept(*this);
                ctx_.DeclNewVar(d->var().str(), ret_);
            }
        }

        virtual void Visit(Mul& mul) {
            mul.lhs()->Accept(*this);
            Value lhs = ret_;
            mul.rhs()->Accept(*this);
            Value rhs = ret_;

            ret_ = lhs.GetInt() * rhs.GetInt();
        }

        virtual void Visit(VarSet& vs) {
            vs.expr()->Accept(*this);
            ctx_.SetVar(vs.var().str(), ret_);
        }

        virtual void Visit(ExprInstr& ei) {
            ei.expr()->Accept(*this);
        }

        virtual void Visit(IntLit& i) {
            ret_ = Value(i.value());
        }

        virtual void Visit(Print& p) {
            p.expr()->Accept(*this);
            std::cout << ret_.GetInt() << "\n";
        }

        virtual void Visit(Sub& mul) {
            mul.lhs()->Accept(*this);
            Value lhs = ret_;
            mul.rhs()->Accept(*this);
            Value rhs = ret_;

            ret_ = lhs.GetInt() - rhs.GetInt();
        }

        virtual void Visit(VarGet& vg) {
            ret_ = ctx_.GetVar(vg.name());
        }

        virtual void Visit(Instr& i) {
            ctx_.PushScope();
            if (i.where()) {
                i.where()->Accept(*this);
            }

            if (i.let()) {
                i.let()->Accept(*this);
            }

            i.body()->Accept(*this);
            ctx_.PopScope();
        }

        virtual void Visit(Binop& b) {
            b.Accept(*this);
        }
};
