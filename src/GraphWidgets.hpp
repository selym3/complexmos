#ifndef __GRAPH_WIDGETS_HPP__
#define __GRAPH_WIDGETS_HPP__

#include "State.hpp"

#include <complex>

namespace complexmos
{

    struct GraphWidget
    {
        std::vector<std::complex<double>> inputs;
        GraphWidget();

        std::complex<double> f(const std::complex<double>& z) const;
        void operator()(State& state);
    };

    struct GraphSettingsWidget
    {
        void operator()(State&);
    };

}

#endif