module;

export module FatPound.Math.Numbers.Common;

import std;

export namespace fatpound::math::numbers
{
    template <std::floating_point T = float> constexpr auto       Pi = std::numbers::pi_v<T>;
    template <std::floating_point T = float> constexpr auto    twoPi = Pi<T> * static_cast<T>(2.0);
    template <std::floating_point T = float> constexpr auto   PiDiv2 = Pi<T> / static_cast<T>(2.0);
    template <std::floating_point T = float> constexpr auto   PiDiv4 = Pi<T> / static_cast<T>(4.0);
    template <std::floating_point T = float> constexpr auto    invPi = static_cast<T>(1.0) / Pi<T>;
    template <std::floating_point T = float> constexpr auto invTwoPi = invPi<T> / static_cast<T>(2.0);
}

module : private;
