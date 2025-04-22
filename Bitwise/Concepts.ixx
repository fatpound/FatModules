module;

export module FatPound.Bitwise.Concepts;

import std;

export namespace fatpound::bitwise
{
    template <typename T> concept UIntegralOrFloating = std::unsigned_integral<T> or std::floating_point<T>;
    template <typename T> concept SIntegralOrFloating = std::signed_integral<T>   or std::floating_point<T>;
    template <typename T> concept  IntegralOrFloating = std::integral<T>          or std::floating_point<T>;
}

module : private;
