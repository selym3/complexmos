#ifndef __STATE_HPP__
#define __STATE_HPP__

#include <vector>
#include <string>

#include "../parse/Tree.hpp"

namespace complexmos
{
    struct State
    {
        constexpr static std::size_t DEFAULT_WIDTH = 640;
        constexpr static std::size_t DEFAULT_HEIGHT = 480;
 
        float radius;
        int points;

        float max_magnitude;

        bool new_expr;
        parse::Node node;

        State();
    };
}

#endif