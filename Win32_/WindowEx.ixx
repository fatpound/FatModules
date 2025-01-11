module;

#include <FatNamespaces.hpp>
#include <FatFrameworkMacros.hpp>

#include <FatWin32.hpp>

#include <DirectXMath.h>

export module FatPound.Win32.WindowEx;

import FatPound.Win32.IWindow;
import FatPound.Win32.WndClassEx;

import FatPound.Concurrency;
import FatPound.IO;
import FatPound.Math;
import FatPound.Util;

import std;

export namespace fatpound::win32
{
    class WindowEx final : public IWindow
    {
    public:
        explicit WindowEx(
            std::shared_ptr<WndClassEx> pWndClassEx,
            const std::wstring title,
            const FATSPACE_UTIL::ScreenSizeInfo clientDimensions,
            std::shared_ptr<FATSPACE_IO::Mouse> pMouse       = std::make_shared<FATSPACE_IO::Mouse>(),
            std::shared_ptr<FATSPACE_IO::Keyboard> pKeyboard = std::make_shared<FATSPACE_IO::Keyboard>(),
            const std::optional<::DirectX::XMINT2> position  = std::nullopt)
            :
            m_pMouse{ std::move(pMouse) },
            m_pKeyboard{ std::move(pKeyboard) },
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

    #if IN_DEBUG or IS_FRAMEWORK

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

#endif // IN_DEBUG or IS_FRAMEWORK

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

#if IN_DEBUG or IS_FRAMEWORK

                        rect.right - rect.left,
                        rect.bottom - rect.top,
#else
                        static_cast<LONG>(mc_client_size_.m_width),
                        static_cast<LONG>(mc_client_size_.m_height),

#endif // IN_DEBUG or IS_FRAMEWORK

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

        explicit WindowEx() = delete;
        explicit WindowEx(const WindowEx& src) = delete;
        explicit WindowEx(WindowEx&& src)      = delete;

        auto operator = (const WindowEx& src) -> WindowEx& = delete;
        auto operator = (WindowEx&& src)      -> WindowEx& = delete;
        virtual ~WindowEx() noexcept(false) final
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


    public:
        virtual auto SetTitle(const std::wstring& title) -> std::future<void> override final
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

        virtual auto GetHandle() const noexcept -> HWND override final
        {
            return m_hWnd_;
        }

        virtual auto IsClosing() const noexcept -> bool override final
        {
            return m_is_closing_;
        }


    public:
        template <FATSPACE_MATH::numset::Rational Q> __forceinline auto GetClientWidth()  const noexcept
        {
            return static_cast<Q>(mc_client_size_.m_width);
        }
        template <FATSPACE_MATH::numset::Rational Q> __forceinline auto GetClientHeight() const noexcept
        {
            return static_cast<Q>(mc_client_size_.m_height);
        }


    public:
        std::shared_ptr<FATSPACE_IO::Mouse>    m_pMouse;
        std::shared_ptr<FATSPACE_IO::Keyboard> m_pKeyboard;


    protected:


    private:
        template <bool Notify = true, typename F, typename... Args>
        requires std::invocable<F, Args...>
        auto DispatchTaskToQueue_(F&& function, Args&&... args) -> auto
        {
            auto future = m_tasks_.Push(std::forward<F>(function), std::forward<Args>(args)...);

            if constexpr (Notify)
            {
                NotifyTaskDispatch_();
            }

            return future;
        }


    private:
        virtual auto HandleMessage_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT override final
        {
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
                return 0;

            case WM_LBUTTONDOWN:
                m_pMouse->OnLeftPressed_();
                return 0;

            case WM_LBUTTONUP:
                m_pMouse->OnLeftReleased_();
                return 0;

            case WM_RBUTTONDOWN:
                m_pMouse->OnRightPressed_();
                return 0;

            case WM_RBUTTONUP:
                m_pMouse->OnRightReleased_();
                return 0;

            case WM_MBUTTONDOWN:
                m_pMouse->OnWheelPressed_();
                return 0;

            case WM_MBUTTONUP:
                m_pMouse->OnWheelReleased_();
                return 0;

            case WM_MOUSEWHEEL:
                m_pMouse->OnWheelDelta_(GET_WHEEL_DELTA_WPARAM(wParam));
                return 0;

            case WM_KILLFOCUS:
                m_pKeyboard->ClearKeyStateBitset_();
                return 0;

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

                // also controls window movement
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


    private:
        void NotifyTaskDispatch_() const
        {
            const auto&& retval = ::PostMessage(m_hWnd_, scx_customTaskMsgId_, 0u, 0);

            if (retval == 0)
            {
                throw std::runtime_error{ "Failed to post task notification message!" };
            }
        }
        void MessageKernel_()
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


    private:
        static constexpr UINT scx_customTaskMsgId_ = WM_USER;


    private:
        FATSPACE_CONCURRENCY::TaskQueue m_tasks_;

        std::shared_ptr<WndClassEx> m_pWndClassEx_;

        const FATSPACE_UTIL::ScreenSizeInfo mc_client_size_;

        HWND m_hWnd_{};

        std::atomic_bool m_is_closing_{};
        std::binary_semaphore m_start_signal_{ 0 };

        std::jthread m_msg_jthread_;
    };
}

module : private;