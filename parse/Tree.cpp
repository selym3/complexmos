#include "./Tree.hpp"
using namespace parse;

complexd BinaryNode::operator()(const complexd& z)
{
    return _op(_left(z), _right(z));
}

complexd UnaryNode::operator()(const complexd& z)
{
    return _op(_node(z));
}

complexd VariableNode::operator()(const complexd& z)
{
    return z;
}

ValueNode::operator complexd()
{
    return _value;
}

complexd ValueNode::operator()(const complexd& z)
{
    return _value;
}

// Node operator+(const Node& lhs, const Node& rhs)
// {
//     return BinaryNode{[](auto l, auto r) { return l + r; }, lhs, rhs};
// }

// Node operator-(const Node& lhs, const Node& rhs)
// {
//     return BinaryNode{[](auto l, auto r) { return l - r; }, lhs, rhs};
// }

// Node operator*(const Node& lhs, const Node& rhs)
// {
//     return BinaryNode{[](auto l, auto r) { return l * r; }, lhs, rhs};
// }

// Node operator/(const Node& lhs, const Node& rhs)
// {
//     return BinaryNode{[](auto l, auto r) { return l / r; }, lhs, rhs};
// }