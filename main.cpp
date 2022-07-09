#include <iostream>

#include "src/Engine.hpp"
#include "src/Widgets.hpp"

using namespace complexmos;

int main(int argc, char** argv)
{
    Engine e;
    if (!e.setup()) return 1;

    e.add_widget(TestWidget{});
    e.add_widget(OtherWidget{});

    while (e.is_running())
    {
        e.run();
    }

    return 0;
}