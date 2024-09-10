module;

export module FatPound.Math.Concepts.Number_Set:Rational;

import std;

export namespace fatpound::math::concepts::number_set
{
    template <typename T>
    concept Rational = std::integral<T> or std::floating_point<T>;
}