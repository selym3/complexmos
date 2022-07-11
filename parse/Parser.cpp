#include "./Parser.hpp"
using namespace parse;

#include <ctype.h>
#include <stdexcept>

#include <iostream>

/*

Engine

*/

Engine::Engine()
    : _numbers{}
{
}

void Engine::push_number(const Number &number)
{
    _numbers.push_back(number);
}

Number Engine::pop_number()
{
    auto tmp = peek_number();
    _numbers.pop_back();
    return tmp;
}

const Number &Engine::peek_number() const
{
    return _numbers.at(_numbers.size() - 1);
}

std::size_t Engine::count_numbers() const
{
    return _numbers.size();
}

bool Engine::has_numbers() const
{
    return count_numbers() > 0;
}

const Token &Engine::peek_token() const
{
    return *_tokens.at(_tokens.size() - 1);
}

std::size_t Engine::count_tokens() const
{
    return _tokens.size();
}

bool Engine::has_tokens() const
{
    return count_tokens() > 0;
}

void Engine::force_push_token(const std::shared_ptr<Token>& token)
{
    _tokens.push_back(token);
}

void Engine::push_token(const std::shared_ptr<Token> &token)
{
    if (token->push(*this))
        _tokens.push_back(token);
}

void Engine::pop_token()
{
    if (!has_tokens())
        throw std::runtime_error{"trying to pop token when no tokens exist"};
    auto &token = _tokens.back();
    token->pop(*this);
    _tokens.pop_back();
}

/*

Parser

*/

Number Parser::parse(const std::string &str, const MakeNumber& make, const TokenTable &tokens)
{
    Parser p{str};
    Engine e;
    p.parse(e, make, tokens);
    while (e.has_tokens())
        e.pop_token();
    if (e.count_numbers() != 1)
        throw std::runtime_error{"engine left with more than 1 answer, malformed expression"};
    return e.peek_number();
}

Parser::Parser(const std::string &str) : _str{str}, _top{0}
{
}

bool Parser::has_char() const
{
    return _top < _str.size();
}

bool Parser::has_next() const
{
    return _top + 1 < _str.size();
}

char Parser::peek() const
{
    return _str.at(_top);
}

char Parser::peek_next() const
{
    return _str.at(_top + 1);
}

bool Parser::is_digit(char c) const
{
    return (std::isdigit(c) != 0);
}

void Parser::parse(Engine &engine, const MakeNumber& make, const TokenTable &tokens)
{
    while (has_char())
        parse_next(engine, make, tokens);
}

void Parser::parse_next(Engine &engine, const MakeNumber& make, const TokenTable &tokens)
{
    if (std::isblank(peek()) || std::isblank(peek()))
    {
        advance();
    }
    else if (std::isdigit(peek()) || peek() == '.' || peek() == 'i')
    {
        auto n = parse_number(make);
        // std::cout << "Parsed number: " << n << std::endl;
        engine.push_number(n);
    }
    else
    {
        const auto &token = parse_token(tokens);
        // std::cout << "Found token: " << token->id() << std::endl;
        engine.push_token(token);
    }

    // std::cout << "[";
    // for (const auto& n : engine._numbers)
    //     std::cout << n << " ";
    // std::cout << "]" << std::endl;

    // advance();
}

Number Parser::parse_number(const MakeNumber& make)
{
    bool reached_decimal = false;
    int number_top = _top;
    // std::cout << "Looking: ";
    while (has_char() && (std::isdigit(peek()) || peek() == '.'))
    {
        // std::cout << peek() << std::endl;
        if (peek() == '.')
        {
            if (reached_decimal)
                throw std::runtime_error("malformed number: already reached decimal point");

            reached_decimal = true;
        }
        advance();
        // std::cout << "remaining: " << has_char() << std::endl;
    }
    // std::cout << " Done looking\n";

    // std::cout << value;

    std::string number_str = _str.substr(number_top, _top - number_top);
    double value = (number_str.size() < 1) ? 1.0 : std::stod(number_str);

    if (has_char() && peek() == 'i')
    {
        advance();
        return make(0.0, value);
    }
    else
    {
        return make(value, 0.0);
    }
    // std::cout << std::endl;
}

const std::shared_ptr<Token> &Parser::parse_token(const TokenTable &tokens)
{

    const std::shared_ptr<Token> *best_match = nullptr;
    for (const auto &token : tokens)
    {
        bool is_longer = best_match == nullptr || token->id().size() > (*best_match)->id().size();
        bool is_better = is_longer && (token->id() == _str.substr(_top, token->id().size()));
        if (is_better)
            best_match = &token;
    }

    if (best_match == nullptr)
        throw std::runtime_error{"malformed token, cannot find match"};

    _top += (*best_match)->id().size();
    return *best_match;
}

void Parser::advance()
{
    _top++;
    // if (is_empty())
}