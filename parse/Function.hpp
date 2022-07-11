#ifndef __FUNCTION_HPP__
#define __FUNCTION_HPP__

#include "./Token.hpp"
#include "./Number.hpp"
#include <functional>
#include <vector>

namespace parse
{

    struct Function : public Token
    {
    public:
        using AnyFunc = std::function<Number(const std::vector<Number>&)>;
        using UnaryFunc = std::function<Number(const Number&)>;
        using BinaryFunc = std::function<Number(const Number&, const Number&)>;
        using TrinaryFunc = std::function<Number(const Number&, const Number&, const Number&)>;

    private:
        AnyFunc _func;
        std::size_t _args;

    public:
        Function(const std::string& id, const AnyFunc& func, std::size_t args);
        Function(const std::string& id, const UnaryFunc&);
        Function(const std::string& id, const BinaryFunc&);
        Function(const std::string& id, const TrinaryFunc&);

        bool push(Engine&) const;
        void pop(Engine&);
    };

}

#endif