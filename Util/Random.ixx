module;

#include <FatNamespaces.hpp>

export module FatPound.Util.Random;

import FatPound.Math.Primes;

import std;

export namespace fatpound::util
{
    template <std::unsigned_integral N>
    auto RandomPrime(const N& min, const N& max) -> N
    {
        std::minstd_rand rng{ std::random_device{}() };
        const auto& rand_num = std::uniform_int_distribution<N>{min, max}(rng);

        if (FATSPACE_MATH::IsPrime<>(rand_num))
        {
            return rand_num;
        }

        if (const auto& next = FATSPACE_MATH::NextPrime<>(rand_num); next <= max)
        {
            return next;
        }

        if (const auto& prev = FATSPACE_MATH::PrevPrime<>(rand_num); min <= prev)
        {
            return prev;
        }

        return 0;
    }

    template <std::unsigned_integral N = std::size_t>
    auto RollDice() -> N
    {
        std::minstd_rand rng{ std::random_device{}() };

        return std::uniform_int_distribution<N>{ 1uz, 6uz }(rng);
    }
}

module : private;
