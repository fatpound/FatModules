module;

#include <FatWin32_.hpp>

#define WINDOW_RECT_WIDTH       (rect.right - rect.left)
#define WINDOW_RECT_HEIGHT      (rect.bottom - rect.top)

#define CLIENT_WIDTH            static_cast<LONG>(m_client_size_.m_width)
#define CLIENT_HEIGHT           static_cast<LONG>(m_client_size_.m_height)

#if IN_RELEASE

#define WINDOW_WIDTH            CLIENT_WIDTH
#define WINDOW_HEIGHT           CLIENT_HEIGHT
#define WINDOW_STYLE            WS_POPUP
#define WINDOW_POSITION_X       CW_USEDEFAULT
#define WINDOW_POSITION_Y       CW_USEDEFAULT

#else

#define WINDOW_WIDTH            WINDOW_RECT_WIDTH
#define WINDOW_HEIGHT           WINDOW_RECT_HEIGHT
#define WINDOW_STYLE            WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX
#define WINDOW_POSITION_X       rect.left
#define WINDOW_POSITION_Y       rect.top

#endif // IN_RELEASE

module FatPound.Win32.Window;

namespace fatpound::win32
{
    // Window
    
    Window::Window(const str_t title, const NAMESPACE_UTIL::ScreenSizeInfo& dimensions)
        :
        m_client_size_{ dimensions }
    {
#if IN_DEBUG

        RECT rect{};
        rect.left = 150;
        rect.right = CLIENT_WIDTH + rect.left;
        rect.top = 150;
        rect.bottom = CLIENT_HEIGHT + rect.top;

        ::AdjustWindowRect(&rect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

#endif // IN_DEBUG

        m_hWnd_ = ::CreateWindow(
            WndClass_::GetName(),
            title,
            WINDOW_STYLE,
            WINDOW_POSITION_X,
            WINDOW_POSITION_Y,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            nullptr,
            nullptr,
            WndClass_::GetInstance(),
            this
        );

        if (m_hWnd_ == nullptr) [[unlikely]]
        {
            throw std::runtime_error("Error occured when creating HWND!");
        }

        ::ShowWindow(m_hWnd_, SW_SHOWDEFAULT);
        ::UpdateWindow(m_hWnd_);
    }
    Window::~Window()
    {
        ::DestroyWindow(m_hWnd_);
    }

    auto Window::ProcessMessages() noexcept -> std::optional<WPARAM>
    {
        MSG msg{};

        while (::PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) [[unlikely]]
            {
                return msg.wParam;
            }

            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        return std::nullopt;
    }

    auto Window::GetHwnd() const noexcept -> HWND
    {
        return m_hWnd_;
    }

    auto Window::IsActive()    const noexcept -> bool
    {
        return ::GetActiveWindow() == m_hWnd_;
    }
    auto Window::IsMinimized() const noexcept -> bool
    {
        return ::IsIconic(m_hWnd_) not_eq 0;
    }

    void Window::SetTitle(const std::wstring& title)
    {
        if (::SetWindowText(m_hWnd_, title.c_str()) == 0) [[unlikely]]
        {
            throw std::runtime_error("Could NOT set the Window Text!");
        }
    }
    void Window::ShowMessageBox(const std::wstring& message, const std::wstring& title, const UINT error_flags) const noexcept
    {
        ::MessageBox(m_hWnd_, message.c_str(), title.c_str(), error_flags);
    }
    void Window::Kill() noexcept
    {
        ::PostQuitMessage(0);
    }

    auto Window::HandleMsg_(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        switch (msg)
        {
        case WM_CLOSE:
            Kill();
            return 0;

        case WM_KILLFOCUS:
            m_keyboard.ClearKeyStateBitset_();
            break;

            /******** KEYBOARD MESSAGES ********/
        case WM_KEYDOWN: [[fallthrough]];
        case WM_SYSKEYDOWN:
            if (wParam == VK_ESCAPE)
            {
                Kill();
                return 0;
            }

            if ((not (lParam bitand 0x40000000)) or m_keyboard.AutoRepeatIsEnabled())
            {
                m_keyboard.OnKeyPressed_(static_cast<unsigned char>(wParam));
            }
            break;

        case WM_KEYUP: [[fallthrough]];
        case WM_SYSKEYUP:
            m_keyboard.OnKeyReleased_(static_cast<unsigned char>(wParam));
            break;

        case WM_CHAR:
            m_keyboard.OnChar_(static_cast<unsigned char>(wParam));
            break;
            /******** END KEYBOARD MESSAGES ********/


            /******** MOUSE MESSAGES ********/
        case WM_MOUSEMOVE:
        {
            const POINTS pt = MAKEPOINTS(lParam);

            if (pt.x >= 0
                and
                pt.x < static_cast<SHORT>(m_client_size_.m_width)
                and
                pt.y >= 0
                and
                pt.y < static_cast<SHORT>(m_client_size_.m_height)
            )
            {
                m_mouse.OnMouseMove_(pt.x, pt.y);

                if (not m_mouse.IsInWindow())
                {
                    ::SetCapture(hWnd);
                    m_mouse.OnMouseEnter_();
                }
            }
            else
            {
                if (wParam bitand (MK_LBUTTON bitor MK_RBUTTON))
                {
                    m_mouse.OnMouseMove_(pt.x, pt.y);
                }
                else
                {
                    ::ReleaseCapture();
                    m_mouse.OnMouseLeave_();
                }
            }
        }
            break;

        case WM_LBUTTONDOWN:
            m_mouse.OnLeftPressed_();
            break;

        case WM_LBUTTONUP:
            m_mouse.OnLeftReleased_();
            break;

        case WM_RBUTTONDOWN:
            m_mouse.OnRightPressed_();
            break;

        case WM_RBUTTONUP:
            m_mouse.OnRightReleased_();
            break;

        case WM_MBUTTONDOWN:
            m_mouse.OnWheelPressed_();
            break;

        case WM_MBUTTONUP:
            m_mouse.OnWheelReleased_();
            break;

        case WM_MOUSEWHEEL:
            m_mouse.OnWheelDelta_(GET_WHEEL_DELTA_WPARAM(wParam));
            break;
            /******* END MOUSE MESSAGES *******/

        default:
            break;
        }

        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }


    // Window::WndClass_

    Window::WndClass_::WndClass_() noexcept
        :
        m_hInst_(::GetModuleHandle(nullptr))
    {
        WNDCLASSEX wcx{};
        wcx.cbSize = sizeof(wcx);
        wcx.style = CS_OWNDC;
        wcx.lpfnWndProc = &WndClass_::HandleMsgSetup_;
        wcx.cbClsExtra = 0;
        wcx.cbWndExtra = 0;
        wcx.hInstance = m_hInst_;
        wcx.hIcon = nullptr;
        wcx.hIconSm = nullptr;
        wcx.hbrBackground = nullptr;
        wcx.lpszMenuName = nullptr;
        wcx.lpszClassName = s_wndClassName_;

        if constexpr (s_cursorEnabled_)
        {
            wcx.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
        }
        else
        {
            ::ShowCursor(false);
        }

        [[maybe_unused]]
        const auto&& atom = ::RegisterClassEx(&wcx);
    }
    Window::WndClass_::~WndClass_() noexcept
    {
        ::UnregisterClass(s_wndClassName_, WndClass_::GetInstance());
    }

    auto Window::WndClass_::GetInstance() noexcept -> HINSTANCE
    {
        static WndClass_ wndClass_;

        return wndClass_.m_hInst_;
    }

    auto Window::WndClass_::GetName() noexcept -> str_t
    {
        return s_wndClassName_;
    }

    auto CALLBACK Window::WndClass_::HandleMsgSetup_(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        if (msg == WM_NCCREATE)
        {
            const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
            Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

            ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

#pragma warning (push)
#pragma warning (disable : 5039)
            ::SetWindowLongPtr(hWnd, GWLP_WNDPROC,  reinterpret_cast<LONG_PTR>(&WndClass_::HandleMsgThunk_));
#pragma warning (pop)

            return pWnd->HandleMsg_(hWnd, msg, wParam, lParam);
        }

        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }
    auto CALLBACK Window::WndClass_::HandleMsgThunk_(const HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        Window* const pWnd = reinterpret_cast<Window*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));

        return pWnd->HandleMsg_(hWnd, msg, wParam, lParam);
    }
}