#include "./Plot.hpp"
using namespace complexmos;

static double clamp(double v)
{
    return std::min(std::max(v, 0.0), 1.0);
}

#include <cmath>

Color Color::hsv(double hue, double s, double v)
{
    hue = std::fmod(hue, 360);
    s = clamp(s);
    v = clamp(v);

    if (s <= 0.0) return Color{v, v, v};

    hue /= 60.0;
    int i = static_cast<int>(hue);
    double ff = hue - i;

    double p = v * (1 - s);
    double q = v * (1 - (s * ff));
    double t = v * (1 - (s * (1.0 - ff)));

    switch (i) 
    {
        case 0:  return Color{v, t, p};
        case 1:  return Color{q, v, p};
        case 2:  return Color{p, v, t};
        case 3:  return Color{p, q, v};
        case 4:  return Color{t, p, v};
        default: return Color{v, p, q};
    };
}


Color::Color(double red, double green, double blue) :
    r { clamp(red) }, g { clamp(green) }, b { clamp(blue) }
{
}

static double get_comp(std::uint32_t hexcode, unsigned int which)
{
    return ((hexcode >> (which<<3)) & 0xFF) / 255.0;
}

Color::Color(std::uint32_t h) :
    Color( get_comp(h, 2), get_comp(h, 1), get_comp(h, 0) )
{
}

static std::uint8_t get_hex(double v)
{
    return static_cast<std::uint8_t>(v * 255);
}

std::uint8_t Color::hexred() const
{
    return get_hex(r);
}

std::uint8_t Color::hexgreen() const
{
    return get_hex(g);
}

std::uint8_t Color::hexblue() const
{
    return get_hex(b);
}

std::uint32_t Color::hexcode() const
{
    return (hexred() << 16) + (hexgreen() << 8) + hexblue();
}

Plot::Plot(std::size_t width, std::size_t height)
{
    set_size(width, height);
    fill(Color{0xFFFFFF});
}

void Plot::fill(const Plot::ColorFunction& func)
{
    for (std::size_t row = 0; row < _height; ++row)
    {
        for (std::size_t col = 0; col < _width; ++col)
        {
            const auto& color = func(col, row);

            _bytes[row * _width * 3 + col * 3 + 0] = color.hexred();
            _bytes[row * _width * 3 + col * 3 + 1] = color.hexgreen();
            _bytes[row * _width * 3 + col * 3 + 2] = color.hexblue();
        }
    }
}

void Plot::fill(const Color& color)
{
    fill([color](auto col, auto row) { return color; });
}

std::size_t Plot::width() const { return _width; }
std::size_t Plot::height() const {  return _height; }
std::pair<std::size_t, std::size_t> Plot::size() const { return { width(), height() }; }

void Plot::set_width(std::size_t w) 
{
    set_size(w, height());
}

void Plot::set_height(std::size_t h)
{
    set_size(width(), h);
}

void Plot::set_size(std::size_t w, std::size_t h)
{
    _width = w;
    _height = h;

    _bytes.resize(w * h * 3);
}

const std::vector<std::uint8_t>& Plot::bytes()
{
    return _bytes;
}