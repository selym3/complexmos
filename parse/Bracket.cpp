#include "./Bracket.hpp"
using namespace parse;

#include "./Parser.hpp"
#include <iostream>

LBracket::LBracket() 
    : Token("(", {false, true})
{
}

bool LBracket::push(Engine& e) const
{
    return true;
}

void LBracket::pop(Engine& e)
{

}

RBracket::RBracket() 
    : Token(")", {false, false})
{
}

bool RBracket::push(Engine& e) const
{
    while (e.has_tokens() && !e.peek_token().is_left_paren())
        e.pop_token();
    
    if (!e.has_tokens()) throw std::runtime_error{"mismatched parens"};
    e.pop_token();

    return false;
}

void RBracket::pop(Engine& e)
{
}
