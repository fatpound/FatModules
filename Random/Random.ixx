module;

#include <_macros/Namespaces.hxx>

export module FatPound.Random;

export import FatPound.Random.URand;

import FatPound.Math.Numbers.Primes;
import FatPound.Traits.Bitwise;
import FatPound.Utility.Color;

import std;

export namespace fatpound::random
{
    template <template <typename> typename Dist, typename T>
    concept StdUniformDist = std::same_as<Dist<T>, std::conditional_t<std::integral<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>>>;
    
    template <template <typename> typename Dist, typename T>
    concept StdOtherBernoulliDist = std::integral<T> and requires()
    {
        requires
               std::same_as<Dist<T>, std::binomial_distribution<T>>
            or std::same_as<Dist<T>, std::negative_binomial_distribution<T>>
            or std::same_as<Dist<T>, std::geometric_distribution<T>>;
    };

    template <template <typename> typename Dist, typename T>
    concept StdPoissonDist = traits::IntegralOrFloating<T> and requires()
    {
        requires
              (std::same_as<Dist<T>, std::poisson_distribution<T>> and std::integral<T>)
            or std::same_as<Dist<T>, std::exponential_distribution<T>>
            or std::same_as<Dist<T>, std::gamma_distribution<T>>
            or std::same_as<Dist<T>, std::weibull_distribution<T>>
            or std::same_as<Dist<T>, std::extreme_value_distribution<T>>;
    };

    template <template <typename> typename Dist, typename T>
    concept StdNormalDist = std::floating_point<T> and requires()
    {
        requires
               std::same_as<Dist<T>, std::normal_distribution<T>>
            or std::same_as<Dist<T>, std::lognormal_distribution<T>>
            or std::same_as<Dist<T>, std::chi_squared_distribution<T>>
            or std::same_as<Dist<T>, std::cauchy_distribution<T>>
            or std::same_as<Dist<T>, std::fisher_f_distribution<T>>
            or std::same_as<Dist<T>, std::student_t_distribution<T>>;
    };

    template <template <typename> typename Dist, typename T>
    concept StdSamplingDist = traits::IntegralOrFloating<T> and requires()
    {
        requires
              (std::same_as<Dist<T>, std::discrete_distribution<T>> and std::integral<T>)
            or std::same_as<Dist<T>, std::piecewise_constant_distribution<T>>
            or std::same_as<Dist<T>, std::piecewise_linear_distribution<T>>;
    };

    template <template <typename> typename Dist, typename T>
    concept StdUniformOrNormalDist = StdUniformDist<Dist, T> or StdNormalDist<Dist, T>;

    template <template <typename> typename Dist, typename T>
    concept StdDistNoBernoulli = StdUniformOrNormalDist<Dist, T> or StdOtherBernoulliDist<Dist, T> or StdPoissonDist<Dist, T> or StdSamplingDist<Dist, T>;



    template <std::unsigned_integral T, template <typename> typename Dist>
    requires StdUniformOrNormalDist<Dist, T>
    auto RandPrimeNumber(std::uniform_random_bit_generator auto& rng, Dist<T>& dist) -> T
    {
        const auto& num = static_cast<T>(dist(rng));

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



    template <utility::Color::ChannelA_t Alpha = 255U, traits::UIntegralOrFloating T = std::size_t, template <typename> typename Dist>
    requires StdUniformOrNormalDist<Dist, T>
    auto RandColor(std::uniform_random_bit_generator auto& rng, Dist<T>& dist) -> utility::Color
    {
        if constexpr (std::unsigned_integral<T>)
        {
            return utility::Color{ dist(rng), Alpha };
        }
        else
        {
            static_assert(false, "floating point Colors are not supported!");
        }
    }



    template <utility::Color::ChannelA_t Alpha = 255U, traits::UIntegralOrFloating T = std::size_t, template <typename> typename Dist>
    requires StdUniformOrNormalDist<Dist, T>
    auto RandColorString(const std::string& prefix, const bool& withAlpha, std::uniform_random_bit_generator auto& rng, Dist<T>& dist) -> std::string
    {
        return RandColor<Alpha>(rng, dist).GetString(prefix, withAlpha);
    }



    auto RandString(const std::unsigned_integral auto& length, const std::string_view& charset, std::uniform_random_bit_generator auto& rng) -> std::string
    {
        if (length == 0)
        {
            return {};
        }

        if (charset.empty())
        {
            throw std::invalid_argument("Charset cannot be empty!");
        }

        std::uniform_int_distribution<std::size_t> dist(0U, charset.size() - 1U);

        return std::views::iota(0U, length)
             | std::views::transform([&charset, &dist, &rng](auto) { return charset[dist(rng)]; })
             | std::ranges::to<std::string>();
    }



    auto RandPassword(
        const std::unsigned_integral auto& length,
        const bool& withLowercase,
        const bool& withUppercase,
        const bool& withDigits,
        const bool& withSymbols,
        const bool& enforceEachType,
        std::uniform_random_bit_generator auto& rng) -> std::string
    {
        constexpr std::string_view LowerCase = "abcdefghijklmnopqrstuvwxyz";
        constexpr std::string_view UpperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        constexpr std::string_view Digits    =                 "0123456789";
        constexpr std::string_view Symbols   = "!@#$%^&*()-_=+[]{}|;:,.<>?";

        if (length == 0)
        {
            throw std::invalid_argument("Password length must be greater than 0");
        }

        if (not (withLowercase or withUppercase or withDigits or withSymbols))
        {
            throw std::invalid_argument("At least one charset must be enabled!");
        }

        std::vector<std::string_view> vec;
        vec.reserve(4U);

        withLowercase ? vec.push_back(LowerCase) : void();
        withUppercase ? vec.push_back(UpperCase) : void();
        withDigits    ? vec.push_back(Digits)    : void();
        withSymbols   ? vec.push_back(Symbols)   : void();

        std::string password;

        if (enforceEachType)
        {
            password += std::ranges::to<std::string>(vec | std::views::transform([](const auto& set) { return set[0]; }));
        }

        password += RandString<>(length - password.length(), std::ranges::to<std::string>(vec | std::views::join), rng);

        std::shuffle<>(password.begin(), password.end(), rng);

        return password;
    }
}

module : private;
