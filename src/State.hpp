#ifndef __STATE_HPP__
#define __STATE_HPP__

#include <vector>
#include <string>

#include "../parse/Tree.hpp"

namespace complexmos
{
    struct State
    {
        constexpr static std::size_t DEFAULT_WIDTH = 300;
        constexpr static std::size_t DEFAULT_HEIGHT = 300;
 
        const std::vector<std::string> modes;
        std::size_t selected_mode;

        float radius;
        std::size_t points;

        bool new_expr;
        parse::Node node;

        // double min_x, max_x;
        // double min_y, max_y;

        State();
    };
}

#endif