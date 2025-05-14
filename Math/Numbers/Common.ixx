module;

export module FatPound.Math.Numbers.Common;

import std;

export namespace fatpound::math::numbers
{
    template <std::floating_point FP = double> constexpr auto       Pi = std::numbers::pi_v<FP>;
    template <std::floating_point FP = double> constexpr auto    twoPi = Pi<FP> * static_cast<FP>(2.0);
    template <std::floating_point FP = double> constexpr auto   PiDiv2 = Pi<FP> / static_cast<FP>(2.0);
    template <std::floating_point FP = double> constexpr auto   PiDiv4 = Pi<FP> / static_cast<FP>(4.0);
    template <std::floating_point FP = double> constexpr auto    invPi = static_cast<FP>(1.0) / Pi<FP>;
    template <std::floating_point FP = double> constexpr auto invTwoPi = invPi / static_cast<FP>(2.0);
}

module : private;
