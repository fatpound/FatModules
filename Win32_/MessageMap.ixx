module;
#include "FatWin32_.hpp"

export module Win32_MessageMap;

import std;

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