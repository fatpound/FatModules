module;

#include <FatWin32_Namespaces.hpp>

export module FatPound.Win32.IO.Mouse;

import std;

namespace fatpound::win32
{
    class Window;
}

export namespace fatpound::win32::io
{
    class Mouse final
    {
        friend NAMESPACE_WIN32::Window;

    public:
        struct RawDelta final
        {
            int x;
            int y;
        };


    public:
        class Event final
        {
        public:
            enum class Type
            {
                LPress,
                LRelease,
                RPress,
                RRelease,
                WheelPress,
                WheelRelease,
                WheelUp,
                WheelDown,
                Enter,
                Move,
                Leave,
                Invalid
            };

        public:
            explicit Event(const Type type, const Mouse& parent) noexcept;

            explicit Event() = default;
            Event(const Event& src) = default;
            Event(Event&& src) = default;

            auto operator = (const Event& src) -> Event& = default;
            auto operator = (Event&& src)      -> Event& = default;
            ~Event() = default;

        public:
            auto GetPos() const noexcept -> std::pair<int, int>;

            auto GetType() const noexcept -> Type;

            auto GetPosX() const noexcept -> int;
            auto GetPosY() const noexcept -> int;

            auto IsValid()        const noexcept -> bool;
            auto LeftIsPressed()  const noexcept -> bool;
            auto RightIsPressed() const noexcept -> bool;
            auto WheelIsPressed() const noexcept -> bool;

        protected:

        private:
            Type type_{ Type::Invalid };

            int x_{};
            int y_{};

            bool left_is_pressed_{};
            bool right_is_pressed_{};
            bool wheel_is_pressed_{};
        };


    public:
        explicit Mouse() = default;
        explicit Mouse(const Mouse& src) = delete;
        explicit Mouse(Mouse&& src) = delete;

        auto operator = (const Mouse& src) -> Mouse& = delete;
        auto operator = (Mouse&& src)      -> Mouse& = delete;
        ~Mouse() noexcept = default;


    public:
        auto GetPos() const noexcept -> std::pair<int, int>;

        auto ReadRawDelta() noexcept -> std::optional<RawDelta>;

        auto ReadFromBuffer() noexcept -> Event;

        auto GetPosX() const noexcept -> int;
        auto GetPosY() const noexcept -> int;

        auto EventBufferIsEmpty() const noexcept -> bool;

        auto IsInWindow()     const noexcept -> bool;
        auto LeftIsPressed()  const noexcept -> bool;
        auto RightIsPressed() const noexcept -> bool;
        auto WheelIsPressed() const noexcept -> bool;

        void FlushBuffer() noexcept;


    protected:


    private:
        void OnMouseMove_(int x, int y);
        void OnMouseEnter_();
        void OnMouseLeave_();

        void OnRawDelta_(int dx, int dy);

        void OnLeftPressed_();
        void OnLeftReleased_();
        void OnRightPressed_();
        void OnRightReleased_();
        void OnWheelPressed_();
        void OnWheelReleased_();
        void OnWheelUp_();
        void OnWheelDown_();
        void OnWheelDelta_(int delta);

        void TrimBuffer_() noexcept;
        void TrimRawInputBuffer_() noexcept;


    private:
        std::queue<Event> m_event_buffer_;
        std::queue<RawDelta> m_raw_delta_buffer_;

        int m_x_ = 0;
        int m_y_ = 0;
        int m_wheel_delta_carry_ = 0;

        bool m_is_in_window_ = false;

        bool m_left_is_pressed_  = false;
        bool m_right_is_pressed_ = false;
        bool m_wheel_is_pressed_ = false;

        static constexpr unsigned int s_bufferSize_ = 16u;
    };
}