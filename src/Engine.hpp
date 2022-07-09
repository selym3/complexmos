#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <optional>

#include <GLFW/glfw3.h>
#include <vector>

#include "Widget.hpp"

namespace complexmos
{

    class Engine
    {
    private:
        GLFWwindow* window;

        State state;
        std::vector<Widget> widgets;

    private:
        void cleanup();
        void render_widgets();
    public:
        bool setup();

        Engine();

        void add_widget(Widget w);
    public:
        ~Engine();

        bool is_running() const;
        void run();
    };

}

#endif