module;

export module FatPound.Math.Special;

import FatPound.Math.Numbers.Common;
import FatPound.Math.Multiplicative;
import FatPound.Traits.Bitwise;

import std;

export namespace fatpound::math
{
    template <traits::IntegralOrFloating T>
    constexpr auto Gaussian(const T& x, const T& rho)
    {
        const auto rhoSq2 = Square<>(rho) * 2.0;

        return (1.0 / std::sqrt(rhoSq2 * numbers::Pi<T>)) * std::exp(-(Square<>(x) / rhoSq2));
    }
}

// module : private;
