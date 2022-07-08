#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include <optional>

#include <GLFW/glfw3.h>

namespace complexmos
{

    class Engine
    {
    private:
        GLFWwindow* window;

    public:
        bool setup();
        void cleanup();

        Engine();

        void render_widgets();
    
    public:
        ~Engine();

        bool is_running() const;
        void run();
    };

}

#endif