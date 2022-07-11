#include "./Function.hpp"
#include "./Number.hpp"
#include "./Parser.hpp"
using namespace parse;

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
        [&func](const std::vector<Number>& v) -> Number { return func(v[0], v[1]); }, 
        2
    )
{
}

Function::Function(const std::string& id, const TrinaryFunc& func)
    : Function(
        id, 
        [&func](const std::vector<Number>& v) -> Number { return func(v[0], v[1], v[2]); }, 
        3
    )
{
}

bool Function::push(Engine& e) const
{
    std::cout << "pushing: " << std::endl;
    return true;
}

void Function::pop(Engine& e)
{
    if (e.count_numbers() < _args)
        throw std::runtime_error{"not enough arguments for function"};

    std::vector<Number> parameters;
    // parameters.reserve(_args);
    // parameters.resize(_args); 

    // for (std::size_t i = 0; i < _args; ++i)
    // {
    //     parameters.at(_args - i - 1) = e.pop_number();
    // }

    std::cout << "am i here?" << std::endl;

    for (std::size_t i = 0; i < _args; ++i)
    {
        parameters.push_back(e.pop_number());
    }
    std::cout << "am i here2?" << std::endl;
    
    std::cout << "hello: " << std::endl << _func(parameters)(0.0) << std::endl;
    e.push_number(_func(parameters));
}