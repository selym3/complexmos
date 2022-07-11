#include "./Tree.hpp"

namespace parse{
Node operator+(const Node& lhs, const Node& rhs)
{
    return BinaryNode{[](complexd l, complexd r) -> complexd { return l + r; }, lhs, rhs};
}

Node operator-(const Node& lhs, const Node& rhs)
{
    return BinaryNode{[](auto l, auto r) { return l - r; }, lhs, rhs};
}

Node operator*(const Node& lhs, const Node& rhs)
{
    return BinaryNode{[](auto l, auto r) { return l * r; }, lhs, rhs};
}

Node operator/(const Node& lhs, const Node& rhs)
{
    return BinaryNode{[](auto l, auto r) { return l / r; }, lhs, rhs};
}
}

#include "./Parser.hpp"
#include "./Operator.hpp"
#include "./Bracket.hpp"
#include "./Function.hpp"
#include "./Variable.hpp"
#include "./Constant.hpp"

using namespace parse;

#include <iostream>

void write_complex(std::ostream& os, const std::complex<double>& rhs)
{
    auto print_real = [&os](auto real) {
        if (real != 0) os << real;
    };

    auto print_imag = [&os](auto imag) {
        if (imag == 0) return;
        
        if (imag < 0) os << " - " << -imag << "i";
        else          os << " + " << +imag << "i";
    };

    if (rhs.real() == 0.0 && rhs.imag() == 0.0) 
    {
        os << "0.0";
        return;
    }

    print_real(rhs.real());
    print_imag(rhs.imag());
}

int main(int argc, char** argv)
{

    auto ans = Parser::parse(
        argv[1],
        
        [](double real, double imag) 
        { 
            return ValueNode{std::complex<double>{real, imag}}; 
        },

        {
            std::make_shared<LBracket>(),
            std::make_shared<RBracket>(),

            std::make_shared<Operator>("+", [](auto l, auto r) { return l + r;}, 0, Operator::Assoc::LEFT),
            std::make_shared<Operator>("-", [](auto l, auto r) { return l - r;}, 0, Operator::Assoc::LEFT),
            std::make_shared<Operator>("*", [](auto l, auto r) { return l * r;}, 1, Operator::Assoc::LEFT),
            std::make_shared<Operator>("/", [](auto l, auto r) { return l / r;}, 1, Operator::Assoc::LEFT),

            std::make_shared<Operator>(
                "^", 
                [](const Number& l, const Number& r) {
                    return BinaryNode{[](complexd a, complexd b) -> complexd { return std::pow(a, b); }, l, r};
                }, 
                2, 
                Operator::Assoc::RIGHT
            ),

            std::make_shared<Function>(
                "sin", 
                [](const Number& z) { return UnaryNode{[](auto a){ return std::sin(a); }, z}; }
            ),

            std::make_shared<Function>(
                "cos", 
                [](const Number& z) { return UnaryNode{[](auto a){ return std::cos(a); }, z}; }
            ),

            std::make_shared<Function>(
                "log", 
                [](const Number& z) { return UnaryNode{[](auto a){ return std::log(a); }, z}; }
            ),

            std::make_shared<Function>(
                "first", 
                [](const Number& a, const Number& b) { return a; }
            ),

            std::make_shared<Function>(
                "second", 
                [](const Number& a, const Number& b) { return b; }
            ),

            std::make_shared<Variable>("z"),
            std::make_shared<Constant>("e", ValueNode{2.7182818284590452353602874713526624977572}),
            std::make_shared<Constant>("pi", ValueNode{3.1415926535897932384626433832795028841972}),
        }
    );
    write_complex(std::cout, ans(0.0));
    std::cout << std::endl;

    return 0;
}