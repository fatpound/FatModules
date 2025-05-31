module;

#include <FatSTL_Macros.hxx>

export module FatPound.Utility;

export import FatPound.Utility.Gfx;

export import FatPound.Utility.Color;
export import FatPound.Utility.Common;
export import FatPound.Utility.Surface;
export import FatPound.Utility.Timer;
export import FatPound.Utility.ViewXM;

import std;

namespace fatpound::utility
{
    template <bool Largest, std::totally_ordered T>
    constexpr auto Nth_LS_ElementUnique(const std::vector<T>& vec, const std::unsigned_integral auto& n) -> T
    {
        if (vec.size() < 1U)
        {
            throw std::runtime_error("vector has no elements!");
        }

        if (vec.size() < n)
        {
            throw std::runtime_error("n CANNOT be greater than vector size!");
        }

        if (n < 1U)
        {
            throw std::runtime_error("n CANNOT be less than 1!");
        }

        const std::set set(vec.cbegin(), vec.cend());

        std::conditional_t<Largest, std::set<T>::reverse_iterator, std::set<T>::iterator> it;

        if constexpr (Largest)
        {
            it = set.rbegin();
        }
        else
        {
            it = set.begin();
        }

        std::advance<>(it, n - 1);

        return *it;
    }
}

export namespace fatpound::utility
{
    template <std::floating_point FP = double, std::integral T>
    CX_MATH23
    auto ClockHandsAngle(T hours, T minutes) noexcept -> FP
    {
        if constexpr (std::signed_integral<T>)
        {
            hours   = std::abs(hours);
            minutes = std::abs(minutes);
        }

        hours   %= 12;
        minutes %= 60;

        const auto angle = std::fabs(static_cast<FP>((11 * minutes) - (60 * hours)) / static_cast<FP>(2.0));

        return (angle > 180) ? static_cast<FP>(360 - angle) : angle;
    }
    
    constexpr auto StrRev(const std::string& str) -> std::string
    {
        auto revstr = str;

        std::reverse(revstr.begin(), revstr.end());

        return revstr;
    }

    /**
     * @brief Time Complexity: O(nlogn)
    */
    template <std::totally_ordered T>
    constexpr auto NthLargestElementUnique(const std::vector<T>& vec, const std::unsigned_integral auto& n) -> T
    {
        return Nth_LS_ElementUnique<true>(vec, n);
    }

    /**
     * @brief Time Complexity: O(nlogn)
    */
    template <std::totally_ordered T>
    constexpr auto NthSmallestElementUnique(const std::vector<T>& vec, const std::unsigned_integral auto& n) -> T
    {
        return Nth_LS_ElementUnique<false>(vec, n);
    }
}

module : private;
