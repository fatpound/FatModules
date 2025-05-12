module;

export module FatPound.Math.Geometry.Circle;

import FatPound.Math.Geometry.Common;
import FatPound.Traits.Bitwise;

import std;

export namespace fatpound::math::geometry
{
    template <traits::UIntegralOrFloating T>
    class Circle
    {
    public:
        explicit Circle(const T& radius)
            :
            m_radius_(radius)
        {

        }

        explicit Circle()         = delete;
        Circle(const Circle&)     = default;
        Circle(Circle&&) noexcept = default;

        auto operator = (const Circle&)     -> Circle& = default;
        auto operator = (Circle&&) noexcept -> Circle& = default;
        ~Circle() noexcept                             = default;


    protected:


    private:
        T m_radius_;
    };
}

module : private;
