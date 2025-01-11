module;

export module FatPound.Math.Numset.Rational;

import std;

export namespace fatpound::math::numset
{
    template <typename T>
    concept Rational = ::std::integral<T> or ::std::floating_point<T>;
}

module : private;
