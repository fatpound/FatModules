module;

export module FatPound.Win32.WRL.Common;

#ifdef _MSC_VER

import <wrl.h>;

export namespace fatpound::win32::wrl
{
    template <typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;
}

export namespace wrl = fatpound::win32::wrl;

#endif

module : private;
