module;

export module FatPound.Util.Common;

#if FAT_BUILDING_WITH_MSVC

import <FatWin32.hxx>;

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
