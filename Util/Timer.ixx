module;

#include <chrono> // to fix IntelliSense errors

export module FatPound.Util.Timer;

import std;

export namespace fatpound::util
{
    class Timer final
    {
    public:
        explicit Timer() = default;
        explicit Timer(const Timer& src) = delete;
        explicit Timer(Timer&& src) = delete;

        auto operator = (const Timer& src) -> Timer& = delete;
        auto operator = (Timer&& src)      -> Timer& = delete;
        ~Timer() noexcept = default;


    public:
        __forceinline auto GetElapsed_ms() const noexcept -> float
        {
            return std::chrono::duration<float, std::milli>(m_last_ - m_start_).count();
        }
        __forceinline auto GetElapsed_s()  const noexcept -> float
        {
            return GetElapsed_ms() / 1000.0f;
        }

        __forceinline void Start() noexcept
        {
            m_start_ = ::std::chrono::steady_clock::now();
        }
        __forceinline void Stop() noexcept
        {
            m_last_ = ::std::chrono::steady_clock::now();
        }


    protected:


    private:
        ::std::chrono::steady_clock::time_point m_start_;
        ::std::chrono::steady_clock::time_point m_last_;
    };
}