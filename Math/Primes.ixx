module;

export module FatPound.Math:Primes;

import <cassert>;

import std;

export namespace fatpound::math
{
    template <std::signed_integral N>
    bool IsPrime(const N& num)
    {
        if (num < 4)
        {
            return num > 1;
        }

        if (num % 2 == 0 || num % 3 == 0)
        {
            return false;
        }

        const N m = num + 1;

        for (N i = 5; (i * i) < m; i += 6)
        {
            if ((num % i == 0) || (num % (i + 2) == 0))
            {
                return false;
            }
        }

        return true;
    }

    template <std::signed_integral N>
    auto NextPrime(const N& num) -> N
    {
        if (num % 2 == 0)
        {
            ++num;
        }

        while (not IsPrime(num))
        {
            num += 2;
        }

        return num;
    }

    template <std::signed_integral N>
    auto PrevPrime(const N& num) -> N
    {
        if (num % 2 == 0)
        {
            --num;
        }

        while (not IsPrime(num))
        {
            num -= 2;
        }

        return num;
    }

    template <std::signed_integral N>
    auto NthPrime(const N& num) -> N
    {
        assert(num > 0);

        if (num == 1)
        {
            return 2;
        }

        N i = 3;
        N counter = 1;

        while (true)
        {
            if (IsPrime(i))
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