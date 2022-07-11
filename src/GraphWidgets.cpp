#include "./GraphWidgets.hpp"
using namespace complexmos;

#include "imgui.h"
#include "implot.h"
#include <iostream>

#include <cmath>


#include <memory>
// TODO: package these together Tokens.hpp
#include "../parse/Operator.hpp"
#include "../parse/Variable.hpp"
#include "../parse/Function.hpp"
#include "../parse/Constant.hpp"
#include "../parse/Bracket.hpp"

void GraphWidget::operator()(State& state)
{
    std::vector<double> ix, iy;
    std::vector<double> ox, oy;
    for (double theta = 0, n = 360.0 / state.points; theta < 360; theta+=n)
    {
        std::complex<double> input = std::polar(static_cast<double>(state.radius), theta * M_PI / 180.0);
        // std::cout << input << " " << theta << " " << (theta * M_PI / 180.0 ) << " " << n << std::endl;

        auto output = state.node(input);

        // std::cout << "f(" << input << ") = ";
        ix.push_back(input.real()); 
        iy.push_back(input.imag());

        // std::cout << output << "\n";
        ox.push_back(output.real());
        oy.push_back(output.imag());
    }

    ImGui::Begin("Graph");

    // TODO: put function (GraphSettingsWidget::function_text) inside of here
    if (ImPlot::BeginPlot("My Plot", ImVec2(-1, -1))) 
    {
        ImPlot::PlotLine("input", ix.data(), iy.data(), ix.size());
        ImPlot::PlotLine("output", ox.data(), oy.data(), ox.size());
        ImPlot::EndPlot();
    }

    ImGui::End();
}

GraphSettingsWidget::GraphSettingsWidget() :
    _token_table
    {
        std::make_shared<parse::LBracket>(),
        std::make_shared<parse::RBracket>(),
        
        std::make_shared<parse::Operator>(
            "*", 
            [](const parse::Number& l, const parse::Number& r) {
                return parse::BinaryNode{[](auto a, auto b) { return a * b; }, l, r};
            },
            1, 
            parse::Operator::Assoc::LEFT
        ),

        std::make_shared<parse::Operator>(
            "^", 
            [](const parse::Number& l, const parse::Number& r) {
                return parse::BinaryNode{[](auto a, auto b) { return std::pow(a, b); }, l, r};
            }, 
            2, 
            parse::Operator::Assoc::RIGHT
        ),

        std::make_shared<parse::Function>(
            "sin", 
            [](const parse::Number& z) { return parse::UnaryNode{[](auto a){ return std::sin(a); }, z}; }
        ),

        std::make_shared<parse::Function>(
            "cos", 
            [](const parse::Number& z) { return parse::UnaryNode{[](auto a){ return std::cos(a); }, z}; }
        ),

        std::make_shared<parse::Function>(
            "log", 
            [](const parse::Number& z) { return parse::UnaryNode{[](auto a){ return std::log(a); }, z}; }
        ),

        std::make_shared<parse::Variable>("z"),
        std::make_shared<parse::Constant>("e", parse::ValueNode{2.7182818284590452353602874713526624977572}),
        std::make_shared<parse::Constant>("pi", parse::ValueNode{3.1415926535897932384626433832795028841972}),
    },
    _to_complex 
    {  
        [](double real, double imag) 
        { 
            return parse::ValueNode{std::complex<double>{real, imag}}; 
        }
    },
    function_text { "z" }
{

}

parse::Node GraphSettingsWidget::parse(const std::string& text) const
{
    return parse::Parser::parse(text, _to_complex, _token_table);
}

void GraphSettingsWidget::operator()(State& state)
{
    ImGui::Begin("Settings");

    // if (ImGui::ListBoxHeader("Graph Mode")) 
    // {
        // for (std::size_t i = 0; i < state.modes.size(); ++i)
        // {
        //     if (ImGui::Selectable(state.modes[i].c_str(), state.selected_mode == i))
        //     {
        //         state.selected_mode = i;
        //     }
        // }

        
        // ImGui::ListBoxFooter();
    // }

    ImGui::SliderFloat("radius", &state.radius, 0, 25);
    
    if (ImGui::InputText("f(z) = ", function_text, IM_ARRAYSIZE(function_text)))
    {
        // std::cout << function_text << std::endl;
        // state.node = function_text;
    }

    if (ImGui::Button("Graph"))
    {
        try {
            state.node = parse(function_text);
        } catch (const std::runtime_error& error)
        {
            std::cout << "TODO: log error in menu here" << std::endl; 
        }
    }

    ImGui::End();
}