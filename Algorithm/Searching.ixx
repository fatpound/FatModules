module;

export module FatPound.Algorithm.Searching;

import std;

namespace fatpound::algorithm
{
    /// @brief Returns the n-th largest or smallest unique element from a vector. Time Complexity: O(nlogn)
    ///
    /// @tparam Largest: If true, retrieves the n-th largest unique element; if false, retrieves the n-th smallest
    /// @tparam       T: The type of elements in the vector, which must be totally ordered
    /// 
    ///  @param     vec: The vector of elements to search
    ///  @param       n: The 1-based index specifying which unique element to retrieve
    ///
    /// @return The n-th largest or smallest unique element in the vector, depending on the value of Largest
    /// 
    template <bool Largest, std::totally_ordered T>
    constexpr auto Nth_LS_UniqueElement(const std::vector<T>& vec, const std::unsigned_integral auto& n) -> T
    {
        if (vec.empty())
        {
            throw std::runtime_error("The vector has NO elements!");
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
    /// @brief Returns the n-th largest unique element from a vector. Time Complexity: O(nlogn)
    ///
    /// @tparam   T: The type of elements in the vector, which must support total ordering
    /// 
    ///  @param vec: The vector of elements to search
    ///  @param   n: The 1-based index (from largest) of the unique element to retrieve
    /// 
    /// @return The n-th largest unique element in the vector
    /// 
    template <std::totally_ordered T>
    constexpr auto NthLargestUniqueElement(const std::vector<T>& vec, const std::unsigned_integral auto& n) -> T
    {
        return Nth_LS_UniqueElement<true>(vec, n);
    }



    /// @brief Returns the n-th smallest unique element from a vector. Time Complexity: O(nlogn)
    ///
    /// @tparam   T: The type of elements in the vector, which must satisfy the std::totally_ordered concept
    /// 
    ///  @param vec: A vector containing elements to search
    ///  @param   n: The 1-based index specifying which smallest unique element to retrieve
    ///
    /// @return The n-th smallest unique element in the vector
    /// 
    template <std::totally_ordered T>
    constexpr auto NthSmallestUniqueElement(const std::vector<T>& vec, const std::unsigned_integral auto& n) -> T
    {
        return Nth_LS_UniqueElement<false>(vec, n);
    }
}

// module : private;
