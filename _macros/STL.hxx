#pragma once

#include <version>

#ifdef __cpp_lib_constexpr_cmath
    #if __cpp_lib_constexpr_cmath == 202202L
        #define FATLIB_CMATH_CONSTEXPR23 constexpr
    #elif __cpp_lib_constexpr_cmath == 202306L
        #define FATLIB_CMATH_CONSTEXPR26 constexpr
    #endif
#else
    #define FATLIB_CMATH_CONSTEXPR23
    #define FATLIB_CMATH_CONSTEXPR26
#endif

#define CX_MATH23 FATLIB_CMATH_CONSTEXPR23
#define CX_MATH26 FATLIB_CMATH_CONSTEXPR26
