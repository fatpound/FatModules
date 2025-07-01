module;

// for lock_guards without CTAD, see: https://clang.llvm.org/docs/DiagnosticsReference.html#wctad-maybe-unsupported

export module FatPound.IO.Keyboard;

import std;

export namespace fatpound::io
{
    /// @brief Represents a keyboard input handler that manages key events, character input, and key states, including support for auto-repeat functionality
    ///
    class Keyboard final
    {
        static constexpr auto scx_bufferSize_ = 16U;

    public:
        struct alignas(2) KeyEvent
        {
            enum struct Type : std::uint8_t
            {
                Press,
                Release,

                Invalid
            };

            Type                           type{ Type::Invalid };
            std::underlying_type_t<Type>   code{};
        };


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

            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            auto keyE = m_key_event_queue_.front();
            m_key_event_queue_.pop();

            return keyE;
        }
        auto GetChar()  noexcept -> std::optional<unsigned char>
        {
            if (CharBufferIsEmpty())
            {
                return std::nullopt;
            }

            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            auto ch = m_char_buffer_.front();
            m_char_buffer_.pop();

            return ch;
        }

        [[nodiscard]] auto KeyIsPressed(KeyCode_t code) const noexcept -> bool
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            return m_key_states_[code];
        }
        [[nodiscard]] auto AutoRepeatIsEnabled() const noexcept -> bool
        {
            return m_auto_repeat_enabled_;
        }

        [[nodiscard]] auto KeyBufferIsEmpty()  const noexcept -> bool
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            return m_key_event_queue_.empty();
        }
        [[nodiscard]] auto CharBufferIsEmpty() const noexcept -> bool
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

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
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_key_states_.reset();
        }

        void AddKeyPressEvent(unsigned char keycode)
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_key_states_[keycode] = true;

            m_key_event_queue_.push(KeyEvent{ .type = KeyEvent::Type::Press, .code = keycode });

            TrimBuffer_NoGuard_(m_key_event_queue_);
        }
        void AddKeyReleaseEvent(unsigned char keycode)
        {
            const std::lock_guard<std::mutex> guard{ m_mtx_ };

            m_key_states_[keycode] = false;

            m_key_event_queue_.push(KeyEvent{ .type = KeyEvent::Type::Release, .code = keycode });

            TrimBuffer_NoGuard_(m_key_event_queue_);
        }
        void AddChar(unsigned char ch)
        {
            const std::lock_guard guard{ m_mtx_ };

            m_char_buffer_.push(ch);

            TrimBuffer_NoGuard_(m_char_buffer_);
        }


    protected:


    private:
        template <typename U>
        static void TrimBuffer_NoGuard_(std::queue<U>& buffer) noexcept
        {
            while (buffer.size() > scx_bufferSize_)
            {
                buffer.pop();
            }
        }


    private:
        std::queue<KeyEvent>                                 m_key_event_queue_;
        std::queue<unsigned char>                            m_char_buffer_;

        std::bitset<std::numeric_limits<KeyCode_t>::max()>   m_key_states_;

        std::atomic_bool                                     m_auto_repeat_enabled_;
        mutable std::mutex                                   m_mtx_;
    };

    using KeyEvent = Keyboard::KeyEvent;
}

module : private;
