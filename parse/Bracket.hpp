#ifndef __BRACKET_HPP__
#define __BRACKET_HPP__

#include "./Token.hpp"

namespace parse
{
    struct LBracket : public Token
    {
        LBracket();
        bool push(Engine&) const;
        void pop(Engine&);
    };

    struct RBracket : public Token
    {
        RBracket();
        bool push(Engine&) const;
        void pop(Engine&);
    };
}

#endif