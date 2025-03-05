module;

export module FatPound.Math.Numbers;

export import FatPound.Math.Numbers.Primes;
export import FatPound.Math.Numbers.Sets;

import std;

export namespace fatpound::math::numbers
{
    using namespace primes;

    template <typename T>
    constexpr auto two_pi = std::numbers::pi_v<T> * static_cast<T>(2.0);
}

module : private;