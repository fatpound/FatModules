module;

export module FatPound.Math.Geometry;

import FatPound.Math.Multiplicative;
import FatPound.Math.Numbers;

import std;

export namespace fatpound::math::geometry
{
    template <numbers::Rational Q>
    constexpr auto SquareArea(const Q length) noexcept(Squarable_NX<Q>) -> Q
    {
        return Square<>(length);
    }

    template <numbers::Rational Q>
    constexpr auto SquarePerimeter(const Q length) -> Q
    {
        return length * 4;
    }

    template <numbers::Rational Q>
    constexpr auto CircleArea(const Q radius) -> Q
    {
        return Square<>(radius) * ::std::numbers::pi_v<Q>;
    }

    template <numbers::Rational Q>
    constexpr auto CirclePerimeter(const Q radius) -> Q
    {
        return radius * numbers::twoPi<Q>;
    }

    template <numbers::Rational Q>
    constexpr auto TrianglePerimeter(const Q a, const Q b, const Q c) -> Q
    {
        return a + b + c;
    }

    template <numbers::Rational Q>
    constexpr auto TriangleArea(const Q a, const Q b, const Q c) -> Q
    {
        const auto s = TrianglePerimeter<>(a, b, c) / static_cast<Q>(2);

        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }

    template <numbers::Rational Q>
    constexpr auto TriangleArea(const Q height, const Q base) -> Q
    {
        return (base * height) / 2;
    }
}

module : private;