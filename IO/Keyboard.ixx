module;

export module FatPound.IO.Keyboard;

export import FatPound.IO.KeyEvent;

import std;

export namespace fatpound::io
{
    class Keyboard final
    {
        static constexpr auto scx_bufferSize_ = 16U;

    public:
        using KeyCode_t = decltype(KeyEvent::code);


    public:
        explicit Keyboard()                    = default;
        explicit Keyboard(const Keyboard&)     = delete;
        explicit Keyboard(Keyboard&&) noexcept = delete;

        auto operator = (const Keyboard&)     -> Keyboard& = delete;
        auto operator = (Keyboard&&) noexcept -> Keyboard& = delete;
        ~Keyboard() noexcept                               = default;


    public:
        auto GetEvent() noexcept -> std::optional<KeyEvent>
        {
            if (KeyBufferIsEmpty())
            {
                return std::nullopt;
            }

            auto keyE = m_key_event_queue_.front();

            m_key_event_queue_.pop();

            return keyE;
        }
        auto GetChar()  noexcept -> std::optional<unsigned char>
        {
            if (m_char_buffer_.empty())
            {
                return std::nullopt;
            }

            auto ch = m_char_buffer_.front();

            m_char_buffer_.pop();

            return ch;
        }

        [[nodiscard]] auto KeyIsPressed(KeyCode_t code) const noexcept -> bool
        {
            return m_key_states_[code];
        }
        [[nodiscard]] auto AutoRepeatIsEnabled() const noexcept -> bool
        {
            return m_auto_repeat_enabled_;
        }

        [[nodiscard]] auto KeyBufferIsEmpty()  const noexcept -> bool
        {
            return m_key_event_queue_.empty();
        }
        [[nodiscard]] auto CharBufferIsEmpty() const noexcept -> bool
        {
            return m_char_buffer_.empty();
        }

        void EnableAutoRepeat()  noexcept
        {
            m_auto_repeat_enabled_ = true;
        }
        void DisableAutoRepeat() noexcept
        {
            m_auto_repeat_enabled_ = false;
        }
        void ClearKeyStateBitset() noexcept
        {
            m_key_states_.reset();
        }

        void AddKeyPressEvent(unsigned char keycode)
        {
            m_key_states_[keycode] = true;

            m_key_event_queue_.push(KeyEvent{ .type = KeyEvent::Type::Press, .code = keycode });

            TrimBuffer_(m_key_event_queue_);
        }
        void AddKeyReleaseEvent(unsigned char keycode)
        {
            m_key_states_[keycode] = false;

            m_key_event_queue_.push(KeyEvent{ .type = KeyEvent::Type::Release, .code = keycode });

            TrimBuffer_(m_key_event_queue_);
        }
        void AddChar(unsigned char ch)
        {
            m_char_buffer_.push(ch);

            TrimBuffer_(m_char_buffer_);
        }


    protected:


    private:
        template <typename U>
        static void TrimBuffer_(std::queue<U>& buffer) noexcept
        {
            while (buffer.size() > scx_bufferSize_)
            {
                buffer.pop();
            }
        }


    private:
        std::queue<KeyEvent> m_key_event_queue_;
        std::queue<unsigned char> m_char_buffer_;

        std::bitset<std::numeric_limits<KeyCode_t>::max()> m_key_states_;

        std::atomic_bool m_auto_repeat_enabled_;
    };
}

module : private;
