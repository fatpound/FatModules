module;

export module FatPound.Math.Geometry;

import FatPound.Math.Multiplicative;
import FatPound.Math.Numbers.Common;

import FatPound.Bitwise.Concepts;

import std;

export namespace fatpound::math::inline geometry
{
    template <bitwise::UIntegralOrFloating T> constexpr auto SquarePerimeter   (const T& length) -> T
    {
        return length * 4;
    }
    template <bitwise::UIntegralOrFloating T> constexpr auto SquareArea        (const T& length) noexcept(Squarable_NX<T>) -> T
    {
        return Square<>(length);
    }
    template <bitwise::UIntegralOrFloating T> constexpr auto CirclePerimeter   (const T& radius) -> T
    {
        return radius * numbers::twoPi<T>;
    }
    template <bitwise::UIntegralOrFloating T> constexpr auto CircleArea        (const T& radius) -> T
    {
        return Square<>(radius) * numbers::Pi<T>;
    }
    template <bitwise::UIntegralOrFloating T> constexpr auto TrianglePerimeter (const T& a, const T& b, const T& c) -> T
    {
        return a + b + c;
    }
    template <bitwise::UIntegralOrFloating T> constexpr auto TriangleArea      (const T& a, const T& b, const T& c) -> T
    {
        const auto s = TrianglePerimeter<>(a, b, c) / static_cast<T>(2);

        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
    template <bitwise::UIntegralOrFloating T> constexpr auto TriangleArea      (const T& height, const T& base) -> T
    {
        return (base * height) / 2.0;
    }
}

module : private;
