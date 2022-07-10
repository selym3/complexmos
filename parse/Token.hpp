#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include <functional>
#include <memory>
#include "Number.hpp"

namespace parse
{
    struct Engine;

    struct TokenInfo
    {
        const bool _operator;
        const bool _left_paren;
    };

    struct Token
    {
    private:
        std::string _id;
        TokenInfo _info;

    public:
        Token(const std::string& id, const TokenInfo& info);

        virtual void push(const std::shared_ptr<Token>&, Engine&) const = 0;
        virtual void pop(Engine&) = 0;

        const std::string& id() const;

        bool is_operator() const;
        bool is_left_paren() const;
    };
}

#endif