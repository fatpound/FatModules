module;

export module FatPound.Algorithm.Sorting;

import std;

export namespace fatpound::algorithm
{
    template <std::unsigned_integral T>
    constexpr void CountingSort_Unchecked(std::vector<T>& inVec, std::vector<T>& outVec, const std::unsigned_integral auto& maxValue) noexcept
    {
        std::vector<T> Counts(maxValue + 1U, 0U);

        for (std::size_t i{}; i < inVec.size(); ++i)
        {
            ++Counts[inVec[i]];
        }

        std::inclusive_scan<>(Counts.begin(), Counts.end(), Counts.begin());

        for (auto i = static_cast<std::ptrdiff_t>(inVec.size() - 1U); i >= 0; --i)
        {
            const auto item = inVec[static_cast<std::size_t>(i)];

            --Counts[item]; // index optimization, decreasing opertion usually comes after the assignment, I do NOT do Counts[item] - 1 then --Counts[item] here.
            outVec[Counts[item]] = item;
        }
    }

    template <std::unsigned_integral T>
    constexpr void CountingSort(std::vector<T>& inVec, std::vector<T>& outVec)
    {
        if (inVec.empty())
        {
            throw std::runtime_error("Input Vector is empty!");
        }

        outVec.clear();
        outVec.resize(inVec.size());

        std::ranges::fill(outVec, 0U);

        CountingSort_Unchecked<>(inVec, outVec, std::ranges::max(inVec));
    }
}

module : private;
