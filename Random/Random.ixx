module;

#include <FatNamespaces.hxx>

export module FatPound.Random;

export import FatPound.Random.URand;

import FatPound.Math.Numbers.Primes;
import FatPound.Traits.Bitwise;

import std;

export namespace fatpound::random
{
    template <traits::UIntegralOrFloating T, std::uniform_random_bit_generator U>
    auto RandNum(const T& min, const T& max, U& rng) -> T
    {
        if constexpr (std::floating_point<T>)
        {
            return static_cast<T>(std::uniform_real_distribution<long double>{ min, max }(rng));
        }
        else
        {
            return static_cast<T>(std::uniform_int_distribution<std::size_t>{ min, max }(rng));
        }
    }

    template <std::unsigned_integral T, std::uniform_random_bit_generator U>
    auto RandPrime(const T& min, const T& max, U& rng) -> T
    {
        const auto& rand_num = RandNum<>(min, max, rng);

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

        return 0U;
    }

    template <std::unsigned_integral T, std::uniform_random_bit_generator U>
    auto RollDice(U& rng) -> T
    {
        return RandNum<>(static_cast<T>(1U), static_cast<T>(6U), rng);
    }

    // Default variants

    template <traits::UIntegralOrFloating T = std::size_t, std::uniform_random_bit_generator U = std::minstd_rand>
    auto RandNum(
        const T&  min = std::numeric_limits<T>::min(),
        const T&  max = std::numeric_limits<T>::max(),
              U&& rng = U{ std::random_device{}() }) -> T
    {
        return RandNum<>(min, max, rng);
    }

    template <std::unsigned_integral T = std::size_t, std::uniform_random_bit_generator U = std::minstd_rand>
    auto RollDice(U&& rng = U{ std::random_device{}() }) -> T
    {
        return RollDice<T>(rng);
    }
}

module : private;
