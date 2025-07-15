module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <DirectXMath.h>
#endif

export module FatPound.Geometry.Shape.Circle;

#ifdef FATLIB_BUILDING_WITH_MSVC

import FatPound.Geometry.AngularConv;
import FatPound.Geometry.Common;

import FatPound.Math.Multiplicative;
import FatPound.Math.Numbers.Common;
import FatPound.Traits.Bitwise;

import std;

namespace dx = DirectX;

export namespace fatpound::geometry::shape
{
    class alignas(32) Circle
    {
        static constexpr auto scx_Default_Z_ = 1.0F;
        static constexpr auto scx_Default_W_ = 1.0F;

    public:
        explicit Circle(const dx::XMVECTOR& center, const std::convertible_to<float> auto& radius)
            :
            m_center_(center),
            m_radius_(static_cast<float>(radius))
        {

        }

        explicit Circle(
            const std::convertible_to<float> auto& x,
            const std::convertible_to<float> auto& y,
            const std::convertible_to<float> auto& z,
            const std::convertible_to<float> auto& radius)
            :
            Circle(dx::XMVectorSet(x, y, z, scx_Default_W_), radius)
        {

        }

        explicit Circle(
            const std::convertible_to<float> auto& x,
            const std::convertible_to<float> auto& y,
            const std::convertible_to<float> auto& radius)
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
        template <traits::UIntegralOrFloating T> static constexpr auto Area      (const T& radius) noexcept -> T
        {
            return math::Square<>(radius) * math::numbers::Pi<T>;
        }
        template <traits::UIntegralOrFloating T> static constexpr auto Diameter  (const T& radius) noexcept -> T
        {
            return radius * static_cast<T>(2.0);
        }
        template <traits::UIntegralOrFloating T> static constexpr auto Perimeter (const T& radius) noexcept -> T
        {
            return Diameter<>(radius) * math::numbers::Pi<T>;
        }


    public:
        auto GetCenter    () const noexcept -> dx::XMVECTOR
        {
            return m_center_;
        }
        auto GetRadius    () const noexcept -> float
        {
            return m_radius_;
        }
        auto GetArea      () const noexcept -> float
        {
            return Area<>(GetRadius());
        }
        auto GetDiameter  () const noexcept -> float
        {
            return Diameter<>(GetRadius());
        }
        auto GetPerimeter () const noexcept -> float
        {
            return Perimeter<>(GetRadius());
        }

        auto Distance_CenterToCenter (const Circle& other) const noexcept -> float
        {
            return Distance4(GetCenter(), other.GetCenter());
        }
        auto Distance_CenterToEdge   (const Circle& other) const noexcept -> float
        {
            return Distance_CenterToCenter(other) - other.GetRadius();
        }
        auto Distance_EdgeToEdge     (const Circle& other) const noexcept -> float
        {
            return Distance_CenterToEdge(other) - GetRadius();
        }
        auto Distance_EdgeToCenter   (const Circle& other) const noexcept -> float
        {
            return Distance_CenterToCenter(other) - GetRadius();
        }

        auto ArcLengthRad (const float& rad) const noexcept -> float
        {
            return GetRadius() * rad;
        }
        auto ArcLengthDeg (const float& deg) const noexcept -> float
        {
            return ArcLengthRad(DegToRad<>(deg));
        }

        auto IsInsideOf   (const Circle& other) const noexcept -> bool
        {
            return Distance_CenterToCenter(other) + GetRadius() <= other.GetRadius();
        }
        auto Contains     (const Circle& other) const noexcept -> bool
        {
            return Distance_CenterToCenter(other) + other.GetRadius() <= GetRadius();
        }

        void TranslateBy  (const dx::XMVECTOR& v) noexcept
        {
            m_center_ = (m_center_ + v);
        }


    protected:


    private:
        dx::XMVECTOR   m_center_;
        float          m_radius_;
    };
}

#endif

module : private;
