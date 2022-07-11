#ifndef __CONSTANTS_HPP__
#define __CONSTANTS_HPP__

#include "./Token.hpp"
#include "./Number.hpp"

namespace parse
{
    struct Constant : public Token
    {
        Number _value;

        Constant(const std::string& id, const Number& value);

        bool push(Engine&) const;
        void pop(Engine&);
    };
}

#endif