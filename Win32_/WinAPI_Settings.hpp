#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef _WIN32_WINNT
    #ifdef __clang__
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wreserved-macro-identifier"
    #endif
    
    #define _WIN32_WINNT _WIN32_WINNT_WIN10

    #ifdef __clang__
        #pragma clang diagnostic pop
    #endif
#endif

#include <sdkddkver.h>

#ifndef NOMINMAX
    #define NOMINMAX
#endif

#ifndef STRICT
    #define STRICT
#endif

#ifndef FATPOUND_FULL_WIN_TARGETED
    #define WIN32_LEAN_AND_MEAN
    #define NOGDICAPMASKS
    #define NOMENUS
    #define NOICONS
    #define NORASTEROPS
    #define OEMRESOURCE
    #define NOCLIPBOARD
    #define NOCTLMGR
    #define NODRAWTEXT
    #define NOKERNEL
    #define NOMEMMGR
    #define NOOPENFILE
    #define NOSCROLL
    #define NOSERVICE
    #define NOSOUND
    #define NOTEXTMETRIC
    #define NOWH
    #define NOCOMM
    #define NOKANJI
    #define NOHELP
    #define NOPROFILER
    #define NODEFERWINDOWPOS
    #define NOMCX
    #define NORPC
    #define NOPROXYSTUB
    #define NOIMAGE
    #define NOTAPE
#endif

#endif
