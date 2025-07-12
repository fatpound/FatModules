module;

export module FatPound.Math.Geometry.AngularConv;

import std;

export namespace fatpound::math::geometry
{
    template <std::floating_point T = float, std::convertible_to<T> U> constexpr auto DegToMOA(const U& deg) noexcept -> T
    {
        return deg * static_cast<T>(60.0);
    }
    template <std::floating_point T = float, std::convertible_to<T> U> constexpr auto DegToRad(const U& deg) noexcept -> T
    {
        return deg * static_cast<T>(0.01745329251994329576923690768489);
    }
    template <std::floating_point T = float, std::convertible_to<T> U> constexpr auto MOAToDeg(const U& moa) noexcept -> T
    {
        return moa * static_cast<T>(0.01666666666666666666666666666667);
    }
    template <std::floating_point T = float, std::convertible_to<T> U> constexpr auto MOAToRad(const U& moa) noexcept -> T
    {
        return moa * static_cast<T>(0.00029088820866572159615394846141477);
    }
    template <std::floating_point T = float, std::convertible_to<T> U> constexpr auto RadToDeg(const U& rad) noexcept -> T
    {
        return rad * static_cast<T>(57.295779513082320876798154814105);
    }
    template <std::floating_point T = float, std::convertible_to<T> U> constexpr auto RadToMOA(const U& rad) noexcept -> T
    {
        return rad * static_cast<T>(3437.7467707849392526078892888463);
    }
}

module : private;
