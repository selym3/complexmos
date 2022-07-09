#include <iostream>

#include "src/Engine.hpp"
#include "src/GraphWidgets.hpp"

using namespace complexmos;

int main(int argc, char** argv)
{
    Engine e;
    if (!e.setup()) return 1;

    e.add_widget(GraphSettingsWidget{});
    e.add_widget(GraphWidget{});

    while (e.is_running())
    {
        e.run();
    }

    return 0;
}