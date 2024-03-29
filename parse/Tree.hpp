#ifndef __TREE_HPP__
#define __TREE_HPP__

#include <functional>
#include <complex>

#include <ostream>

namespace parse
{
    using complexd = std::complex<double>;

    using Node = std::function<complexd(const complexd&)>;

    struct BinaryNode
    {
        using Op = std::function<complexd(complexd, complexd)>;
        
        Op _op;
        Node _left, _right;

        complexd operator()(const complexd& z);
    };

    struct UnaryNode
    {
        using Op = std::function<complexd(complexd)>;

        Op _op;
        Node _node;

        complexd operator()(const complexd& z);
    };

    struct VariableNode
    {
        complexd operator()(const complexd& z);
    };

    struct ValueNode
    {
        complexd _value;
        operator complexd();
        complexd operator()(const complexd& z);
    };


}

#endif