#pragma once

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
                d->Accept(*this);
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
            if (i.where()) {
                i.where()->Accept(*this);
            }

            if (i.let()) {
                i.let()->Accept(*this);
            }

            i.body()->Accept(*this);
        }

        virtual void Visit(Binop& b) {
            b.Accept(*this);
        }
};
