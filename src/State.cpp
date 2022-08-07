#include "./State.hpp"
using namespace complexmos;

State::State() :
    radius { 1.0 },
    points {360},
    max_magnitude { 1.0 },
    new_expr { false },
    node { parse::VariableNode{} }
{
}