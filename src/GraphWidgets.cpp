#include "./GraphWidgets.hpp"
using namespace complexmos;

#include "imgui.h"
#include "implot.h"
#include <iostream>

#include <cmath>
GraphWidget::GraphWidget()
{
    for (int i = 0; i < 360; ++i)
    {
        inputs.push_back(std::polar(3.0, i * M_PI / 180.0));
    }
}

std::complex<double> GraphWidget::f(const std::complex<double>& z) const
{
    return std::sin(z) * std::tan(z);
}

void GraphWidget::operator()(State& state)
{
    std::vector<double> ix, iy;
    std::vector<double> ox, oy;
    for (const auto& input : inputs)
    {
        auto output = f(input);

        // std::cout << "f(" << input << ") = ";
        ix.push_back(input.real()); 
        iy.push_back(input.imag());

        // std::cout << output << "\n";
        ox.push_back(output.real());
        oy.push_back(output.imag());
    }

    ImGui::Begin("Graph");
    if (ImPlot::BeginPlot("My Plot")) 
    {
        ImPlot::PlotLine("input", ix.data(), iy.data(), ix.size());
        ImPlot::PlotLine("output", ox.data(), oy.data(), ox.size());
        ImPlot::EndPlot();
    }

    ImGui::End();
}

void GraphSettingsWidget::operator()(State& state)
{
    ImGui::Begin("Settings");

    ImGui::ListBoxHeader("Graph Mode");
    for (std::size_t i = 0; i < state.modes.size(); ++i)
    {
        if (ImGui::Selectable(state.modes[i].c_str(), state.selected_mode == i))
        {
            state.selected_mode = i;
        }
    }
    ImGui::ListBoxFooter();


    ImGui::End();
}