#include "./Bracket.hpp"
using namespace parse;

#include "./Parser.hpp"
#include <iostream>

LBracket::LBracket() 
    : Token("(", {false, true})
{
}

void LBracket::push(const std::shared_ptr<Token>& self, Engine& e) const
{
    e.force_push_token(self);
}

void LBracket::pop(Engine& e)
{

}

RBracket::RBracket() 
    : Token(")", {false, false})
{
}

void RBracket::push(const std::shared_ptr<Token>& self, Engine& e) const
{
    while (e.has_tokens() && !e.peek_token().is_left_paren())
        e.pop_token();
    
    if (!e.has_tokens()) throw std::runtime_error{"mismatched parens"};
    e.pop_token();
}

void RBracket::pop(Engine& e)
{
}
