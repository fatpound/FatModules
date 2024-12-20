module;

export module FatPound.Math.Number_Set.Rational;

import std;

export namespace fatpound::math::number_set
{
    template <typename T>
    concept Rational = ::std::integral<T> or ::std::floating_point<T>;
}

module : private;