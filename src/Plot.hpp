#ifndef __PLOT_HPP__
#define __PLOT_HPP__

#include <cstdint>
#include <vector>
#include <utility>
#include <functional>

namespace complexmos
{

struct Color
{
    static Color hsv(double hue, double s, double v);

    const double r, g, b;

    Color(double red, double green, double blue);
    Color(std::uint32_t hexcode);

    std::uint32_t hexcode() const;
    std::uint8_t hexred() const;
    std::uint8_t hexgreen() const;
    std::uint8_t hexblue() const;
};

struct Plot
{
public:
    Plot(std::size_t width, std::size_t height);

    using ColorFunction = std::function<Color(std::size_t, std::size_t)>;
    void fill(const ColorFunction& func);
    void fill(const Color& color);

public:
    std::size_t width() const;
    std::size_t height() const;
    std::pair<std::size_t, std::size_t> size() const;

    void set_width(std::size_t);
    void set_height(std::size_t);
    void set_size(std::size_t width, std::size_t height);

    const std::vector<std::uint8_t>& bytes();

private:
    std::size_t _width, _height;
    std::vector<std::uint8_t> _bytes;
};



}

#endif