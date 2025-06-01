module;

export module FatPound.Algorithm.Searching;

import std;

namespace fatpound::algorithm
{
    /// @brief Time Complexity: O(nlogn)
    ///
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

        std::conditional_t<Largest, typename std::set<T>::reverse_iterator, typename std::set<T>::iterator> it;

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

export namespace fatpound::algorithm
{
    /// @brief Time Complexity: O(nlogn)
    ///
    template <std::totally_ordered T>
    constexpr auto NthLargestElementUnique(const std::vector<T>& vec, const std::unsigned_integral auto& n) -> T
    {
        return Nth_LS_ElementUnique<true>(vec, n);
    }

    /// @brief Time Complexity: O(nlogn)
    ///
    template <std::totally_ordered T>
    constexpr auto NthSmallestElementUnique(const std::vector<T>& vec, const std::unsigned_integral auto& n) -> T
    {
        return Nth_LS_ElementUnique<false>(vec, n);
    }
}

module : private;
