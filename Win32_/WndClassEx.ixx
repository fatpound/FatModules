module;

#include <FatWin32.hpp>

export module FatPound.Win32.WndClassEx;

import FatPound.Win32.IWindow;

import std;

using std::string_literals::operator ""s;

export namespace fatpound::win32
{
    class WndClassEx final
    {
    public:
        explicit WndClassEx(const std::wstring& clsName = L"#fat->pound.Default.Window.Class#"s)
            :
            m_hInstance_{ ::GetModuleHandle(nullptr) }
        {
            const WNDCLASSEX wcx
            {
                .cbSize = sizeof(wcx),
                .style = CS_OWNDC,
                .lpfnWndProc = &WndClassEx::HandleMsgSetup_,
                .cbClsExtra = 0,
                .cbWndExtra = 0,
                .hInstance = m_hInstance_,
                .hIcon = nullptr,
                .hCursor = ::LoadCursor(nullptr, IDC_ARROW),
                .hbrBackground = nullptr,
                .lpszMenuName = nullptr,
                .lpszClassName = clsName.c_str(),
                .hIconSm = nullptr
            };

            m_atom_ = ::RegisterClassEx(&wcx);

            if (m_atom_ == 0)
            {
                throw std::runtime_error{
                    "ATOM could not be created!\n\n"
                    "You might consider checking WNDCLASSEX::lpszClassName\n"
                    "It should have a unique name. If that's not the problem\n"
                    "Then check other parameters too."
                };
            }
        }

        explicit WndClassEx() = delete;
        explicit WndClassEx(const WndClassEx& src) = delete;
        explicit WndClassEx(WndClassEx&& src) = delete;

        auto operator = (const WndClassEx& src) -> WndClassEx& = delete;
        auto operator = (WndClassEx&& src)      -> WndClassEx& = delete;
        ~WndClassEx() noexcept
        {
            [[maybe_unused]]
            const auto&& retval = ::UnregisterClass(MAKEINTATOM(m_atom_), m_hInstance_);
        }


    public:
        auto GetAtom()     const noexcept -> ATOM
        {
            return m_atom_;
        }
        auto GetInstance() const noexcept -> HINSTANCE
        {
            return m_hInstance_;
        }


    protected:


    private:
        static auto CALLBACK HandleMsgSetup_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            if (msg == WM_NCCREATE)
            {
#if UNICODE
                using CREATESTRUCT = CREATESTRUCTW;
#else
                using CREATESTRUCT = CREATESTRUCTA;
#endif // UNICODE

                IWindow* const pWnd = static_cast<IWindow*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

                ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

#pragma warning (push)
#pragma warning (disable : 5039)
                ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WndClassEx::HandleMsgThunk_));
#pragma warning (pop)

                return ForwardMsg_(pWnd, hWnd, msg, wParam, lParam);
            }

            return ::DefWindowProc(hWnd, msg, wParam, lParam);
        }
        static auto CALLBACK HandleMsgThunk_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            IWindow* const pWnd = reinterpret_cast<IWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

            return ForwardMsg_(pWnd, hWnd, msg, wParam, lParam);
        }

        static auto ForwardMsg_(class IWindow* const pWnd, const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
        {
            return pWnd->HandleMessage_(hWnd, msg, wParam, lParam);
        }


    private:
        HINSTANCE m_hInstance_;
        ATOM m_atom_;
    };
}

module : private;