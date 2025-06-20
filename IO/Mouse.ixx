module;

// for lock_guards without CTAD, see: https://clang.llvm.org/docs/DiagnosticsReference.html#wctad-maybe-unsupported

export module FatPound.IO.Mouse;

import std;

export namespace fatpound::io
{
    /// @brief Represents a mouse input handler that tracks mouse events, button states, position, and provides an event buffer interface
    ///
    class Mouse final
    {
        static constexpr auto scx_bufferSize_ = 16U;


    public:
        struct alignas(16) Event final
        {
            enum struct Type : std::uint8_t
            {
                Move,

                LPress,
                LRelease,
                RPress,
                RRelease,
                WheelPress,
                WheelRelease,

                WheelUp,
                WheelDown,
                WheelDelta,

                Enter,
                Leave,

                Invalid
            };

            Type type{ Type::Invalid };

            bool left_is_pressed{};
            bool right_is_pressed{};
            bool wheel_is_pressed{};

            // ints are below for alignment

            int pos_x{};
            int pos_y{};
            int wheel_delta_carry{};
        };


    public:
        using   Position_t = decltype(Event::pos_x);
        using WheelDelta_t = decltype(Event::wheel_delta_carry);


    public:
        explicit Mouse()                 = default;
        explicit Mouse(const Mouse&)     = delete;
        explicit Mouse(Mouse&&) noexcept = delete;

        auto operator = (const Mouse&)     -> Mouse& = delete;
        auto operator = (Mouse&&) noexcept -> Mouse& = delete;
        ~Mouse() noexcept                            = default;


    public:
        auto GetEvent() noexcept -> std::optional<Event>
        {
            if (EventBufferIsEmpty())
            {
                return std::nullopt;
            }

            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            auto mouseE = m_event_buffer_.front();
            m_event_buffer_.pop();

            return mouseE;
        }

        [[nodiscard]] auto GetPos() const noexcept -> std::pair<Position_t, Position_t>
        {
            return { GetPosX(), GetPosY() };
        }
        [[nodiscard]] auto GetPosX() const noexcept -> Position_t
        {
            return m_pos_x_;
        }
        [[nodiscard]] auto GetPosY() const noexcept -> Position_t
        {
            return m_pos_y_;
        }

        [[nodiscard]] auto EventBufferIsEmpty() const noexcept -> bool
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            return m_event_buffer_.empty();
        }

        [[nodiscard]] auto IsInWindow() const noexcept -> bool
        {
            return m_is_in_window_;
        }

        [[nodiscard]] auto LeftIsPressed()  const noexcept -> bool
        {
            return m_left_is_pressed_;
        }
        [[nodiscard]] auto RightIsPressed() const noexcept -> bool
        {
            return m_right_is_pressed_;
        }
        [[nodiscard]] auto WheelIsPressed() const noexcept -> bool
        {
            return m_wheel_is_pressed_;
        }

        void AddMouseMoveEvent(const int x, const int y)
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_pos_x_ = x;
            m_pos_y_ = y;

            m_event_buffer_.push(Event{ .type = Event::Type::Move, .pos_x = m_pos_x_, .pos_y = m_pos_y_ });

            TrimBuffer_NoGuard_();
        }
        void AddMouseEnterEvent()
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_is_in_window_ = true;

            m_event_buffer_.push(Event{ .type = Event::Type::Enter });

            TrimBuffer_NoGuard_();
        }
        void AddMouseLeaveEvent()
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_is_in_window_ = false;

            m_event_buffer_.push(Event{ .type = Event::Type::Leave });

            TrimBuffer_NoGuard_();
        }

        void AddLeftPressEvent         ()
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_left_is_pressed_ = true;

            m_event_buffer_.push(Event{ .type = Event::Type::LPress, .pos_x = m_pos_x_, .pos_y = m_pos_y_ });

            TrimBuffer_NoGuard_();
        }
        void AddLeftReleaseEvent       ()
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_left_is_pressed_ = false;

            m_event_buffer_.push(Event{ .type = Event::Type::LRelease });

            TrimBuffer_NoGuard_();
        }
        void AddRightPressEvent        ()
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_right_is_pressed_ = true;

            m_event_buffer_.push(Event{ .type = Event::Type::RPress });

            TrimBuffer_NoGuard_();
        }
        void AddRightReleaseEvent      ()
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_right_is_pressed_ = false;

            m_event_buffer_.push(Event{ .type = Event::Type::RRelease });

            TrimBuffer_NoGuard_();
        }
        void AddWheelPressEvent        ()
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_wheel_is_pressed_ = true;

            m_event_buffer_.push(Event{ .type = Event::Type::WheelPress });

            TrimBuffer_NoGuard_();
        }
        void AddWheelReleaseEvent      ()
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_wheel_is_pressed_ = false;

            m_event_buffer_.push(Event{ .type = Event::Type::WheelRelease });

            TrimBuffer_NoGuard_();
        }
        void AddWheelUpEvent_NoGuard   ()
        {
            m_event_buffer_.push(Event{ .type = Event::Type::WheelUp });

            TrimBuffer_NoGuard_();
        }
        void AddWheelDownEvent_NoGuard ()
        {
            m_event_buffer_.push(Event{ .type = Event::Type::WheelDown });

            TrimBuffer_NoGuard_();
        }
        void AddWheelUpEvent           ()
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            AddWheelUpEvent_NoGuard();
        }
        void AddWheelDownEvent         ()
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            AddWheelDownEvent_NoGuard();
        }

        void ProcessWheelDelta(const WheelDelta_t delta)
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_wheel_delta_carry_ += delta;

// NOLINTBEGIN(cppcoreguidelines-macro-usage)
#define FATLIB_WHEEL_DELTA 120
            while (m_wheel_delta_carry_ >= FATLIB_WHEEL_DELTA)
            {
                m_wheel_delta_carry_ -= FATLIB_WHEEL_DELTA;

                AddWheelUpEvent_NoGuard();
            }

            while (m_wheel_delta_carry_ <= -FATLIB_WHEEL_DELTA)
            {
                m_wheel_delta_carry_ += FATLIB_WHEEL_DELTA;

                AddWheelDownEvent_NoGuard();
            }
#undef FATLIB_WHEEL_DELTA
// NOLINTEND(cppcoreguidelines-macro-usage)
        }


    protected:


    private:
        void TrimBuffer_NoGuard_() noexcept
        {
            while (m_event_buffer_.size() > scx_bufferSize_)
            {
                m_event_buffer_.pop();
            }
        }


    private:
        std::queue<Event> m_event_buffer_;

        mutable std::mutex m_mtx_;

        Position_t m_pos_x_{};
        Position_t m_pos_y_{};

        WheelDelta_t m_wheel_delta_carry_{};

        std::atomic_bool m_is_in_window_;

        std::atomic_bool m_left_is_pressed_;
        std::atomic_bool m_right_is_pressed_;
        std::atomic_bool m_wheel_is_pressed_;
    };

    using MouseEvent = Mouse::Event;
}

module : private;
