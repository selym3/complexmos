#ifndef __OPERATOR_HPP__
#define __OPERATOR_HPP__

#include "Number.hpp"
#include "Token.hpp"

#include <functional>
#include <memory>

namespace parse
{
    struct Operator : public Token
    {
    public:
        enum Assoc { LEFT, RIGHT };
        using Prec  = std::size_t;
        
        using Eval = std::function<Number(const Number&, const Number&)>;

    private:
        Assoc _assoc;
        Prec _prec;

        Eval _eval;

    public:
        Operator(const std::string& id, const Eval& eval, Prec prec, Assoc assoc);

        bool push(Engine& e) const override;
        void pop(Engine& e) override;
    };
}

#endif