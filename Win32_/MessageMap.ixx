module;

#include <FatWin32.hpp>

export module FatPound.Win32.MessageMap;

import std;

export namespace fatpound::win32
{
    class MessageMap final
    {
    public:
        explicit MessageMap();
        explicit MessageMap(const MessageMap& src) = delete;
        explicit MessageMap(MessageMap&& src) = delete;

        auto operator = (const MessageMap& src) -> MessageMap& = delete;
        auto operator = (MessageMap&& src)      -> MessageMap& = delete;
        ~MessageMap() noexcept = default;


    public:
        auto operator () (const DWORD msg, const WPARAM wp, const LPARAM lp) const -> std::wstring;


    protected:


    private:
        std::unordered_map<DWORD, std::wstring> m_map_;
    };
}