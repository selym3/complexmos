#ifndef __STATE_HPP__
#define __STATE_HPP__

#include <functional>

namespace complexmos
{
    class State
    {

    };

    using Widget = std::function<void(State&)>;
}

#endif