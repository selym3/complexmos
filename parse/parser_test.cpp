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
            std::make_shared<Operator>("*", [](auto l, auto r) { return l * r;}, 0, Operator::Assoc::LEFT),
            std::make_shared<Operator>("/", [](auto l, auto r) { return l / r;}, 0, Operator::Assoc::LEFT),
        }
    );
    std::cout << ans(0.0) << std::endl;

    // std::make_shared<Operator>("-", [](auto l, auto r) { return l - r; }, 0, Operator::Assoc::LEFT),
    // std::make_shared<Operator>("*", [](auto l, auto r) { return l * r; }, 1, Operator::Assoc::LEFT),
    // std::make_shared<Operator>("/", [](auto l, auto r) { return l / r; }, 1, Operator::Assoc::LEFT),

    // std::make_shared<Operator>("^", [](auto l, auto r) { return std::pow(l, r); }, 2, Operator::Assoc::RIGHT),

    // Parser p { ".14" };
    // p.parse();

    return 0;
}