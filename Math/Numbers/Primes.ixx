module;

export module FatPound.Math.Numbers.Primes;

import FatPound.Math.Numbers.Sets;

export namespace fatpound::math::numbers
{
    template <Natural N> constexpr auto IsPrime       (const N& num) noexcept -> bool
    {
        if (num < 4)
        {
            return num > 1;
        }

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
    template <Natural N> constexpr auto NextPrime     (const N& num) noexcept -> N
    {
        if (num < 5)
        {
            return 2 + (num > 2 ? 3 : static_cast<int>(num == 2));
        }

        auto x{num};

        if (x % 2 == 0)
        {
            ++x;

            while (not IsPrime<>(x))
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
            while (not IsPrime<>(x));
        }

        return x;
    }
    template <Natural N> constexpr auto PrevPrime     (const N& num) noexcept -> N
    {
        if (num < 5)
        {
            return num > 2 ? (num - 1) : 0;
        }

        auto x{num};

        if (x % 2 == 0)
        {
            --x;

            while (not IsPrime<>(x))
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
            while (not IsPrime<>(x));
        }

        return x;
    }
    template <Natural N> constexpr auto ClosestPrime  (const N& num) noexcept -> N
    {
        const auto prev = PrevPrime<>(num);
        const auto next = NextPrime<>(num);

        return (num not_eq 0) and ((num - prev) < (next - num)) ? prev : next;
    }
    template <Natural N> constexpr auto NthPrime      (const N& idx) noexcept -> N
    {
        if (idx < 2)
        {
            return (idx == 1) ? 2 : 0;
        }

        N i = 3;
        N counter = 1;

        while (true)
        {
            if (IsPrime<>(i))
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
    template <Natural N> constexpr auto NthSuperPrime (const N& idx) noexcept -> N
    {
        return idx == 0 ? 0 : NthPrime<>(NthPrime<>(idx));
    }
    template <Natural N> constexpr auto IsStrongPrime (const N& num) -> bool
    {
        return (num > 2) and IsPrime<>(num) and (num > ((PrevPrime<>(num) + NextPrime<>(num)) / 2));
    }
    
    template <Integer Z> constexpr auto IsPrime       (const Z& num) noexcept -> bool
    {
        return num < 0 ? false : IsPrime<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto NextPrime     (const Z& num) noexcept -> Z
    {
        return num < 0 ? 2 : NextPrime<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto PrevPrime     (const Z& num) noexcept -> Z
    {
        return num < 0 ? 0 : PrevPrime<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto ClosestPrime  (const Z& num) noexcept -> Z
    {
        return num < 0 ? 2 : ClosestPrime<::std::make_unsigned_t<Z>>(num);
    }
    template <Integer Z> constexpr auto NthPrime      (const Z& idx) noexcept -> Z
    {
        return idx < 0 ? 0 : NthPrime<::std::make_unsigned_t<Z>>(idx);
    }
    template <Integer Z> constexpr auto NthSuperPrime (const Z& idx) noexcept -> Z
    {
        return idx < 0 ? 0 : NthSuperPrime<::std::make_unsigned_t<Z>>(idx);
    }
    template <Integer Z> constexpr auto IsStrongPrime (const Z& num) -> bool
    {
        return num < 0 ? false : IsStrongPrime<std::make_unsigned_t<Z>>(num);
    }
}
