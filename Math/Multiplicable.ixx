module;

export module FatPound.Math.Multiplicable;

import std;

export namespace fatpound::math
{
    template <typename T, typename U>
    concept Multiplicable = requires(T a, U b)
    {
        a * b;
    };

    template <typename T, typename U>
    concept Multiplicable_NX = requires(T a, U b)
    {
        { a * b } noexcept;
    };

    template <typename T, typename U, bool First>
    concept Multiplicable_SameAs = requires(T a, U b)
    {
        { a * b } -> ::std::same_as<::std::conditional_t<First, T, U>>;
    };
    
    template <typename T, typename U> concept Multiplicable_BothWays    = Multiplicable<T, U>    and Multiplicable<U, T>;
    template <typename T, typename U> concept Multiplicable_NX_BothWays = Multiplicable_NX<T, U> and Multiplicable_NX<U, T>;

    template <typename T, typename U> concept Multiplicable_SameAs_First     = Multiplicable_SameAs<T, U, true>;
    template <typename T, typename U> concept Multiplicable_SameAs_Second    = Multiplicable_SameAs<T, U, false>;
    template <typename T, typename U> concept Multiplicable_SameAs_First_NX  = Multiplicable_SameAs_First<T, U>  and Multiplicable_NX<T, U>;
    template <typename T, typename U> concept Multiplicable_SameAs_Second_NX = Multiplicable_SameAs_Second<T, U> and Multiplicable_NX<T, U>;

    template <typename T, typename U> concept Multiplicable_SameAs_First_BothWays     = Multiplicable_SameAs<T, U, true>  and Multiplicable_SameAs<U, T, false>;
    template <typename T, typename U> concept Multiplicable_SameAs_Second_BothWays    = Multiplicable_SameAs<T, U, false> and Multiplicable_SameAs<U, T, true>;
    template <typename T, typename U> concept Multiplicable_SameAs_First_NX_BothWays  = Multiplicable_SameAs_First_BothWays<T, U>  and Multiplicable_NX_BothWays<T, U>;
    template <typename T, typename U> concept Multiplicable_SameAs_Second_NX_BothWays = Multiplicable_SameAs_Second_BothWays<T, U> and Multiplicable_NX_BothWays<T, U>;

    template <typename T> concept Squarable    = Multiplicable<T, T>;
    template <typename T> concept Squarable_NX = Multiplicable_NX<T, T>;
}

module : private;
