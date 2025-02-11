module;

export module FatPound.Math.Primes;

import std;

export namespace fatpound::math
{
    template <std::integral N> constexpr auto IsPrime  (const N& num) -> bool
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
    template <std::integral N> constexpr auto NextPrime(const N& num) -> N
    {
        N x{num};

        if (x % 2 == 0)
        {
            ++x;
        }

        while (not IsPrime<>(x))
        {
            x += 2;
        }

        return x;
    }
    template <std::integral N> constexpr auto PrevPrime(const N& num) -> N
    {
        N x{num};

        if (x % 2 == 0)
        {
            --x;
        }

        while (not IsPrime<>(x))
        {
            x -= 2;
        }

        return x;
    }
    template <std::integral N> constexpr auto NthPrime (const N& num) -> N
    {
        if (num == 1)
        {
            return 2;
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
}

module : private;