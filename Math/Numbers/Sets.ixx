module;

export module FatPound.Math.Numbers.Sets;

import std;

export namespace fatpound::math::numbers
{
    template <typename N>
    concept Rational = ::std::integral<N> or ::std::floating_point<N>;

    template <typename N>
    concept Natural = ::std::unsigned_integral<N>;
}

module : private;