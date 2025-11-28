module;

export module FatPound.Math.Numbers.Sets;

import FatPound.Traits.Bitwise;
import std;

export namespace fatpound::math::numbers
{
    template <typename T> concept Natural  = std::unsigned_integral<T>; // with 0
    template <typename T> concept Integer  = std::integral<T>;
    template <typename T> concept Rational = traits::IntegralOrFloating<T>;
}

// module : private;
