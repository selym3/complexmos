#include "./Parser.hpp"
#include "./Operator.hpp"
#include "./Bracket.hpp"

using namespace parse;

#include <iostream>

int main(int argc, char** argv)
{

    auto ans = Parser::parse(
        argv[1], 
        {
            std::make_shared<LBracket>(),
            std::make_shared<RBracket>(),

            std::make_shared<Operator>("+", [](auto l, auto r) { return l + r; }, 0, Operator::Assoc::LEFT),
            std::make_shared<Operator>("-", [](auto l, auto r) { return l - r; }, 0, Operator::Assoc::LEFT),
            std::make_shared<Operator>("*", [](auto l, auto r) { return l * r; }, 1, Operator::Assoc::LEFT),
            std::make_shared<Operator>("/", [](auto l, auto r) { return l / r; }, 1, Operator::Assoc::LEFT),

            std::make_shared<Operator>("^", [](auto l, auto r) { return std::pow(l, r); }, 2, Operator::Assoc::RIGHT),
        }
    );
    std::cout << ans << std::endl;

    // Parser p { ".14" };
    // p.parse();

    return 0;
}