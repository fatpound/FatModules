module;

#include <FatWin32_.hpp>

export module FatPound.Win32.Window_;

import FatPound.Win32.IO;
import FatPound.Math;
import FatPound.Util;

import std;

export namespace fatpound::win32
{
    class Window_ final
    {
#ifdef UNICODE
        using str_t = const wchar_t*;
#else
        using str_t = const char*;
#endif // UNICODE
        
    public:
        explicit Window_(const str_t title, const NAMESPACE_UTIL::ScreenSizeInfo& dimensions);

        explicit Window_() = delete;
        explicit Window_(const Window_& src) = delete;
        explicit Window_(Window_&& src) = delete;

        auto operator = (const Window_& src) -> Window_& = delete;
        auto operator = (Window_&& src)      -> Window_& = delete;
        ~Window_() noexcept;


    public:
        static auto ProcessMessages() noexcept -> std::optional<WPARAM>;


    public:
        template <NAMESPACE_MATH_CONCEPTS::number_set::Rational Q>
        auto GetClientWidth() const noexcept
        {
            return static_cast<Q>(m_client_size_.m_width);
        }

        template <NAMESPACE_MATH_CONCEPTS::number_set::Rational Q>
        auto GetClientHeight() const noexcept
        {
            return static_cast<Q>(m_client_size_.m_height);
        }


    public:
        auto GetHwnd() const noexcept -> HWND;

        auto IsActive()    const noexcept -> bool;
        auto IsMinimized() const noexcept -> bool;

        void SetTitle(const std::wstring& title);
        void ShowMessageBox(const std::wstring& message, const std::wstring& title, const UINT error_flags) const noexcept;
        void Kill() noexcept;


    public:
        NAMESPACE_IO::Mouse m_mouse;
        NAMESPACE_IO::Keyboard m_keyboard;

        
    protected:


    private:
        class WndClass_ final
        {
        public:
            static auto GetInstance() noexcept -> HINSTANCE;

            static auto GetName() noexcept -> str_t;

        protected:

        private:
            explicit WndClass_() noexcept;
            explicit WndClass_(const WndClass_& src) = delete;
            explicit WndClass_(WndClass_&& src) = delete;

            auto operator = (const WndClass_& src) -> WndClass_& = delete;
            auto operator = (WndClass_&& src)      -> WndClass_& = delete;
            ~WndClass_() noexcept;

        private:
            static auto CALLBACK HandleMsgSetup_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT;
            static auto CALLBACK HandleMsgThunk_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT;

        private:
            HINSTANCE m_hInst_;

#ifdef UNICODE
            static constexpr str_t s_wndClassName_ = L"FatPound Default WndClass";
#else
            static constexpr str_t s_wndClassName_ =  "FatPound Default WndClass";
#endif // UNICODE
        };


    private:
        auto HandleMsg_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT;


    private:
        HWND m_hWnd_;

        const NAMESPACE_UTIL::ScreenSizeInfo m_client_size_;

        static constexpr bool s_cursorEnabled_ = true;
    };
}