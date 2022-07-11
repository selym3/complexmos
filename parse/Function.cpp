#include "./Function.hpp"
#include "./Number.hpp"
#include "./Parser.hpp"
using namespace parse;

#include <algorithm>
#include <iostream>

Function::Function(const std::string& id, const AnyFunc& func, std::size_t args)
    : Token(id, { false, false }), _func { func }, _args { args }
{
}

Function::Function(const std::string& id, const UnaryFunc& func)
    : Function(
        id, 
        [func](const std::vector<Number>& v) -> Number { return func(v[0]); }, 
        1
    )
{
}

Function::Function(const std::string& id, const BinaryFunc& func)
    : Function(
        id, 
        [func](const std::vector<Number>& v) -> Number { return func(v[0], v[1]); }, 
        2
    )
{
}

Function::Function(const std::string& id, const TrinaryFunc& func)
    : Function(
        id, 
        [func](const std::vector<Number>& v) -> Number { return func(v[0], v[1], v[2]); }, 
        3
    )
{
}

bool Function::push(Engine& e) const
{
    return true;
}

void Function::pop(Engine& e)
{
    if (e.count_numbers() < _args)
        throw std::runtime_error{"not enough arguments for function"};

    std::vector<Number> parameters;

    for (std::size_t i = 0; i < _args; ++i)
        parameters.push_back(e.pop_number());
    std::reverse(parameters.begin(), parameters.end());
    e.push_number(_func(parameters));
}