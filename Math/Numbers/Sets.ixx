module;

export module FatPound.Math.Numbers.Sets;

import FatPound.Bitwise.Concepts;

import std;

export namespace fatpound::math::numbers
{
    template <typename T> concept Natural  = std::unsigned_integral<T>;
    template <typename T> concept Integer  = std::integral<T>;
    template <typename T> concept Rational = bitwise::IntegralOrFloating<T>;
}

module : private;
