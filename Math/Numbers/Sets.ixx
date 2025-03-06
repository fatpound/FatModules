module;

export module FatPound.Math.Numbers.Sets;

import std;

export namespace fatpound::math::numbers
{
    template <typename T> concept Floating = ::std::floating_point<T>;
    template <typename T> concept Natural  = ::std::unsigned_integral<T>;
    template <typename T> concept Integer  = ::std::integral<T>;
    template <typename T> concept Rational = Integer<T> or Floating<T>;
}

module : private;