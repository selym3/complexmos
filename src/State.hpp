#ifndef __STATE_HPP__
#define __STATE_HPP__

#include <vector>
#include <string>

#include "../parse/Tree.hpp"

namespace complexmos
{
    struct State
    {
        const std::vector<std::string> modes;
        std::size_t selected_mode;

        float radius;
        std::size_t points;
        parse::Node node;


        State();
    };
}

#endif