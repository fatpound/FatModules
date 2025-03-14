module;

#if defined(_MSC_VER)
#include <FatWin32.hpp>
#endif

export module FatPound.Util.Common;

#if defined(_MSC_VER)

import std;

export namespace fatpound::util
{
    auto ToWString(const std::string& str) -> std::wstring
    {
        std::wstring wstr(str.size(), '\0');

        ::MultiByteToWideChar(
            CP_UTF8,
            0,
            str.c_str(),
            static_cast<int>(str.size()),
            wstr.data(),
            static_cast<int>(wstr.size())
        );

        return wstr;
    }
}

#endif

module : private;
