module;

#include <FatWin32_.hpp>

#include <DirectXMath.h>

export module FatPound.Win32.WindowEx;

import FatPound.Win32.IWindow;
import FatPound.Win32.WndClassEx;

import FatPound.Concurrency;
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
            std::shared_ptr<FATSPACE_UTIL_IO::Keyboard> pKeyboard,
            std::shared_ptr<FATSPACE_UTIL_IO::Mouse> pMouse,
            std::wstring title,
            FATSPACE_UTIL::ScreenSizeInfo clientDimensions,
            std::optional<::DirectX::XMINT2> position = std::nullopt
        );

        explicit WindowEx() = delete;
        explicit WindowEx(const WindowEx& src) = delete;
        explicit WindowEx(WindowEx&& src)      = delete;

        auto operator = (const WindowEx& src) -> WindowEx& = delete;
        auto operator = (WindowEx&& src)      -> WindowEx& = delete;
        virtual ~WindowEx() noexcept(false) final;


    public:
        virtual auto SetTitle(const std::wstring& title) -> std::future<void> override final;

        virtual auto GetHandle() const noexcept -> HWND override final;

        virtual auto IsClosing() const noexcept -> bool override final;


    public:
        template <FATSPACE_MATH::number_set::Rational Q>
        auto GetClientWidth() const noexcept
        {
            return static_cast<Q>(mc_client_size_.m_width);
        }

        template <FATSPACE_MATH::number_set::Rational Q>
        auto GetClientHeight() const noexcept
        {
            return static_cast<Q>(mc_client_size_.m_height);
        }


    public:
        std::shared_ptr<FATSPACE_UTIL_IO::Keyboard> m_pKeyboard;
        std::shared_ptr<FATSPACE_UTIL_IO::Mouse> m_pMouse;


    protected:


    private:
        template <
            bool Notify = true,
            typename F,
            typename... Args
        >
        requires(std::invocable<F, Args...>)
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
        virtual auto HandleMessage_(const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT override final;


    private:
        void NotifyTaskDispatch_() const;
        void MessageKernel_();


    private:
        static constexpr UINT scx_customTaskMsgId_ = WM_USER;


    private:
        FATSPACE_CONCURRENCY::TaskQueue m_tasks_;

        std::shared_ptr<WndClassEx> m_pWndClassEx_;

        const FATSPACE_UTIL::ScreenSizeInfo mc_client_size_;

        HWND m_hWnd_{};

        std::atomic<bool> m_is_closing_{};
        std::binary_semaphore m_start_signal_{ 0 };

        std::jthread m_msg_jthread_;
    };
}