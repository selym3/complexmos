#ifndef __COMPLEX_HPP__
#define __COMPLEX_HPP__

#include <cmath>

#include <iostream>

namespace complexmos
{

    template <typename Number>
    struct Complex 
    {   
        constexpr static Complex cis(const Number& thetaRads)
        {
            return cis(Number{1}, thetaRads);
        }

        constexpr static Complex cis(const Number& r, const Number& thetaRads)
        {
            return Complex(r * std::cos(thetaRads), r * std::sin(thetaRads));
        }

        Number _real, _imag;

        constexpr Complex(const Number& real, const Number& imag) : 
            _real { real }, _imag { imag }
        {
        }

        constexpr Complex(const Number& real) :
            Complex(real, Number{0})
        {
        }

        constexpr Complex() :
            Complex(Number{0})
        {
        }

        inline constexpr const Number& real() const { return _real; }
        inline constexpr const Number& imag() const { return _imag; }
        
        inline constexpr Number norm() const { return real() * real() + imag() * imag(); }
        inline constexpr Number mag() const { return std::sqrt(norm()); }
        inline constexpr Number arg() const { return std::atan2(imag(), real()); }

        inline constexpr Complex conj() const { return Complex{real(), -imag()}; }

        inline constexpr Complex& operator+=(const Complex& rhs)
        {
            _real += rhs._real;
            _imag += rhs._imag;
            return *this;
        }

        inline constexpr friend Complex operator+(Complex lhs, const Complex& rhs)
        {
            return lhs += rhs;
        }

        inline constexpr Complex& operator-=(const Complex& rhs)
        {
            _real -= rhs._real;
            _imag -= rhs._imag;
            return *this;
        }

        inline constexpr friend Complex operator-(Complex lhs, const Complex& rhs)
        {
            return lhs -= rhs;
        }

        inline constexpr Complex& operator*=(const Complex& rhs)
        {
            Complex mul = (*this) * rhs;
            _real = mul._real;
            _imag = mul._imag;
            return *this;
        }

        inline constexpr friend Complex operator*(const Complex& lhs, const Complex& rhs)
        {
            return Complex
            { 
                lhs.real() * rhs.real() - lhs.imag() * rhs.imag(), 
                lhs.imag() * rhs.real() + lhs.real() * rhs.imag() 
            };
        }

        inline constexpr friend Complex operator*(const Complex& lhs, const Number& rhs)
        {
            return Complex{lhs.real() * rhs, lhs.imag() * rhs};
        }

        inline constexpr friend Complex operator*(const Number& lhs, const Complex& rhs)
        {
            return rhs * lhs;
        }

        inline constexpr Complex& operator/=(const Complex& rhs)
        {
            Complex div = (*this) / rhs;
            _real = div._real;
            _imag = div._imag;
            return *this;
        }

        inline constexpr friend Complex operator/(const Complex& lhs, const Complex& rhs)
        {
            return (lhs * rhs.conj()) / rhs.norm();
        }

        inline constexpr friend Complex operator/(const Number& lhs, const Complex& rhs)
        {
            return (lhs * rhs.conj()) / rhs.norm();
        }

        inline constexpr friend Complex operator/(const Complex& lhs, const Number& rhs)
        {
            return Complex{ lhs.real() / rhs, lhs.imag() / rhs };
        }

        Complex pow(const Number& exponent) const
        {
            auto r = std::pow(mag(), exponent);
            auto theta = arg() * exponent;

            return cis(r, theta);
        }

    };

    using Complexd = Complex<long double>;

    template <typename Number>
    std::ostream& operator<<(std::ostream& os, const Complex<Number>& rhs)
    {
        return os << "(" << rhs.real() << " + " << rhs.imag() << "i)";
    }

    Complex<long double> operator ""_i(long double imag)
    {
        return Complex<long double>(0.0, imag);
    }

    Complex<long double> operator ""_i(unsigned long long imag)
    {
        return Complex<long double>(0.0, imag);
    }

}

#endif