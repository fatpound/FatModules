module;

#include <FatDefines.hpp>

#ifdef __INTELLISENSE__
    #include <chrono>
#endif

export module FatPound.Util.Timer;

import std;

export namespace fatpound::util
{
    class Timer final
    {
    public:
        explicit Timer()                 = default;
        explicit Timer(const Timer&)     = delete;
        explicit Timer(Timer&&) noexcept = delete;

        auto operator = (const Timer&)     -> Timer& = delete;
        auto operator = (Timer&&) noexcept -> Timer& = delete;
        ~Timer() noexcept                            = default;


    public:
        [[nodiscard]] FAT_FORCEINLINE auto GetElapsed_ms() const noexcept -> float
        {
            return std::chrono::duration<float, std::milli>(m_last_ - m_start_).count();
        }
        [[nodiscard]] FAT_FORCEINLINE auto GetElapsed_s()  const noexcept -> float
        {
            return GetElapsed_ms() / 1000.0F;
        }

        FAT_FORCEINLINE void Start() noexcept
        {
            m_start_ = std::chrono::steady_clock::now();
        }
        FAT_FORCEINLINE void Stop() noexcept
        {
            m_last_ = std::chrono::steady_clock::now();
        }


    protected:


    private:
        std::chrono::steady_clock::time_point m_start_;
        std::chrono::steady_clock::time_point m_last_;
    };
}

module : private;
