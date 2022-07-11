#include "./Tree.hpp"
#include "./Variable.hpp"
#include "./Parser.hpp"
using namespace parse;

Variable::Variable(const std::string& id)
    : Token(id, { false, false })
{
}

void Variable::pop(Engine& e)
{
}

bool Variable::push(Engine& e) const
{
    e.push_number(VariableNode{});
    return false;
}