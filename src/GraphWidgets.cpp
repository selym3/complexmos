#include "./GraphWidgets.hpp"
using namespace complexmos;

#include "imgui.h"

void GraphWidget::operator()(State& state)
{



}


#include <iostream>
void GraphSettingsWidget::operator()(State& state)
{
    ImGui::Begin("Settings");

    ImGui::ListBoxHeader("Graph Mode");
    std::cout << state.modes.size() << std::endl;
    for (std::size_t i = 0; i < state.modes.size(); ++i)
    {
        if (ImGui::Selectable(state.modes.at(i).c_str(), state.selected_mode == i))
        {
            state.selected_mode = i;
        }
    }
    ImGui::ListBoxFooter();


    ImGui::End();
}