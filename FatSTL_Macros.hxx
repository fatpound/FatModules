#pragma once

#include <version>

#ifdef __cpp_lib_constexpr_cmath
    #if __cpp_lib_constexpr_cmath == 202202L
        #ifndef FAT_CMATH_CONSTEXPR23
            #define FAT_CMATH_CONSTEXPR23 constexpr
        #endif
    #elif __cpp_lib_constexpr_cmath == 202306L
        #ifndef FAT_CMATH_CONSTEXPR26
            #define FAT_CMATH_CONSTEXPR26 constexpr
        #endif
    #endif
#else
    #ifndef FAT_CMATH_CONSTEXPR23
        #define FAT_CMATH_CONSTEXPR23
    #endif
    #ifndef FAT_CMATH_CONSTEXPR26
        #define FAT_CMATH_CONSTEXPR26
    #endif
#endif

#ifndef CX_MATH23
    #define CX_MATH23 FAT_CMATH_CONSTEXPR23
#endif

#ifndef CX_MATH26
    #define CX_MATH26 FAT_CMATH_CONSTEXPR26
#endif