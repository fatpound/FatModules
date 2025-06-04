module;

#include <FatSTL_Macros.hxx>

export module FatPound.Math.Geometry.Common;

import FatPound.Math.Multiplicative;
import FatPound.Math.Numbers.Common;
import FatPound.Traits.Bitwise;

import std;

export namespace fatpound::math::geometry
{
    template <traits::UIntegralOrFloating T> constexpr auto SquarePerimeter   (const T& length) -> T
    {
        return length * static_cast<T>(4);
    }
    template <traits::UIntegralOrFloating T> constexpr auto SquareArea        (const T& length) noexcept(Squarable_NX<T>) -> T
    {
        return Square<>(length);
    }
    template <traits::UIntegralOrFloating T> constexpr auto CircleDiameter    (const T& radius) -> T
    {
        return radius * static_cast<T>(2);
    }
    template <traits::UIntegralOrFloating T> constexpr auto CirclePerimeter   (const T& radius) -> T
    {
        return CircleDiameter<T>(radius) * numbers::Pi<T>;
    }
    template <traits::UIntegralOrFloating T> constexpr auto CircleArea        (const T& radius) -> T
    {
        return Square<>(radius) * numbers::Pi<T>;
    }
    template <traits::UIntegralOrFloating T> constexpr auto TrianglePerimeter (const T& a, const T& b, const T& c) -> T
    {
        return a + b + c;
    }
    template <traits::UIntegralOrFloating T> CX_MATH26 auto TriangleArea      (const T& a, const T& b, const T& c) -> T
    {
        const auto s = TrianglePerimeter<>(a, b, c) / static_cast<T>(2);

        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
    template <traits::UIntegralOrFloating T> constexpr auto TriangleArea      (const T& height, const T& base) -> T
    {
        return (base * height) / 2.0;
    }

    /// @brief Determines whether three side lengths can form a triangle
    /// 
    /// @tparam T: A type that is either an unsigned integral or floating-point type, as defined by traits::UIntegralOrFloating
    /// 
    ///  @param a: The length of the  first side
    ///  @param b: The length of the second side
    ///  @param c: The length of the  third side
    /// 
    /// @return true if the three side lengths satisfy the triangle inequality and can form a triangle; otherwise, false
    /// 
    template <traits::UIntegralOrFloating T> constexpr auto FormsATriangle    (const T& a, const T& b, const T& c) -> bool
    {
        return     (std::abs(b - c) < a and a < b + c)
               and (std::abs(a - c) < b and b < a + c)
               and (std::abs(a - b) < c and c < a + b);
    }
}

module : private;
