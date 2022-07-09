#ifndef __WIDGET_HPP__
#define __WIDGET_HPP__


#include <functional>

#include "State.hpp"

namespace complexmos
{
    using Widget = std::function<void(State&)>;
}

#endif