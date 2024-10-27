module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

module FatPound.Win32.WindowEx;

namespace fatpound::win32
{
    WindowEx::WindowEx(
            std::shared_ptr<WndClassEx> pWndClassEx,
            std::shared_ptr<FATSPACE_IO::Keyboard> pKeyboard,
            std::shared_ptr<FATSPACE_IO::Mouse> pMouse,
            std::wstring title,
            FATSPACE_UTIL::ScreenSizeInfo clientDimensions,
            std::optional<::DirectX::XMINT2> position
        )
        :
        m_pKeyboard{ std::move(pKeyboard) },
        m_pMouse{ std::move(pMouse) },
        m_pWndClassEx_{ std::move(pWndClassEx) },
        mc_client_size_{ .m_width = clientDimensions.m_width, .m_height = clientDimensions.m_height },
        ///////////////////////////////////////////////
#pragma region (thread w/o C4355)
#pragma warning (push)
#pragma warning (disable : 4355)
        m_msg_jthread_{ &WindowEx::MessageKernel_, this }
#pragma warning (pop)
#pragma endregion
        ///////////////////////////////////////////////
    {
        auto future = DispatchTaskToQueue_<false>(
            [=, this]() -> void
            {
                constexpr DWORD exStyles{};

                constexpr DWORD styles
                {
                    WS_VISIBLE

#if IN_DEBUG

                    bitor WS_CAPTION
                    bitor WS_MINIMIZEBOX
                    bitor WS_OVERLAPPED
                    bitor WS_SYSMENU
                };
                
                RECT rect{};
                rect.left = 0l;
                rect.right = rect.left + static_cast<LONG>(mc_client_size_.m_width);
                rect.top = 0l;
                rect.bottom = rect.top + static_cast<LONG>(mc_client_size_.m_height);

                {
                    [[maybe_unused]]
                    const auto&& retval = ::AdjustWindowRectEx(&rect, styles, false, exStyles);
                }

#else

                    bitor WS_POPUP
                };

#endif // IN_DEBUG
                
                const auto hModule = ::GetModuleHandle(nullptr);
                
                if (hModule == nullptr) [[unlikely]]
                {
                    throw std::runtime_error("Error occured when obtaining hModule!");
                }

                m_hWnd_ = ::CreateWindowEx(
                    exStyles,
                    MAKEINTATOM(m_pWndClassEx_->GetAtom()),
                    title.c_str(),
                    styles,
                    position.has_value() ? position->x : CW_USEDEFAULT,
                    position.has_value() ? position->y : CW_USEDEFAULT,
#if IN_DEBUG
                    rect.right  - rect.left,
                    rect.bottom - rect.top,
#else
                    static_cast<LONG>(mc_client_size_.m_width),
                    static_cast<LONG>(mc_client_size_.m_height),
#endif // IN_DEBUG
                    nullptr,
                    nullptr,
                    hModule,
                    this
                );

                if (m_hWnd_ == nullptr) [[unlikely]]
                {
                    throw std::runtime_error("Error occured when creating HWND!");
                }
            }
        );

        m_start_signal_.release();

        future.get();
    }
    WindowEx::~WindowEx() noexcept(false)
    {
        [[maybe_unused]]
        auto future = DispatchTaskToQueue_(
            [this]() noexcept -> void
            {
                [[maybe_unused]]
                const auto&& retval = ::DestroyWindow(m_hWnd_);
            }
        );
    }

    auto WindowEx::SetTitle(const std::wstring& title) -> std::future<void>
    {
        auto future = DispatchTaskToQueue_(
            [=, this]() noexcept -> void
            {
                [[maybe_unused]]
                const auto&& retval = ::SetWindowText(m_hWnd_, title.c_str());
            }
        );

        return future;
    }

    auto WindowEx::GetHandle() const noexcept -> HWND
    {
        return m_hWnd_;
    }

    auto WindowEx::IsClosing() const noexcept -> bool
    {
        return m_is_closing_;
    }

    auto WindowEx::HandleMessage_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
    {
        using FATSPACE_IO::Keyboard;
        using FATSPACE_IO::KeyEvent;

        using enum KeyEvent::Type;

        switch (msg)
        {
        case WM_MOUSEMOVE:
        {
            const POINTS pt = MAKEPOINTS(lParam);

            if (pt.x >= 0
                and pt.x < static_cast<SHORT>(mc_client_size_.m_width)
                and pt.y >= 0
                and pt.y < static_cast<SHORT>(mc_client_size_.m_height)
                )
            {
                m_pMouse->OnMouseMove_(pt.x, pt.y);

                if (not m_pMouse->IsInWindow())
                {
                    ::SetCapture(hWnd);
                    m_pMouse->OnMouseEnter_();
                }
            }
            else
            {
                if (wParam bitand (MK_LBUTTON bitor MK_RBUTTON))
                {
                    m_pMouse->OnMouseMove_(pt.x, pt.y);
                }
                else
                {
                    ::ReleaseCapture();
                    m_pMouse->OnMouseLeave_();
                }
            }
        }
            break;

        case WM_LBUTTONDOWN:
            m_pMouse->OnLeftPressed_();
            break;

        case WM_LBUTTONUP:
            m_pMouse->OnLeftReleased_();
            break;

        case WM_RBUTTONDOWN:
            m_pMouse->OnRightPressed_();
            break;

        case WM_RBUTTONUP:
            m_pMouse->OnRightReleased_();
            break;

        case WM_MBUTTONDOWN:
            m_pMouse->OnWheelPressed_();
            break;

        case WM_MBUTTONUP:
            m_pMouse->OnWheelReleased_();
            break;

        case WM_MOUSEWHEEL:
            m_pMouse->OnWheelDelta_(GET_WHEEL_DELTA_WPARAM(wParam));
            break;

        case WM_KILLFOCUS:
            m_pKeyboard->ClearKeyStateBitset_();
            break;

        case WM_KEYDOWN: [[fallthrough]];
        case WM_SYSKEYDOWN:
            if ((not (lParam bitand 0x40000000)) or m_pKeyboard->AutoRepeatIsEnabled())
            {
                m_pKeyboard->OnKeyPressed_(static_cast<unsigned char>(wParam));
            }
            break;

        case WM_KEYUP: [[fallthrough]];
        case WM_SYSKEYUP:
            m_pKeyboard->OnKeyReleased_(static_cast<unsigned char>(wParam));
            break;

        case WM_CHAR:
            m_pKeyboard->OnChar_(static_cast<unsigned char>(wParam));
            break;

        case scx_customTaskMsgId_:
            m_tasks_.ExecuteFirstAndPopOff();
            return 0;

        case WM_SYSCOMMAND:
            if ((wParam bitand 0xFFF0u) == SC_CLOSE)
            {
                ::PostMessage(m_hWnd_, WM_CLOSE, 0, 0);
            }
            break;

        case WM_CLOSE:
            m_is_closing_ = true;
            return 0;

        case WM_DESTROY:
            m_hWnd_ = nullptr;
            ::PostQuitMessage(0);
            return 0;

        default:
            break;
        }

        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

    void WindowEx::NotifyTaskDispatch_() const
    {
        const auto&& retval = ::PostMessage(m_hWnd_, scx_customTaskMsgId_, 0u, 0);

        if (retval == 0)
        {
            throw std::runtime_error{ "Failed to post task notification message!" };
        }
    }
    void WindowEx::MessageKernel_()
    {
        m_start_signal_.acquire();
        m_tasks_.ExecuteFirstAndPopOff();

        MSG msg{};

        while (::GetMessage(&msg, m_hWnd_, 0u, 0u) not_eq 0)
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
    }
}