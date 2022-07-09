#ifndef __GRAPH_WIDGETS_HPP__
#define __GRAPH_WIDGETS_HPP__

#include "State.hpp"

namespace complexmos
{

    struct GraphWidget
    {
        void operator()(State& state);
    };

    struct GraphSettingsWidget
    {
        void operator()(State&);
    };

}

#endif