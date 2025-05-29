module;

export module FatPound.IO.Mouse;

import std;

export namespace fatpound::io
{
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
        using Position_t = decltype(Event::pos_x);


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
            m_pos_x_ = x;
            m_pos_y_ = y;

            m_event_buffer_.push(Event{ .type = Event::Type::Move, .pos_x = m_pos_x_, .pos_y = m_pos_y_ });

            TrimBuffer_();
        }
        void AddMouseEnterEvent()
        {
            m_is_in_window_ = true;

            m_event_buffer_.push(Event{ .type = Event::Type::Enter });

            TrimBuffer_();
        }
        void AddMouseLeaveEvent()
        {
            m_is_in_window_ = false;

            m_event_buffer_.push(Event{ .type = Event::Type::Leave });

            TrimBuffer_();
        }

        void AddLeftPressEvent    ()
        {
            m_left_is_pressed_ = true;

            m_event_buffer_.push(Event{ .type = Event::Type::LPress, .pos_x = m_pos_x_, .pos_y = m_pos_y_ });

            TrimBuffer_();
        }
        void AddLeftReleaseEvent  ()
        {
            m_left_is_pressed_ = false;

            m_event_buffer_.push(Event{ .type = Event::Type::LRelease });

            TrimBuffer_();
        }
        void AddRightPressEvent   ()
        {
            m_right_is_pressed_ = true;

            m_event_buffer_.push(Event{ .type = Event::Type::RPress });

            TrimBuffer_();
        }
        void AddRightReleaseEvent ()
        {
            m_right_is_pressed_ = false;

            m_event_buffer_.push(Event{ .type = Event::Type::RRelease });

            TrimBuffer_();
        }
        void AddWheelPressEvent   ()
        {
            m_wheel_is_pressed_ = true;

            m_event_buffer_.push(Event{ .type = Event::Type::WheelPress });

            TrimBuffer_();
        }
        void AddWheelReleaseEvent ()
        {
            m_wheel_is_pressed_ = false;

            m_event_buffer_.push(Event{ .type = Event::Type::WheelRelease });

            TrimBuffer_();
        }
        void AddWheelUpEvent      ()
        {
            m_event_buffer_.push(Event{ .type = Event::Type::WheelUp });

            TrimBuffer_();
        }
        void AddWheelDownEvent    ()
        {
            m_event_buffer_.push(Event{ .type = Event::Type::WheelDown });

            TrimBuffer_();
        }
        void ProcessWheelDelta(const int delta)
        {
            m_wheel_delta_carry_ += delta;

#define FAT_WHEEL_DELTA 120
            while (m_wheel_delta_carry_ >= FAT_WHEEL_DELTA)
            {
                m_wheel_delta_carry_ -= FAT_WHEEL_DELTA;

                AddWheelUpEvent();
            }

            while (m_wheel_delta_carry_ <= -FAT_WHEEL_DELTA)
            {
                m_wheel_delta_carry_ += FAT_WHEEL_DELTA;

                AddWheelDownEvent();
            }
#undef FAT_WHEEL_DELTA
        }


    protected:


    private:
        void TrimBuffer_() noexcept
        {
            while (m_event_buffer_.size() > scx_bufferSize_)
            {
                m_event_buffer_.pop();
            }
        }


    private:
        std::queue<Event> m_event_buffer_;

        Position_t m_pos_x_{};
        Position_t m_pos_y_{};

        Position_t m_wheel_delta_carry_{};

        bool m_is_in_window_{};

        bool m_left_is_pressed_{};
        bool m_right_is_pressed_{};
        bool m_wheel_is_pressed_{};
    };
}

module : private;
