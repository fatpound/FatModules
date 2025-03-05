module;

export module FatPound.Math.Numbers.Primes;

export import FatPound.Math.Numbers.Sets;

export namespace fatpound::math::inline primes
{
    template <numbers::Natural N> constexpr auto IsPrime      (const N& num) noexcept -> bool
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
    template <numbers::Natural N> constexpr auto NextPrime    (const N& num) noexcept -> N
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
    template <numbers::Natural N> constexpr auto PrevPrime    (const N& num) noexcept -> N
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
    template <numbers::Natural N> constexpr auto NthPrime     (const N& num) noexcept -> N
    {
        if (num < 2)
        {
            return (num == 1) ? 2 : 0;
        }

        N i = 3;
        N counter = 1;

        while (true)
        {
            if (IsPrime<>(i))
            {
                ++counter;

                if (counter == num)
                {
                    break;
                }
            }

            i += 2;
        }

        return i;
    }
    template <numbers::Natural N> constexpr auto ClosestPrime (const N& num) noexcept -> N
    {
        const auto prev = PrevPrime<>(num);
        const auto next = NextPrime<>(num);

        return (num not_eq 0) and ((num - prev) < (next - num)) ? prev : next;
    }
}
