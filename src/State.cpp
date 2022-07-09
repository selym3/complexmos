#include "./State.hpp"
using namespace complexmos;

State::State() :
    modes { "color map", "circle" },
    selected_mode { std::size_t{0} }
{
}