#include "./Token.hpp"
using namespace parse;

/*

Token

*/

Token::Token(const std::string& id, const TokenInfo& info)
    : _id { id }, _info { info }
{
}

const std::string& Token::id() const 
{
    return _id;
}

bool Token::is_left_paren() const 
{
    return _info._left_paren;
}

bool Token::is_operator() const 
{
    return _info._operator;
}