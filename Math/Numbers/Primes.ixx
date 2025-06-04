module;

export module FatPound.Math.Numbers.Primes;

import std;

export namespace fatpound::math::numbers
{
    // _GT* postfix => The function will assume that the function argument value is greater than N

    template <std::unsigned_integral T> constexpr auto IsPrime_GT4        (const T& num) noexcept -> bool
    {
        if (num % 2 == 0 or num % 3 == 0)
        {
            return false;
        }

        for (T i{5}; (i * i) <= num; i += 6)
        {
            if ((num % i == 0) or (num % (i + 2) == 0))
            {
                return false;
            }
        }

        return true;
    }
    template <std::unsigned_integral T> constexpr auto IsPrime            (const T& num) noexcept -> bool
    {
        if (num < 5)
        {
            return num > 1 and num not_eq 4;
        }

        return IsPrime_GT4<>(num);
    }
    template <std::unsigned_integral T> constexpr auto PrevPrime_GT5      (const T& num) noexcept -> T
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
    template <std::unsigned_integral T> constexpr auto PrevPrime          (const T& num) noexcept -> T
    {
        if (num < 6)
        {
            return num > 2 ? (num - 1 - static_cast<T>(num == 5)) : 0;
        }

        return PrevPrime_GT5<>(num);
    }
    template <std::unsigned_integral T> constexpr auto NextPrime_GT4      (const T& num) noexcept -> T
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
    template <std::unsigned_integral T> constexpr auto NextPrime          (const T& num) noexcept -> T
    {
        if (num < 5)
        {
            return 2 + (num > 2 ? 3 : static_cast<T>(num == 2));
        }

        return NextPrime_GT4<>(num);
    }
    template <std::unsigned_integral T> constexpr auto ClosestPrime_GT5   (const T& num) noexcept -> T
    {
        const auto prev = PrevPrime_GT5<>(num);
        const auto next = NextPrime_GT4<>(num);

        return ((num - prev) < (next - num)) ? prev : next;
    }
    template <std::unsigned_integral T> constexpr auto ClosestPrime       (const T& num) noexcept -> T
    {
        if (num < 4)
        {
            return 2 + static_cast<T>(num == 2);
        }
        
        if (num < 7)
        {
            return 3 + (static_cast<T>(num == 6) * 2);
        }

        return ClosestPrime_GT5<>(num);
    }
    template <std::unsigned_integral T> constexpr auto NthPrime_GT2       (const T& idx) noexcept -> T
    {
        T i = 5;
        T counter = 2;

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
    template <std::unsigned_integral T> constexpr auto NthPrime           (const T& idx) noexcept -> T
    {
        if (idx < 3)
        {
            return (idx == 0) ? 0 : (2 + static_cast<T>(idx == 2));
        }

        return NthPrime_GT2<>(idx);
    }
    template <std::unsigned_integral T> constexpr auto NthSuperPrime_GT2  (const T& idx) noexcept -> T
    {
        return NthPrime_GT2<>(NthPrime_GT2<>(idx));
    }
    template <std::unsigned_integral T> constexpr auto NthSuperPrime      (const T& idx) noexcept -> T
    {
        if (idx < 3)
        {
            if (idx == 0)
            {
                return 0;
            }

            return idx == 1 ? 3 : 5;
        }

        return NthSuperPrime_GT2<>(idx);
    }
    template <std::unsigned_integral T> constexpr auto IsStrongPrime_GT10 (const T& num) -> bool
    {
        return IsPrime_GT4<>(num) and (num > ((PrevPrime_GT5<>(num) + NextPrime_GT4<>(num)) / 2));
    }
    template <std::unsigned_integral T> constexpr auto IsStrongPrime      (const T& num) -> bool
    {
        if (num < 11)
        {
            return false;
        }

        return IsStrongPrime_GT10<>(num);
    }
    
    template <std::signed_integral T>   constexpr auto IsPrime_GT4        (const T& num) noexcept -> bool
    {
        return IsPrime_GT4<std::make_unsigned_t<T>>(num);
    }
    template <std::signed_integral T>   constexpr auto IsPrime            (const T& num) noexcept -> bool
    {
        return num < 2 ? false : IsPrime<std::make_unsigned_t<T>>(num);
    }
    template <std::signed_integral T>   constexpr auto PrevPrime_GT5      (const T& num) noexcept -> T
    {
        return PrevPrime_GT5<std::make_unsigned_t<T>>(num);
    }
    template <std::signed_integral T>   constexpr auto PrevPrime          (const T& num) noexcept -> T
    {
        return num < 3 ? 0 : PrevPrime<std::make_unsigned_t<T>>(num);
    }
    template <std::signed_integral T>   constexpr auto NextPrime_GT4      (const T& num) noexcept -> T
    {
        return NextPrime_GT4<std::make_unsigned_t<T>>(num);
    }
    template <std::signed_integral T>   constexpr auto NextPrime          (const T& num) noexcept -> T
    {
        return num < 2 ? 2 : NextPrime<std::make_unsigned_t<T>>(num);
    }
    template <std::signed_integral T>   constexpr auto ClosestPrime_GT5   (const T& num) noexcept -> T
    {
        return ClosestPrime_GT5<std::make_unsigned_t<T>>(num);
    }
    template <std::signed_integral T>   constexpr auto ClosestPrime       (const T& num) noexcept -> T
    {
        return num < 2 ? 2 : ClosestPrime<std::make_unsigned_t<T>>(num);
    }
    template <std::signed_integral T>   constexpr auto NthPrime_GT2       (const T& idx) noexcept -> T
    {
        return NthPrime_GT2<std::make_unsigned_t<T>>(idx);
    }
    template <std::signed_integral T>   constexpr auto NthPrime           (const T& idx) noexcept -> T
    {
        return idx < 1 ? 0 : NthPrime<std::make_unsigned_t<T>>(idx);
    }
    template <std::signed_integral T>   constexpr auto NthSuperPrime_GT2  (const T& idx) noexcept -> T
    {
        return NthSuperPrime_GT2<std::make_unsigned_t<T>>(idx);
    }
    template <std::signed_integral T>   constexpr auto NthSuperPrime      (const T& idx) noexcept -> T
    {
        return idx < 1 ? 0 : NthSuperPrime<std::make_unsigned_t<T>>(idx);
    }
    template <std::signed_integral T>   constexpr auto IsStrongPrime_GT10 (const T& num) -> bool
    {
        return IsStrongPrime_GT10<std::make_unsigned_t<T>>(num);
    }
    template <std::signed_integral T>   constexpr auto IsStrongPrime      (const T& num) -> bool
    {
        return num < 3 ? false : IsStrongPrime<std::make_unsigned_t<T>>(num);
    }
}

module : private;
