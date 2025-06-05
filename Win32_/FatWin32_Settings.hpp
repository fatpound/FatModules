#pragma once

#ifdef _MSC_VER

#ifndef _WIN32_WINNT
    #define _WIN32_WINNT _WIN32_WINNT_WIN10
#endif

#include <sdkddkver.h>

#ifndef NOMINMAX
    #define NOMINMAX
#endif

#ifndef STRICT
    #define STRICT
#endif

#ifndef FATPOUND_FULL_WIN_TARGETED // except NOMINMAX
    #define WIN32_LEAN_AND_MEAN    // for 16-bit Windows libraries, rarely used
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
//  #define NOMETAFILE
//  #define NOSYSMETRICS
//  #define NOSYSCOMMANDS
//  #define NOATOM
//  #define NOCOLOR
//  #define NONLS
//  #define NOVIRTUALKEYCODES
//  #define NOWINMESSAGES
//  #define NOWINSTYLES
//  #define NOKEYSTATES
//  #define NOSHOWWINDOW
//  #define NOGDI
//  #define NOUSER
//  #define NOMB
//  #define NOMSG
//  #define NOWINOFFSETS
#endif

#endif
