module;

#include <FatNamespaces.hpp>

export module FatPound.Random;

import FatPound.Math.Numbers.Primes;

import std;

export namespace fatpound::random
{
    template <std::unsigned_integral N>
    auto RandomPrime(const N& min, const N& max) -> N
    {
        std::minstd_rand rng{ std::random_device{}() };
        const auto& rand_num = std::uniform_int_distribution<N>{min, max}(rng);

        if (FATSPACE_NUMBERS::IsPrime<>(rand_num))
        {
            return rand_num;
        }

        if (const auto& next = FATSPACE_NUMBERS::NextPrime<>(rand_num); next <= max)
        {
            return next;
        }

        if (const auto& prev = FATSPACE_NUMBERS::PrevPrime<>(rand_num); min <= prev)
        {
            return prev;
        }

        return 0;
    }

    template <std::unsigned_integral N = std::size_t>
    auto RollDice() -> N
    {
        std::minstd_rand rng{ std::random_device{}() };

        return std::uniform_int_distribution<N>{ 1U, 6U }(rng);
    }
}

module : private;
