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
    concept StdOtherBernoulliDist = requires()
    {
        requires std::integral<T>;

        requires
               std::same_as<Dist<T>, std::binomial_distribution<T>>
            or std::same_as<Dist<T>, std::negative_binomial_distribution<T>>
            or std::same_as<Dist<T>, std::geometric_distribution<T>>;
    };

    template <template <typename> typename Dist, typename T>
    concept StdPoissonDist = requires()
    {
        requires traits::IntegralOrFloating<T>;

        requires
              (std::same_as<Dist<T>, std::poisson_distribution<T>> and std::integral<T>)
            or std::same_as<Dist<T>, std::exponential_distribution<T>>
            or std::same_as<Dist<T>, std::gamma_distribution<T>>
            or std::same_as<Dist<T>, std::weibull_distribution<T>>
            or std::same_as<Dist<T>, std::extreme_value_distribution<T>>;
    };

    template <template <typename> typename Dist, typename T>
    concept StdNormalDist = requires()
    {
        requires std::floating_point<T>;

        requires
               std::same_as<Dist<T>, std::normal_distribution<T>>
            or std::same_as<Dist<T>, std::lognormal_distribution<T>>
            or std::same_as<Dist<T>, std::chi_squared_distribution<T>>
            or std::same_as<Dist<T>, std::cauchy_distribution<T>>
            or std::same_as<Dist<T>, std::fisher_f_distribution<T>>
            or std::same_as<Dist<T>, std::student_t_distribution<T>>;
    };

    template <template <typename> typename Dist, typename T>
    concept StdSamplingDist = requires()
    {
        requires traits::IntegralOrFloating<T>;

        requires
              (std::same_as<Dist<T>, std::discrete_distribution<T>> and std::integral<T>)
            or std::same_as<Dist<T>, std::piecewise_constant_distribution<T>>
            or std::same_as<Dist<T>, std::piecewise_linear_distribution<T>>;
    };

    template <template <typename> typename Dist, typename T> concept StdUniformOrNormalDist = StdUniformDist<Dist, T>         or StdNormalDist<Dist, T>;
    template <template <typename> typename Dist, typename T> concept StdDistNoBernoulli     = StdUniformOrNormalDist<Dist, T> or StdOtherBernoulliDist<Dist, T> or StdPoissonDist<Dist, T> or StdSamplingDist<Dist, T>;



    /// @brief Returns a random prime number within the range defined by the distribution
    ///
    /// @tparam    T: An unsigned integral type
    /// @tparam Dist: A standard uniform or normal distribution type
    ///
    /// @param   rng: A standard uniform random bit generator
    /// @param  dist: An instance of the distribution used to determine the range
    ///
    /// @return A random prime number in the range [dist.min(), dist.max()]
    /// 
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



    /// @brief Generates a random color with optionally fixed alpha
    ///
    /// @tparam FixedAlpha: Whether to use the fixed alpha value specified by @p Alpha (default: true)
    /// @tparam      Alpha: The fixed alpha value of type Color::ChannelA_t (default: 255)
    /// @tparam          T: An unsigned integral or floating-point type (default: std::size_t)
    /// @tparam       Dist: A standard uniform or normal distribution type
    ///              
    /// @param         rng: A standard uniform random bit generator
    /// @param        dist: A distribution instance used to generate the color's RGB components
    ///
    /// @return A Color object with ARGB components generated from the distribution and fixed alpha value
    ///
    /// @note Only unsigned integral types for T are supported. Using floating-point types will cause a static assertion failure.
    ///
    /// @see utility::Color
    /// 
    template <bool FixedAlpha = true, utility::Color::ChannelA_t Alpha = 255U, traits::UIntegralOrFloating T = std::size_t, template <typename> typename Dist>
    requires StdUniformOrNormalDist<Dist, T>
    auto RandColor(std::uniform_random_bit_generator auto& rng, Dist<T>& dist) -> utility::Color
    {
        if constexpr (std::unsigned_integral<T>)
        {
            if constexpr (FixedAlpha)
            {
                return utility::Color{ dist(rng), Alpha };
            }
            else
            {
                return utility::Color{ dist(rng), bool{} };
            }
        }
        else
        {
            static_assert(false, "floating-point Colors are not supported!");
        }
    }



    /// @brief Generates a random color string with optionally fixed alpha
    ///
    /// @tparam FixedAlpha: Whether to use the fixed alpha value specified by @p Alpha (default: true)
    /// @tparam      Alpha: The fixed alpha value of type Color::ChannelA_t (default: 255)
    /// @tparam          T: An unsigned integral or floating-point type (default: std::size_t)
    /// @tparam       Dist: A standard uniform or normal distribution type
    ///              
    /// @param      prefix: A string to prepend to the resulting color string
    /// @param   withAlpha: Whether to include the alpha channel in the output string
    /// @param         rng: A standard uniform random bit generator
    /// @param        dist: A distribution instance used to generate the color's RGB components
    ///
    /// @return A string representing the randomly generated color, optionally including alpha
    ///
    /// @note Only unsigned integral types for T are supported. Using floating-point types will cause a static assertion failure.
    ///
    /// @see utility::Color
    /// 
    template <bool FixedAlpha = true, utility::Color::ChannelA_t Alpha = 255U, traits::UIntegralOrFloating T = std::size_t, template <typename> typename Dist>
    requires StdUniformOrNormalDist<Dist, T>
    auto RandColorString(const std::string& prefix, const bool& withAlpha, std::uniform_random_bit_generator auto& rng, Dist<T>& dist) -> std::string
    {
        return RandColor<FixedAlpha, Alpha>(rng, dist).GetString(prefix, withAlpha);
    }



    /// @brief Generates a random string of the specified length using the given character set
    ///
    /// @param  length: The length of the string to generate (must be an unsigned integral value)
    /// @param charset: A string view containing the set of characters to randomly choose from
    /// @param     rng: A uniform random bit generator
    ///
    /// @return A randomly generated string of size @p length, composed of characters from @p charset
    ///
    /// @throws std::invalid_argument if @p charset is empty
    /// 
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



    /// @brief Generates a random password string with customizable character sets and enforcement rules
    ///
    /// @param          length: The desired length of the password (unsigned integral value) (must be greater than 0)
    /// @param   withLowercase: Whether to include lowercase letters (of the English alphabet)
    /// @param   withUppercase: Whether to include uppercase letters (of the English alphabet)
    /// @param      withDigits: Whether to include digits
    /// @param     withSymbols: Whether to include symbols => !@#$%^&*()-_=+[]{}|;:,.<>?
    /// @param enforceEachType: Whether to ensure that at least one character from each selected set is included
    /// @param             rng: A uniform random bit generator
    ///
    /// @return A randomly generated password string of the specified length
    ///
    /// @throws std::invalid_argument if @p length is zero
    /// @throws std::invalid_argument if none of the character sets are enabled
    ///
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
