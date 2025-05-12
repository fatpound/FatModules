module;

export module FatPound.DSA.Cryptography.XorCipher;

import std;

export namespace fatpound::dsa::cryptography
{
    template <std::integral T = char, std::uniform_random_bit_generator RNG = std::minstd_rand, std::input_iterator InIt, std::output_iterator<T> OutIt>
    void ApplyXorCipherWithKey(const InIt& begin, const InIt& end, const OutIt& outBegin, const std::size_t& key)
    {
        RNG rng{ static_cast<RNG::result_type>(key) };

        std::transform<>(
            begin,
            end,
            outBegin,
            [&rng](const T& val) noexcept -> T
            {
                return static_cast<T>(val xor rng());
            }
        );
    }
}

module : private;
