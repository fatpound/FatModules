module;

#include <FatNamespaces.hxx>

export module FatPound.Random;

export import FatPound.Random.URand;

import FatPound.Math.Numbers.Primes;
import FatPound.Traits.Bitwise;
import FatPound.Traits.Callable;
import FatPound.Utility.Color;

import std;

export namespace fatpound::random
{
    template <template <typename> typename T, typename U>
    concept StdUniformDist = std::same_as<T<U>, std::conditional_t<std::integral<U>, std::uniform_int_distribution<U>, std::uniform_real_distribution<U>>>;

    template <std::uniform_random_bit_generator T, typename D>
    requires std::same_as<D, std::bernoulli_distribution>
    auto RandBool(T& rng, D& dist) -> bool
    {
        return dist(rng);
    }

    template <traits::UIntegralOrFloating T, std::uniform_random_bit_generator U, template <typename> typename D>
    requires StdUniformDist<D, T>
    auto RandNum(U& rng, D<T>& dist) -> T
    {
        return static_cast<T>(dist(rng));
    }

    template <traits::UIntegralOrFloating T, std::uniform_random_bit_generator U>
    auto RandNum(const T& min, const T& max, U& rng) -> T
    {
        std::uniform_int_distribution<T> dist{ min, max };

        return RandNum<>(rng, dist);
    }

    template <std::unsigned_integral T, std::uniform_random_bit_generator U, template <typename> typename D>
    requires StdUniformDist<D, T>
    auto RandPrime(U& rng, D<T>& dist) -> T
    {
        const auto& num = RandNum<>(rng, dist);

        if (FATSPACE_NUMBERS::IsPrime<>(num))
        {
            return num;
        }

        if (const auto& next = FATSPACE_NUMBERS::NextPrime<>(num); next <= dist.max())
        {
            return next;
        }

        if (const auto& prev = FATSPACE_NUMBERS::PrevPrime<>(num); dist.min() <= prev)
        {
            return prev;
        }

        return static_cast<T>(0U);
    }

    template <std::unsigned_integral T, std::uniform_random_bit_generator U>
    auto RandPrime(const T& min, const T& max, U& rng) -> T
    {
        std::uniform_int_distribution<T> dist{ min, max };

        return RandPrime<>(rng, dist);
    }
    
    template <std::unsigned_integral T, std::uniform_random_bit_generator U, template <typename> typename D>
    requires StdUniformDist<D, T>
    auto RollDice(U& rng, D<T>& dist) -> T
    {
        return RandNum<>(rng, dist);
    }
    
    template <std::unsigned_integral T, std::uniform_random_bit_generator U>
    auto RollDice(U& rng) -> T
    {
        std::uniform_int_distribution<std::size_t> dist{ 1U, 6U };

        return RollDice<>(rng, dist);
    }

    template <bool FullAlpha = true, traits::UIntegralOrFloating T = std::size_t, std::uniform_random_bit_generator U, template <typename> typename D>
    requires StdUniformDist<D, T>
    auto RandColor(U& rng, D<T>& dist) -> utility::Color
    {
        if constexpr (std::unsigned_integral<T>)
        {
            const auto& xrgb = static_cast<std::uint32_t>(RandNum<T>(rng, dist));

            if constexpr (FullAlpha)
            {
                return utility::Color{ xrgb, static_cast<std::uint8_t>(255U) };
            }
            else
            {
                return utility::Color{ xrgb };
            }
        }
        else
        {
            static_assert(false, "floating point Colors are not supported!");
        }
    }
}

module : private;
