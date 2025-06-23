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
    template <template <typename> typename T, typename U>
    concept StdUniformDist = std::same_as<T<U>, std::conditional_t<std::integral<U>, std::uniform_int_distribution<U>, std::uniform_real_distribution<U>>>;
    
    template <template <typename> typename T, typename U>
    concept StdOtherBernoulliDist = std::integral<U> and requires()
    {
        requires
               std::same_as<T<U>, std::binomial_distribution<U>>
            or std::same_as<T<U>, std::negative_binomial_distribution<U>>
            or std::same_as<T<U>, std::geometric_distribution<U>>;
    };

    template <template <typename> typename T, typename U>
    concept StdPoissonDist = traits::IntegralOrFloating<U> and requires()
    {
        requires
              (std::same_as<T<U>, std::poisson_distribution<U>> and std::integral<U>)
            or std::same_as<T<U>, std::exponential_distribution<U>>
            or std::same_as<T<U>, std::gamma_distribution<U>>
            or std::same_as<T<U>, std::weibull_distribution<U>>
            or std::same_as<T<U>, std::extreme_value_distribution<U>>;
    };

    template <template <typename> typename T, typename U>
    concept StdNormalDist = std::floating_point<U> and requires()
    {
        requires
               std::same_as<T<U>, std::normal_distribution<U>>
            or std::same_as<T<U>, std::lognormal_distribution<U>>
            or std::same_as<T<U>, std::chi_squared_distribution<U>>
            or std::same_as<T<U>, std::cauchy_distribution<U>>
            or std::same_as<T<U>, std::fisher_f_distribution<U>>
            or std::same_as<T<U>, std::student_t_distribution<U>>;
    };

    template <template <typename> typename T, typename U>
    concept StdSamplingDist = traits::IntegralOrFloating<U> and requires()
    {
        requires
              (std::same_as<T<U>, std::discrete_distribution<U>> and std::integral<U>)
            or std::same_as<T<U>, std::piecewise_constant_distribution<U>>
            or std::same_as<T<U>, std::piecewise_linear_distribution<U>>;
    };

    template <template <typename> typename T, typename U>
    concept StdUniformOrNormalDist = StdUniformDist<T, U> or StdNormalDist<T, U>;

    template <template <typename> typename T, typename U>
    concept StdDistNoBernoulli = StdUniformOrNormalDist<T, U> or StdOtherBernoulliDist<T, U> or StdPoissonDist<T, U> or StdSamplingDist<T, U>;

    auto RandBool(std::uniform_random_bit_generator auto& rng, std::bernoulli_distribution& bdist) -> bool
    {
        return bdist(rng);
    }

    template <traits::UIntegralOrFloating T, template <typename> typename D>
    requires StdUniformOrNormalDist<D, T>
    auto RandNumber(std::uniform_random_bit_generator auto& rng, D<T>& dist) -> T
    {
        return static_cast<T>(dist(rng));
    }

    template <traits::UIntegralOrFloating T>
    auto RandNumber(const T& min, const T& max, std::uniform_random_bit_generator auto& rng) -> T
    {
        std::conditional_t<std::unsigned_integral<T>, std::uniform_int_distribution<T>, std::uniform_real_distribution<T>> dist{ min, max };

        return RandNumber<>(rng, dist);
    }

    template <std::unsigned_integral T, template <typename> typename D>
    requires StdUniformOrNormalDist<D, T>
    auto RandPrimeNumber(std::uniform_random_bit_generator auto& rng, D<T>& dist) -> T
    {
        const auto& num = RandNumber<>(rng, dist);

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

    template <std::unsigned_integral T>
    auto RandPrimeNumber(const T& min, const T& max, std::uniform_random_bit_generator auto& rng) -> T
    {
        std::uniform_int_distribution<T> dist{ min, max };

        return RandPrimeNumber<>(rng, dist);
    }
    
    template <std::unsigned_integral T, template <typename> typename D>
    requires StdUniformOrNormalDist<D, T>
    auto RollDice(std::uniform_random_bit_generator auto& rng, D<T>& dist) -> T
    {
        return RandNumber<>(rng, dist);
    }
    
    template <std::unsigned_integral T>
    auto RollDice(std::uniform_random_bit_generator auto& rng) -> T
    {
        std::uniform_int_distribution<std::size_t> dist{ 1U, 6U };

        return RollDice<>(rng, dist);
    }

    template <bool FullAlpha = true, traits::UIntegralOrFloating T = std::size_t, template <typename> typename D>
    requires StdUniformOrNormalDist<D, T>
    auto RandColor(std::uniform_random_bit_generator auto& rng, D<T>& dist) -> utility::Color
    {
        if constexpr (std::unsigned_integral<T>)
        {
            using utility::Color;

            const auto& xrgb = static_cast<Color::Value_t>(RandNumber<>(rng, dist));

            if constexpr (FullAlpha)
            {
                return Color{ xrgb, static_cast<Color::ChannelA_t>(255U) };
            }
            else
            {
                return Color{ xrgb, bool{} };
            }
        }
        else
        {
            static_assert(false, "floating point Colors are not supported!");
        }
    }

    template <bool FullAlpha = true, traits::UIntegralOrFloating T = std::size_t, template <typename> typename D>
    requires StdUniformOrNormalDist<D, T>
    auto RandColorString(const std::string& prefix, const bool& withAlpha, std::uniform_random_bit_generator auto& rng, D<T>& dist) -> std::string
    {
        return RandColor<FullAlpha>(rng, dist).GetString(prefix, withAlpha);
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
