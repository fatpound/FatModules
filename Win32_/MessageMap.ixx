module;
#include "FatWin32_.hpp"

export module Win32_MessageMap;

#if _MSVC_LANG > 202002L
import std;
#elif _MSVC_LANG == 202002L
import std.core;
#else
#error MSVC /std:c++20 or newer option required
#endif // _MSVC_LANG > 202002L

export namespace fatpound::win32
{
    class MessageMap final
    {
    public:
        MessageMap() noexcept;


    public:
        auto operator () (DWORD msg, WPARAM wp, LPARAM lp) const noexcept -> std::string;


    protected:


    private:
        std::unordered_map<DWORD, std::string> map_;
    };
}