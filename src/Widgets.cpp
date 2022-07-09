#include "./Widgets.hpp"
using namespace complexmos;

#include "imgui.h"
#include "implot.h"

TestWidget::TestWidget()
{
    for (int i = 0; i < 1000; ++i) x_data[i] = -3.14 + 6.28f / i;
    for (int i = 0; i < 1000; ++i) y_data[i] = x_data[i] - (x_data[i] * x_data[i] * x_data[i]) / 6;
}

void TestWidget::operator()(State& state)
{
    ImGui::Begin("Plot");
    if (ImPlot::BeginPlot("My Plot")) 
    {
        ImPlot::PlotLine("My Line Plot", x_data, y_data, 1000);
        ImPlot::EndPlot();
    }
    ImGui::End();
}

void OtherWidget::operator()(State& state)
// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
{
    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    // ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    // ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    // ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
