module;

#include <FatWin32.hpp>

export module FatPound.Win32.Common;

import std;

export namespace fatpound::win32
{
#ifdef UNICODE
    using CREATESTRUCT_t = ::CREATESTRUCTW;
    using STR_t          = ::LPCWSTR;
#else
    using CREATESTRUCT_t = ::CREATESTRUCTA;
    using STR_t          = ::LPCSTR;
#endif

    auto ModuleHandleOf(const STR_t& cstr = nullptr) -> HINSTANCE
    {
        const auto& hInstance{ ::GetModuleHandle(cstr) };

        if (hInstance == nullptr)
        {
            throw std::runtime_error("Error occured when obtaining hInstance [GetModuleHandle]");
        }

        return hInstance;
    }
}

module : private;