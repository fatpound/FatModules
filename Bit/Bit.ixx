module;

export module FatPound.Bit;

import std;

namespace fatpound::bit
{
    /// @brief Generates a bitmask with bits set from startBit to endBit (inclusive) for unsigned integral types
    /// 
    /// @tparam   ForOne: If true, the mask has ones in the specified range; if false, the mask has zeros in the specified range and ones elsewhere
    /// @tparam        T: The unsigned integral type to use for the mask (default => std::size_t)
    /// 
    ///  @param   endBit: The index of the  most significant bit to include in the mask
    ///  @param startBit: The index of the least significant bit to include in the mask
    /// 
    /// @return A value of type T representing the generated bitmask
    /// 
    template <bool ForOne, std::unsigned_integral T = std::size_t>
    constexpr auto Mask_(const T& endBit, const T& startBit) -> T
    {
        if constexpr (ForOne)
        {
            if (startBit > endBit)
            {
                return T{ 0 };
            }

            return ((T{ 1 } << (endBit - startBit + 1U)) - 1U) << startBit;
        }
        else
        {
            return compl Mask_<not ForOne>(endBit, startBit);
        }
    }
}

export namespace fatpound::bit
{
    /// @brief Generates a bitmask with ones from startBit to endBit (inclusive)
    /// 
    /// @tparam        T: The unsigned integral type to use for the bitmask. Defaults to std::size_t
    /// 
    ///  @param   endBit: The position one past the last bit to set to one
    ///  @param startBit: The position of the first bit to set to one
    /// 
    /// @return A value of type T with bits set to one from startBit to endBit (inclusive)
    /// 
    template <std::unsigned_integral T = std::size_t>
    constexpr auto OneMask(const T& endBit, const T& startBit) -> T
    {
        return Mask_<true>(endBit, startBit);
    }



    /// @brief Generates a bitmask with zeros from startBit to endBit (inclusive), and ones elsewhere
    /// 
    /// @tparam        T: The unsigned integral type used for the bitmask. Defaults to std::size_t
    /// 
    ///  @param   endBit: The index of the  most significant bit in the range to be zeroed
    ///  @param startBit: The index of the least significant bit in the range to be zeroed
    /// 
    /// @return A value of type T with bits from startBit to endBit set to zero, and all other bits set to one
    /// 
    template <std::unsigned_integral T = std::size_t>
    constexpr auto ZeroMask(const T& endBit, const T& startBit) -> T
    {
        return Mask_<false>(endBit, startBit);
    }
}

// module : private;

namespace fatpound::bit
{
    static_assert( OneMask<>( 7U,  0U) == 0x000000FFU);
    static_assert( OneMask<>(15U,  8U) == 0x0000FF00U); // (== OneMask<>( 7U,  0U) << 8U)
    static_assert( OneMask<>(23U, 16U) == 0x00FF0000U); // (== OneMask<>(15U,  8U) << 8U)
    static_assert( OneMask<>(31U, 24U) == 0xFF000000U); // (== OneMask<>(23U, 16U) << 8U)

    static_assert(ZeroMask<>( 7U,  0U) == 0xFFFFFF00U); //  == compl OneMask<>( 7U,  0U)
    static_assert(ZeroMask<>(15U,  8U) == 0xFFFF00FFU); //  == compl OneMask<>(15U,  8U)
    static_assert(ZeroMask<>(23U, 16U) == 0xFF00FFFFU); //  == compl OneMask<>(23U, 16U)
    static_assert(ZeroMask<>(31U, 24U) == 0x00FFFFFFU); //  == compl OneMask<>(31U, 24U)
}
