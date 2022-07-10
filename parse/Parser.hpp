#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include <vector>
#include "Number.hpp"
#include "Token.hpp"

#include <memory>

namespace parse
{
    struct Engine
    {
        std::vector<Number> _numbers;
        std::vector<std::shared_ptr<Token>> _tokens;

        Engine();

        const Number& peek_number() const;
        std::size_t count_numbers() const;
        bool has_numbers() const;
        void push_number(const Number& number);
        Number pop_number();

        const Token& peek_token() const;
        std::size_t count_tokens() const;
        bool has_tokens() const;
        void push_token(const std::shared_ptr<Token>& token);
        void force_push_token(const std::shared_ptr<Token>& token);
        void pop_token();
    };

    class Parser
    {
    public:
        using TokenTable = std::vector<std::shared_ptr<Token>>;
        static Number parse(const std::string& str, const TokenTable& tokens);

    private:
        std::string _str;
        std::size_t _top;

        Parser(const std::string& str);

        bool has_char() const;
        bool has_next() const;
        
        char peek() const;
        char peek_next() const;

        bool is_digit(char c) const;

        void parse(Engine& engine, const TokenTable&);
        void parse_next(Engine& engine, const TokenTable&);

        Number parse_number();
        const std::shared_ptr<Token>& parse_token(const TokenTable&);

        void advance();
    };

}

#endif