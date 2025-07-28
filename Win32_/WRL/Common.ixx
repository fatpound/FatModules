module;

export module FatPound.Win32.WRL.Common;

#ifdef FATLIB_BUILDING_WITH_MSVC

import <wrl.h>;

export namespace wrl
{
    template <typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;
}

#endif

// module : private;
