module;

#ifdef FAT_BUILDING_WITH_MSVC
    #include <DirectXMath.h>
#endif

export module FatPound.Math.Geometry.Shape.Circle;

#ifdef FAT_BUILDING_WITH_MSVC

import FatPound.Math.Multiplicative;
import FatPound.Math.Numbers.Common;
import FatPound.Math.Geometry.Common;
import FatPound.Math.Geometry.AngularConv;
import FatPound.Traits.Bitwise;

import std;

namespace dx = DirectX;

export namespace fatpound::math::geometry
{
    template <std::floating_point T>
    class alignas(32) Circle
    {
        static constexpr auto scx_Default_Z_ = 1.0F;
        static constexpr auto scx_Default_W_ = 1.0F;

    public:
        explicit Circle(const dx::XMVECTOR& center, const std::floating_point auto& radius)
            :
            m_center_(center),
            m_radius_(static_cast<T>(radius))
        {

        }

        explicit Circle(
            const std::convertible_to<T> auto& x,
            const std::convertible_to<T> auto& y,
            const std::convertible_to<T> auto& z,
            const std::convertible_to<T> auto& radius)
            :
            Circle(
                dx::XMVectorSet(
                    static_cast<float>(x),
                    static_cast<float>(y),
                    static_cast<float>(z),
                    scx_Default_W_
                ),
                radius)
        {

        }

        explicit Circle(
            const std::convertible_to<T> auto& x,
            const std::convertible_to<T> auto& y,
            const std::convertible_to<T> auto& radius)
            :
            Circle(x, y, scx_Default_Z_, radius)
        {

        }

        explicit Circle()         = delete;
        Circle(const Circle&)     = default;
        Circle(Circle&&) noexcept = default;

        auto operator = (const Circle&)     -> Circle& = default;
        auto operator = (Circle&&) noexcept -> Circle& = default;
        ~Circle() noexcept                             = default;


    public:
        template <traits::UIntegralOrFloating U> constexpr auto Area      (const U& radius) -> U
        {
            return Square<>(radius) * numbers::Pi<U>;
        }
        template <traits::UIntegralOrFloating U> constexpr auto Diameter  (const U& radius) -> U
        {
            return radius * static_cast<U>(2.0);
        }
        template <traits::UIntegralOrFloating U> constexpr auto Perimeter (const U& radius) -> U
        {
            return Diameter<>(radius) * numbers::Pi<U>;
        }


    public:
        auto GetCenter    () const noexcept
        {
            return m_center_;
        }
        auto GetRadius    () const noexcept -> T
        {
            return m_radius_;
        }
        auto GetArea      () const noexcept
        {
            return Area<>(GetRadius());
        }
        auto GetDiameter  () const noexcept
        {
            return Diameter<>(GetRadius());
        }
        auto GetPerimeter () const noexcept
        {
            return Perimeter<>(GetRadius());
        }

        auto IsInsideOf              (const Circle& other) const noexcept -> bool
        {
            return Distance_CenterToCenter(other) + GetRadius() <= other.GetRadius();
        }
        auto Contains                (const Circle& other) const noexcept -> bool
        {
            return Distance_CenterToCenter(other) + other.GetRadius() <= GetRadius();
        }

        auto Distance_CenterToCenter (const Circle& other) noexcept
        {
            return Distance<>(GetCenter(), other.GetCenter());
        }
        auto Distance_CenterToEdge   (const Circle& other) noexcept
        {
            return Distance_CenterToCenter(other) - other.GetRadius();
        }
        auto Distance_EdgeToEdge     (const Circle& other) noexcept
        {
            return Distance_CenterToEdge(other) - GetRadius();
        }
        auto Distance_EdgeToCenter   (const Circle& other) noexcept
        {
            return Distance_CenterToCenter(other) - GetRadius();
        }

        auto ArcLengthRad (const T& rad) const
        {
            return GetRadius() * rad;
        }
        auto ArcLengthDeg (const T& deg) const
        {
            return ArcLengthRad(DegToRad<>(deg));
        }

        void TranslateBy  (const dx::XMVECTOR& v) noexcept
        {
            m_center_ = (m_center_ + v);
        }


    protected:


    private:
        dx::XMVECTOR m_center_;
        T            m_radius_;
    };

    using CircleLD = Circle<long double>;
    using CircleD  = Circle<double>;
    using CircleF  = Circle<float>;
}

#endif

module : private;
