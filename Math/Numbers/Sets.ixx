module;

export module FatPound.Math.Numbers.Sets;

import FatPound.Bitwise.Concepts;

import std;

export namespace fatpound::math::numbers
{
    template <typename T> concept Natural  = bitwise::Unsigned_Integral<T>;
    template <typename T> concept Integer  = bitwise::Integral<T>;
    template <typename T> concept Rational = bitwise::Integral_Or_Floating<T>;
}

module : private;