module;

#include <FatSTL_Macros.hxx>

#ifdef FAT_BUILDING_WITH_MSVC
    #include <DirectXMath.h>
#endif

export module FatPound.Math.Geometry.Common;

import FatPound.Math.Multiplicative;
import FatPound.Math.Numbers.Common;
import FatPound.Traits.Bitwise;

import std;

#ifdef FAT_BUILDING_WITH_MSVC
    namespace dx = DirectX;
#endif

export namespace fatpound::math::geometry
{
#ifdef FAT_BUILDING_WITH_MSVC

    auto operator + (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) noexcept -> dx::XMVECTOR
    {
        return dx::XMVectorAdd(p0, p1);
    }
    auto operator - (const dx::XMVECTOR& p1, const dx::XMVECTOR& p0) noexcept -> dx::XMVECTOR
    {
        return dx::XMVectorSubtract(p1, p0);
    }

    auto DistanceVector2 (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1)
    {
        return dx::XMVector2Length(p1 - p0);
    }
    auto DistanceVector3 (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1)
    {
        return dx::XMVector3Length(p1 - p0);
    }
    auto Distance2       (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) -> float
    {
        return dx::XMVectorGetX(DistanceVector2(p0, p1));
    }
    auto Distance3       (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) -> float
    {
        return dx::XMVectorGetX(DistanceVector3(p0, p1));
    }


    /// @brief Calculates distance, 3D by default
    /// 
    /// @param p0: 1st 3D position vector
    /// @param p1: 2nd 3D position vector
    /// 
    /// @return the distance in float type
    auto Distance        (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1) -> float
    {
        return Distance3(p0, p1);
    }


    auto Distance        (const dx::XMFLOAT2& p0, const dx::XMFLOAT2& p1) noexcept -> float
    {
        return Distance2(dx::XMLoadFloat2(&p0), dx::XMLoadFloat2(&p1));
    }
    auto Distance        (const dx::XMFLOAT3& p0, const dx::XMFLOAT3& p1) noexcept -> float
    {
        return Distance3(dx::XMLoadFloat3(&p0), dx::XMLoadFloat3(&p1));
    }
    auto CompareDistance (const dx::XMVECTOR& p0, const dx::XMVECTOR& p1)
    {
        return dx::XMVectorGetX(dx::XMVector3LengthSq(p0)) > dx::XMVectorGetX(dx::XMVector3LengthSq(p1));
    }

#endif

    template <traits::UIntegralOrFloating T> constexpr auto SquarePerimeter   (const T& length) -> T
    {
        return length * static_cast<T>(4);
    }
    template <traits::UIntegralOrFloating T> constexpr auto SquareArea        (const T& length) noexcept(Squarable_NX<T>) -> T
    {
        return Square<>(length);
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

    /// @brief Checks whether three side lengths can form a triangle
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
