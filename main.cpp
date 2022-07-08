#include <iostream>
#include "src/Engine.hpp"
using namespace complexmos;

int main(int argc, char** argv)
{
    Engine e;
    if (!e.setup()) return 1;

    std::cout << "Running engine...\n";
    while (e.is_running())
    {
        e.run();
    }
    std::cout << "Closing engine...\n";

    return 0;
}