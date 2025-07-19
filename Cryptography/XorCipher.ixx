module;

export module FatPound.Cryptography.XorCipher;

import std;

export namespace fatpound::cryptography
{
    /// @brief Applies an XOR cipher to a range of values using a key and writes the result to an output iterator
    /// 
    /// @tparam        T: The integral type of the values to be outputted (defaults to char)
    /// @tparam      RNG: The type of the uniform random bit generator to use (defaults to std::minstd_rand)
    /// @tparam     InIt: The type of the  input iterator for the  input range
    /// @tparam    OutIt: The type of the output iterator for the output range
    /// 
    ///  @param    begin: Iterator to the beginning of the input range to encrypt or decrypt
    ///  @param      end: Iterator to the end of the input range
    ///  @param outBegin: Output iterator to the beginning of the destination range
    ///  @param      key: A Key to seed the random number generator for the XOR cipher
    /// 
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
                return static_cast<T>(static_cast<std::make_unsigned_t<T>>(val) xor rng());
            }
        );
    }
}

// module : private;
