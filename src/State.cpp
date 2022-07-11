#include "./State.hpp"
using namespace complexmos;

State::State() :
    modes { "color map", "circle" },
    selected_mode { std::size_t{0} },
    radius { 1.0 },
    points {360},
    node { parse::VariableNode{} }
{
}