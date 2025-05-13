module;

#if FAT_BUILDING_WITH_MSVC

#include <FatWin32.hpp>
#include <wrl.h>

#endif

export module FatPound.Win32.WRL.Common;

#if FAT_BUILDING_WITH_MSVC

export namespace fatpound::win32::wrl
{
    template <typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;
}

#endif

module : private;
