#ifndef __VARIABLE_HPP__
#define __VARIABLE_HPP__

#include "./Token.hpp"
#include "./Number.hpp"

namespace parse
{
    struct Variable : public Token
    {
        Variable(const std::string& id);

        bool push(Engine&) const;
        void pop(Engine&);
    };

}

#endif