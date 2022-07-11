#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

#include <functional>
#include <string>
#include <memory>

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

        // function that runs before a token is pushed that allows the 
        // token to handle precedence and returns a boolean if it should
        // be pushed at all
        virtual bool push(Engine&) const = 0;
        
        // function that runs before a token is removed from the token stack
        virtual void pop(Engine&) = 0;

        const std::string& id() const;

        bool is_operator() const;
        bool is_left_paren() const;
    };
}

#endif