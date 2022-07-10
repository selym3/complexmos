#include "./Operator.hpp"
using namespace parse;

#include "./Parser.hpp"

#include <iostream>


Operator::Operator(const std::string& id, const Eval& eval, Prec prec, Assoc assoc)
    : Token(id, {true, false}), _eval { eval }, _prec { prec }, _assoc { assoc }
{
}

bool Operator::push(Engine& e) const
{
    while (e.has_tokens())
    {
        const auto& token = e.peek_token();
        if (token.is_left_paren() || !token.is_operator())
            break;

        if (const Operator* op = dynamic_cast<const Operator*>(&token))
        {
            if (op->_prec > _prec) e.pop_token();
            else if (op->_prec == _prec && op->_assoc == Assoc::LEFT) e.pop_token();
            else break;
        }
    }

    return true;
}

void Operator::pop(Engine& e)
{
    if (e.count_numbers() < 2)
        throw std::runtime_error{"not enough arguments for operator"};
    auto r = e.pop_number();
    auto l = e.pop_number();

    e.push_number(_eval(l, r));
}
