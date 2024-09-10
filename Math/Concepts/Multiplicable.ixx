module;

export module FatPound.Math.Concepts:Multiplicable;

import std;

export namespace fatpound::math::concepts
{
    template <
        typename T,
        typename U
    >
    concept Multiplicable = requires(T var1, U var2)
    {
        { var1 * var2 };
    };

    template <
        typename T,
        typename U
    >
    concept Multiplicable_Noexcept = Multiplicable<T, U>
    and
    requires(T var1, U var2)
    {
        { var1 * var2 } noexcept;
    };

    template <
        typename T,
        typename U,
        typename Which = T
    >
    concept Multiplicable_SameAs_Which = Multiplicable<T, U>
    and
    requires(T var1, U var2)
    {
        { var1 * var2 } -> std::same_as<Which>;
    };

    template <typename T> concept SelfMultiplicable          = Multiplicable<T, T>;
    template <typename T> concept SelfMultiplicable_Noexcept = Multiplicable_Noexcept<T, T>;
}