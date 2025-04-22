module;

export module FatPound.Math.AngularConv;

import std;

export namespace fatpound::math::inline angular_conv
{
    template <std::floating_point FP = double, std::convertible_to<FP> T> constexpr auto DegToMOA(const T& deg) -> FP
    {
        return deg * 60.0;
    }
    template <std::floating_point FP = double, std::convertible_to<FP> T> constexpr auto DegToRad(const T& deg) -> FP
    {
        return deg * 0.01745329251994329576923690768489;
    }
    template <std::floating_point FP = double, std::convertible_to<FP> T> constexpr auto MOAToDeg(const T& moa) -> FP
    {
        return moa * 0.01666666666666666666666666666667;
    }
    template <std::floating_point FP = double, std::convertible_to<FP> T> constexpr auto MOAToRad(const T& moa) -> FP
    {
        return moa * 0.00029088820866572159615394846141477;
    }
    template <std::floating_point FP = double, std::convertible_to<FP> T> constexpr auto RadToDeg(const T& rad) -> FP
    {
        return rad * 57.295779513082320876798154814105;
    }
    template <std::floating_point FP = double, std::convertible_to<FP> T> constexpr auto RadToMOA(const T& rad) -> FP
    {
        return rad * 3437.7467707849392526078892888463;
    }
}

module : private;
