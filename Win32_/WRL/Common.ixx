module;

#if FAT_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <FatWin32.hpp>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.WRL.Common;

#if FAT_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <wrl.h>;
#endif

export namespace fatpound::win32::wrl
{
    template <typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;
}

#endif

module : private;
