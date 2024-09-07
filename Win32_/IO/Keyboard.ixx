module;

#include <FatWin32_Namespaces.hpp>

export module FatPound.Win32.IO.Keyboard;

import std;

namespace fatpound::win32
{
    class Window;
}

export namespace fatpound::win32::io
{
    class Keyboard final
    {
        friend NAMESPACE_WIN32::Window;

    public:
        class Event final
        {
        public:
            enum class Type
            {
                Press,
                Release,
                Invalid
            };

        public:
            explicit Event(const Type type, const unsigned char code) noexcept;

            explicit Event() = default;
            Event(const Event& src) = default;
            Event(Event&& src) = default;

            auto operator = (const Event& src) -> Event& = default;
            auto operator = (Event&& src)      -> Event& = default;
            ~Event() noexcept = default;

        public:
            auto GetCode() const noexcept -> unsigned char;

            auto IsPress()   const noexcept -> bool;
            auto IsRelease() const noexcept -> bool;
            auto IsInvalid() const noexcept -> bool;

        protected:

        private:
            Type m_type_ = Type::Invalid;

            unsigned char m_code_ = 0u;
        };


    public:
        explicit Keyboard() = default;
        explicit Keyboard(const Keyboard& src) = delete;
        explicit Keyboard(Keyboard&& src) = delete;

        auto operator = (const Keyboard& src) -> Keyboard& = delete;
        auto operator = (Keyboard&& src)      -> Keyboard& = delete;
        ~Keyboard() noexcept = default;


    public:
        auto ReadKeyFromBuffer() noexcept -> Event;

        auto ReadCharFromBuffer() noexcept -> unsigned char;

        auto KeyIsPressed(const unsigned char keycode) const noexcept -> bool;

        auto KeyBufferIsEmpty()    const noexcept -> bool;
        auto CharBufferIsEmpty()   const noexcept -> bool;
        auto AutoRepeatIsEnabled() const noexcept -> bool;

        void FlushKeyBuffer()    noexcept;
        void FlushCharBuffer()   noexcept;
        void FlushBuffers()      noexcept;
        void EnableAutoRepeat()  noexcept;
        void DisableAutoRepeat() noexcept;


    protected:


    private:
        template <typename T>
        static void TrimBuffer_(std::queue<T>& buffer) noexcept
        {
            while (buffer.size() > s_bufferSize_)
            {
                buffer.pop();
            }
        }


    private:
        void OnKeyPressed_(unsigned char keycode);
        void OnKeyReleased_(unsigned char keycode);
        void OnChar_(unsigned char character);

        void ClearKeyStateBitset_() noexcept;


    private:
        static constexpr unsigned int s_keyCount_ = 256u;

        std::bitset<s_keyCount_> m_key_states_;
        
        std::queue<Event> m_event_buffer_;
        std::queue<unsigned char> m_char_buffer_;

        bool m_auto_repeat_enabled_ = false;

        static constexpr unsigned int s_bufferSize_ = 16u;
    };
}