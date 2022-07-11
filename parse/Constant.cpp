#include "./Constant.hpp"
#include "./Parser.hpp"
using namespace parse;

Constant::Constant(const std::string& id, const Number& value) 
    : Token(id, { false, false }), _value { value }
{
}

bool Constant::push(Engine& e) const
{
    e.push_number(_value);
    return false;
}

void Constant::pop(Engine& e) 
{
}