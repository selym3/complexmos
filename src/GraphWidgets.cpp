#include "./GraphWidgets.hpp"
using namespace complexmos;

#include "imgui.h"
#include "implot.h"
#include <iostream>

#include <cmath>

#include <iostream>
#include <GLFW/glfw3.h>

#include <memory>
#include "../parse/Tokens.hpp"

void GraphWidget::operator()(State &state)
{
    std::vector<double> ix, iy;
    std::vector<double> ox, oy;
    for (double theta = 0, n = 360.0 / state.points; theta < 360; theta += n)
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

ColorPlotWidget::ColorPlotWidget() :
    _plot { State::DEFAULT_WIDTH, State::DEFAULT_HEIGHT }
{
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

ColorPlotWidget::~ColorPlotWidget()
{
    // TODO: delete texture?
}

void ColorPlotWidget::save_plot()
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _plot.width(), _plot.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _plot.bytes().data());
}

#include <cstdio>

void ColorPlotWidget::operator()(State &state)
{
    ImGui::Begin("Color Plot");

    if (state.new_expr)
    {
        _plot.fill([this, &state](std::size_t col, std::size_t row) { 
            double ux = (col / static_cast<double>(_plot.width())) - 0.5;
            double uy = (row / static_cast<double>(_plot.height())) - 0.5;

            std::complex<double> z = { ux, uy };
            std::complex<double> fz = state.node(z);

            double mag = std::abs(fz);
            double radians = std::arg(fz);
            double degrees = (radians / M_PI) * 180 + 180;

            return Color::hsv(degrees, 1.0, mag);
        });

        save_plot();
    }

    ImGui::Image((void *)(intptr_t)_texture, ImVec2(_plot.width(), _plot.height()));

    ImGui::End();
}

GraphSettingsWidget::GraphSettingsWidget() : _token_table{
                                                 std::make_shared<parse::LBracket>(),
                                                 std::make_shared<parse::RBracket>(),

                                                 std::make_shared<parse::Operator>(
                                                     "+",
                                                     [](const parse::Number &l, const parse::Number &r)
                                                     {
                                                         return parse::BinaryNode{[](auto a, auto b)
                                                                                  { return a + b; },
                                                                                  l, r};
                                                     },
                                                     1,
                                                     parse::Operator::Assoc::LEFT),

                                                 std::make_shared<parse::Operator>(
                                                     "-",
                                                     [](const parse::Number &l, const parse::Number &r)
                                                     {
                                                         return parse::BinaryNode{[](auto a, auto b)
                                                                                  { return a - b; },
                                                                                  l, r};
                                                     },
                                                     1,
                                                     parse::Operator::Assoc::LEFT),

                                                 std::make_shared<parse::Operator>(
                                                     "*",
                                                     [](const parse::Number &l, const parse::Number &r)
                                                     {
                                                         return parse::BinaryNode{[](auto a, auto b)
                                                                                  { return a * b; },
                                                                                  l, r};
                                                     },
                                                     1,
                                                     parse::Operator::Assoc::LEFT),

                                                 std::make_shared<parse::Operator>(
                                                     "/",
                                                     [](const parse::Number &l, const parse::Number &r)
                                                     {
                                                         return parse::BinaryNode{[](auto a, auto b)
                                                                                  { return a / b; },
                                                                                  l, r};
                                                     },
                                                     1,
                                                     parse::Operator::Assoc::LEFT),

                                                 std::make_shared<parse::Operator>(
                                                     "^",
                                                     [](const parse::Number &l, const parse::Number &r)
                                                     {
                                                         return parse::BinaryNode{[](auto a, auto b)
                                                                                  { return std::pow(a, b); },
                                                                                  l, r};
                                                     },
                                                     2,
                                                     parse::Operator::Assoc::RIGHT),

                                                 std::make_shared<parse::Function>(
                                                     "sin",
                                                     [](const parse::Number &z)
                                                     { return parse::UnaryNode{[](auto a)
                                                                               { return std::sin(a); },
                                                                               z}; }),

                                                 std::make_shared<parse::Function>(
                                                     "cos",
                                                     [](const parse::Number &z)
                                                     { return parse::UnaryNode{[](auto a)
                                                                               { return std::cos(a); },
                                                                               z}; }),

                                                 std::make_shared<parse::Function>(
                                                     "log",
                                                     [](const parse::Number &z)
                                                     { return parse::UnaryNode{[](auto a)
                                                                               { return std::log(a); },
                                                                               z}; }),

                                                 std::make_shared<parse::Variable>("z"),
                                                 std::make_shared<parse::Constant>("e", parse::ValueNode{2.7182818284590452353602874713526624977572}),
                                                 std::make_shared<parse::Constant>("pi", parse::ValueNode{3.1415926535897932384626433832795028841972}),
                                             },
                                             _to_complex{[](double real, double imag)
                                                         {
                                                             return parse::ValueNode{std::complex<double>{real, imag}};
                                                         }},
                                             function_text{"z"}
{
}

parse::Node GraphSettingsWidget::parse(const std::string &text) const
{
    return parse::Parser::parse(text, _to_complex, _token_table);
}

void GraphSettingsWidget::operator()(State &state)
{
    ImGui::Begin("Settings");
    ImGui::SliderFloat("radius", &state.radius, 0, 25);

    ImGui::InputText("f(z) = ", function_text, IM_ARRAYSIZE(function_text));

    if ((state.new_expr = ImGui::Button("Graph")))
    {
        try
        {
            state.node = parse(function_text);
        }
        catch (const std::runtime_error &error)
        {
            std::cout << "TODO: log error in menu here" << std::endl;
        }
    }

    ImGui::End();
}