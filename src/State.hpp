#ifndef __STATE_HPP__
#define __STATE_HPP__

#include <vector>
#include <string>

namespace complexmos
{
    struct State
    {
        const std::vector<std::string> modes;
        std::size_t selected_mode;

        State();
    };
}

#endif