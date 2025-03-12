module;

export module FatPound.Bitwise.Concepts;

import std;

export namespace fatpound::bitwise
{
    template <typename T> concept Floating                      = ::std::floating_point<T>;
    template <typename T> concept Unsigned_Integral             = ::std::unsigned_integral<T>;
    template <typename T> concept Signed_Integral               = ::std::signed_integral<T>;
    template <typename T> concept Integral                      = Unsigned_Integral<T> or Signed_Integral<T>;

    template <typename T> concept Unsigned_Integral_Or_Floating = Unsigned_Integral<T> or Floating<T>;
    template <typename T> concept   Signed_Integral_Or_Floating =   Signed_Integral<T> or Floating<T>;
    template <typename T> concept          Integral_Or_Floating =          Integral<T> or Floating<T>;
}

module : private;