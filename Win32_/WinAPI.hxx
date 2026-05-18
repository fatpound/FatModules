#pragma once

#define FATPOUND_FULL_WIN_TARGETED
#include <Win32_/FatWin.hpp>
#undef FATPOUND_FULL_WIN_TARGETED
#include <gdiplus.h>
#include <combaseapi.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <xaudio2.h>

#pragma comment(lib, "gdiplus")
#pragma comment(lib, "mfplat")
#pragma comment(lib, "mfreadwrite")
#pragma comment(lib, "mfuuid")
#pragma comment(lib, "xaudio2")

import FatPound.Win32.Common;
