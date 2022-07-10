#ifndef __BRACKET_HPP__
#define __BRACKET_HPP__

#include "./Token.hpp"

namespace parse
{
    struct LBracket : public Token
    {
        LBracket();
        void push(const std::shared_ptr<Token>&, Engine&) const;
        void pop(Engine&);
    };

    struct RBracket : public Token
    {
        RBracket();
        void push(const std::shared_ptr<Token>&, Engine&) const;
        void pop(Engine&);
    };
}

#endif