#pragma once

#include <version>

#ifdef __cpp_lib_constexpr_cmath
    #if __cpp_lib_constexpr_cmath == 202202L
        #define FAT_CMATH_CONSTEXPR23 constexpr
    #elif __cpp_lib_constexpr_cmath == 202306L
        #define FAT_CMATH_CONSTEXPR26 constexpr
    #endif
#else
    #define FAT_CMATH_CONSTEXPR23
    #define FAT_CMATH_CONSTEXPR26
#endif

#define CX_MATH23 FAT_CMATH_CONSTEXPR23
#define CX_MATH26 FAT_CMATH_CONSTEXPR26
