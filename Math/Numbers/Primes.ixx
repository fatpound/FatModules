module;

export module FatPound.Math.Numbers.Primes;

import FatPound.Math.Numbers.Sets;

export namespace fatpound::math::numbers
{
    template <Natural N> constexpr auto IsPrime            (const N& num) noexcept -> bool
    {
        if (num < 5)
        {
            return num > 1 and num not_eq 4;
        }

        return IsPrime_GT4<>(num);
    }
    template <Natural N> constexpr auto IsPrime_GT4        (const N& num) noexcept -> bool
    {
        if (num % 2 == 0 or num % 3 == 0)
        {
            return false;
        }

        for (N i{5}; (i * i) <= num; i += 6)
        {
            if ((num % i == 0) or (num % (i + 2) == 0))
            {
                return false;
            }
        }

        return true;
    }
    template <Natural N> constexpr auto NextPrime          (const N& num) noexcept -> N
    {
        if (num < 5)
        {
            return 2 + (num > 2 ? 3 : static_cast<int>(num == 2));
        }

        return NextPrime_GT4<>(num);
    }
    template <Natural N> constexpr auto NextPrime_GT4      (const N& num) noexcept -> N
    {
        auto x{num};

        if (x % 2 == 0)
        {
            ++x;

            while (not IsPrime_GT4<>(x))
            {
                x += 2;
            }
        }
        else
        {
            do
            {
                x += 2;
            }
            while (not IsPrime_GT4<>(x));
        }

        return x;
    }
    template <Natural N> constexpr auto PrevPrime          (const N& num) noexcept -> N
    {
        if (num < 6)
        {
            return num > 2 ? (num - 1 - static_cast<N>(num == 5)) : 0;
        }

        return PrevPrime_GT5<>(num);
    }
    template <Natural N> constexpr auto PrevPrime_GT5      (const N& num) noexcept -> N
    {
        auto x{num};

        if (x % 2 == 0)
        {
            --x;

            while (not IsPrime_GT4<>(x))
            {
                x -= 2;
            }
        }
        else
        {
            do
            {
                x -= 2;
            }
            while (not IsPrime_GT4<>(x));
        }

        return x;
    }
    template <Natural N> constexpr auto ClosestPrime       (const N& num) noexcept -> N
    {
        if (num < 4)
        {
            return 2 + static_cast<N>(num == 2);
        }
        
        if (num < 7)
        {
            return 3 + static_cast<N>(num == 6) * 2;
        }

        return ClosestPrime_GT5<>(num);
    }
    template <Natural N> constexpr auto ClosestPrime_GT5   (const N& num) noexcept -> N
    {
        const auto prev = PrevPrime_GT5<>(num);
        const auto next = NextPrime_GT4<>(num);

        return ((num - prev) < (next - num)) ? prev : next;
    }
    template <Natural N> constexpr auto NthPrime           (const N& idx) noexcept -> N
    {
        if (idx < 3)
        {
            return (idx == 0) ? 0 : (2 + static_cast<N>(idx == 3));
        }

        return NthPrime_GT2<>(idx);
    }
    template <Natural N> constexpr auto NthPrime_GT2       (const N& idx) noexcept -> N
    {
        N i = 5;
        N counter = 2;

        while (true)
        {
            if (IsPrime_GT4<>(i))
            {
                ++counter;

                if (counter == idx)
                {
                    break;
                }
            }

            i += 2;
        }

        return i;
    }
    template <Natural N> constexpr auto NthSuperPrime      (const N& idx) noexcept -> N
    {
        if (idx < 3)
        {
            return idx == 0 ? 0 : (idx == 1 ? 3 : 5);
        }

        return NthSuperPrime_GT2<>(idx);
    }
    template <Natural N> constexpr auto NthSuperPrime_GT2  (const N& idx) noexcept -> N
    {
        return NthPrime_GT2<>(NthPrime_GT2<>(idx));
    }
    template <Natural N> constexpr auto IsStrongPrime      (const N& num) -> bool
    {
        if (num < 11)
        {
            return false;
        }

        return IsStrongPrime_GT10<>(num);
    }
    template <Natural N> constexpr auto IsStrongPrime_GT10 (const N& num) -> bool
    {
        return IsPrime_GT4<>(num) and (num > ((PrevPrime_GT5<>(num) + NextPrime_GT4<>(num)) / 2));
    }
    
    template <Integer Z> constexpr auto IsPrime            (const Z& num) noexcept -> bool
    {
        return num < 2 ? false : IsPrime<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto IsPrime_GT4        (const Z& num) noexcept -> bool
    {
        return IsPrime_GT4<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto NextPrime          (const Z& num) noexcept -> Z
    {
        return num < 2 ? 2 : NextPrime<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto NextPrime_GT4      (const Z& num) noexcept -> Z
    {
        return NextPrime_GT4<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto PrevPrime          (const Z& num) noexcept -> Z
    {
        return num < 3 ? 0 : PrevPrime<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto PrevPrime_GT5      (const Z& num) noexcept -> Z
    {
        return PrevPrime_GT5<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto ClosestPrime       (const Z& num) noexcept -> Z
    {
        return num < 2 ? 2 : ClosestPrime<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto ClosestPrime_GT5   (const Z& num) noexcept -> Z
    {
        return ClosestPrime_GT5<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto NthPrime           (const Z& idx) noexcept -> Z
    {
        return idx < 1 ? 0 : NthPrime<::std::make_unsigned_t<Z>>(idx);
    }
    template <Integer Z> constexpr auto NthPrime_GT2       (const Z& idx) noexcept -> Z
    {
        return NthPrime_GT2<::std::make_unsigned_t<Z>>(idx);
    }
    template <Integer Z> constexpr auto NthSuperPrime      (const Z& idx) noexcept -> Z
    {
        return idx < 1 ? 0 : NthSuperPrime<::std::make_unsigned_t<Z>>(idx);
    }
    template <Integer Z> constexpr auto NthSuperPrime_GT2  (const Z& idx) noexcept -> Z
    {
        return NthSuperPrime_GT2<::std::make_unsigned_t<Z>>(idx);
    }
    template <Integer Z> constexpr auto IsStrongPrime      (const Z& num) -> bool
    {
        return num < 3 ? false : IsStrongPrime<std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto IsStrongPrime_GT10 (const Z& num) -> bool
    {
        return IsStrongPrime_GT10<std::make_unsigned_t<Z>>(num);
    }
}

module : private;
