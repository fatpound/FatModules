module;

#include <FatWin32_.hpp>

module FatPound.Win32.IO.Mouse;

namespace fatpound::win32::io
{
    // Mouse

    auto Mouse::GetPos() const noexcept -> std::pair<int, int>
    {
        return { m_x_, m_y_ };
    }

    auto Mouse::ReadRawDelta() noexcept -> std::optional<RawDelta>
    {
        if (m_raw_delta_buffer_.empty())
        {
            return std::nullopt;
        }

        const RawDelta delta = m_raw_delta_buffer_.front();
        m_raw_delta_buffer_.pop();

        return delta;
    }

    auto Mouse::ReadFromBuffer() noexcept -> Event
    {
        if (m_event_buffer_.size() > 0u)
        {
            Event e = m_event_buffer_.front();
            m_event_buffer_.pop();

            return e;
        }

        return Event{};
    }

    auto Mouse::GetPosX() const noexcept -> int
    {
        return m_x_;
    }
    auto Mouse::GetPosY() const noexcept -> int
    {
        return m_y_;
    }

    auto Mouse::EventBufferIsEmpty() const noexcept -> bool
    {
        return m_event_buffer_.empty();
    }

    auto Mouse::IsInWindow()     const noexcept -> bool
    {
        return m_is_in_window_;
    }
    auto Mouse::LeftIsPressed()  const noexcept -> bool
    {
        return m_left_is_pressed_;
    }
    auto Mouse::RightIsPressed() const noexcept -> bool
    {
        return m_right_is_pressed_;
    }
    auto Mouse::WheelIsPressed() const noexcept -> bool
    {
        return m_wheel_is_pressed_;
    }

    void Mouse::FlushBuffer() noexcept
    {
        m_event_buffer_ = std::queue<Event>{};
    }

    void Mouse::OnMouseMove_(int x, int y)
    {
        m_x_ = x;
        m_y_ = y;

        m_event_buffer_.push(Event{ Event::Type::Move, *this });

        TrimBuffer_();
    }
    void Mouse::OnMouseEnter_()
    {
        m_is_in_window_ = true;

        m_event_buffer_.push(Event{ Event::Type::Enter, *this });

        TrimBuffer_();
    }
    void Mouse::OnMouseLeave_()
    {
        m_is_in_window_ = false;

        m_event_buffer_.push(Event{ Event::Type::Leave, *this });

        TrimBuffer_();
    }

    void Mouse::OnRawDelta_(int dx, int dy)
    {
        m_raw_delta_buffer_.push(RawDelta(dx, dy));

        TrimBuffer_();
    }

    void Mouse::OnLeftPressed_()
    {
        m_left_is_pressed_ = true;

        m_event_buffer_.push(Event{ Event::Type::LPress, *this });

        TrimBuffer_();
    }
    void Mouse::OnLeftReleased_()
    {
        m_left_is_pressed_ = false;

        m_event_buffer_.push(Event{ Event::Type::LRelease, *this });

        TrimBuffer_();
    }
    void Mouse::OnRightPressed_()
    {
        m_right_is_pressed_ = true;

        m_event_buffer_.push(Event{ Event::Type::RPress, *this });

        TrimBuffer_();
    }
    void Mouse::OnRightReleased_()
    {
        m_right_is_pressed_ = false;

        m_event_buffer_.push(Event{ Event::Type::RRelease, *this });

        TrimBuffer_();
    }
    void Mouse::OnWheelPressed_()
    {
        m_wheel_is_pressed_ = true;

        m_event_buffer_.push(Event{ Event::Type::WheelPress, *this });

        TrimBuffer_();
    }
    void Mouse::OnWheelReleased_()
    {
        m_wheel_is_pressed_ = false;

        m_event_buffer_.push(Event{ Event::Type::WheelRelease, *this });

        TrimBuffer_();
    }
    void Mouse::OnWheelUp_()
    {
        m_event_buffer_.push(Event{ Event::Type::WheelUp, *this });

        TrimBuffer_();
    }
    void Mouse::OnWheelDown_()
    {
        m_event_buffer_.push(Event{ Event::Type::WheelDown, *this });

        TrimBuffer_();
    }
    void Mouse::OnWheelDelta_(int delta)
    {
        m_wheel_delta_carry_ += delta;

        while (m_wheel_delta_carry_ >= WHEEL_DELTA)
        {
            m_wheel_delta_carry_ -= WHEEL_DELTA;

            OnWheelUp_();
        }

        while (m_wheel_delta_carry_ <= -WHEEL_DELTA)
        {
            m_wheel_delta_carry_ += WHEEL_DELTA;

            OnWheelDown_();
        }
    }

    void Mouse::TrimBuffer_() noexcept
    {
        while (m_event_buffer_.size() > Mouse::s_bufferSize_)
        {
            m_event_buffer_.pop();
        }
    }
    void Mouse::TrimRawInputBuffer_() noexcept
    {
        while (m_raw_delta_buffer_.size() > Mouse::s_bufferSize_)
        {
            m_raw_delta_buffer_.pop();
        }
    }


    // Event

    Mouse::Event::Event(const Type type, const Mouse& parent) noexcept
        :
        type_(type),
        x_(parent.m_x_),
        y_(parent.m_y_),
         left_is_pressed_(parent.m_left_is_pressed_),
        right_is_pressed_(parent.m_right_is_pressed_),
        wheel_is_pressed_(parent.m_wheel_is_pressed_)
    {

    }

    auto Mouse::Event::GetPos() const noexcept -> std::pair<int, int>
    {
        return { x_, y_ };
    }

    auto Mouse::Event::GetType() const noexcept -> Type
    {
        return type_;
    }

    auto Mouse::Event::GetPosX() const noexcept -> int
    {
        return x_;
    }
    auto Mouse::Event::GetPosY() const noexcept -> int
    {
        return y_;
    }

    auto Mouse::Event::IsValid() const noexcept -> bool
    {
        return type_ not_eq Type::Invalid;
    }
    auto Mouse::Event::LeftIsPressed()  const noexcept -> bool
    {
        return left_is_pressed_;
    }
    auto Mouse::Event::RightIsPressed() const noexcept -> bool
    {
        return right_is_pressed_;
    }
    auto Mouse::Event::WheelIsPressed() const noexcept -> bool
    {
        return wheel_is_pressed_;
    }
}