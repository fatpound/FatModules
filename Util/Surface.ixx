module;

#include <FatNamespaces.hpp>

#include <cassert>

#define FAT_DEFAULT_ALIGNMENT 16u

export module FatPound.Util.Surface;

import FatPound.Util.Color;
import FatPound.Util.ScreenSizeInfo;

import FatPound.Math;

import FatPound.Memory;

import FatPound.Win32.GDI_Plus;

import std;

export namespace fatpound::util
{
    class Surface final
    {
    public:
        explicit Surface(const std::wstring& filename, const unsigned int alignBytes = FAT_DEFAULT_ALIGNMENT);
        explicit Surface(const ScreenSizeInfo& dimensions, const unsigned int alignBytes = FAT_DEFAULT_ALIGNMENT);
        explicit Surface(const unsigned int width, const unsigned int height, const unsigned int alignBytes = FAT_DEFAULT_ALIGNMENT);

        explicit Surface() noexcept;
        Surface(const Surface& src);
        Surface(Surface&& src) noexcept;

        auto operator = (const Surface& src)     -> Surface&;
        auto operator = (Surface&& src) noexcept -> Surface&;
        ~Surface() noexcept = default;


    public:
        operator Color* () &  noexcept;
        operator Color* () && noexcept;
        operator volatile Color* () volatile &  noexcept;
        operator volatile Color* () volatile && noexcept;


    public:
        static auto CalculatePixelPitch(const unsigned int width, const unsigned int alignBytes) noexcept -> unsigned int;


    public:
        template <FATSPACE_MATH::numset::Rational Q> __forceinline auto GetWidth()      const noexcept -> Q
        {
            return static_cast<Q>(m_width_);
        }
        template <FATSPACE_MATH::numset::Rational Q> __forceinline auto GetHeight()     const noexcept -> Q
        {
            return static_cast<Q>(m_height_);
        }
        template <FATSPACE_MATH::numset::Rational Q> __forceinline auto GetAlignment()  const noexcept -> Q
        {
            return static_cast<Q>(m_align_byte_);
        }
        template <FATSPACE_MATH::numset::Rational Q> __forceinline auto GetPixelPitch() const noexcept -> Q
        {
            return static_cast<Q>(m_pixel_pitch_);
        }
        template <FATSPACE_MATH::numset::Rational Q> __forceinline auto GetPitch()      const noexcept -> Q
        {
            return static_cast<Q>(m_pixel_pitch_ * sizeof(Color));
        }

        template <std::integral N> __forceinline auto GetPixel(const N x, const N y) const -> Color
        {
            if constexpr (std::signed_integral<N>)
            {
                assert(x >= 0);
                assert(y >= 0);
            }

            assert(x < GetWidth<N>());
            assert(y < GetHeight<N>());

            return m_pBuffer_[y * m_pixel_pitch_ + x];
        }
        template <std::integral N> __forceinline void PutPixel(const N x, const N y, const Color color) noexcept
        {
            if constexpr (std::signed_integral<N>)
            {
                assert(x >= 0);
                assert(y >= 0);
            }
            
            assert(x < GetWidth<N>());
            assert(y < GetHeight<N>());

            m_pBuffer_[y * m_pixel_pitch_ + x] = color;
        }


    public:
        auto ReleaseBuffer() noexcept -> Color*;

        auto GetScreenSizeInfo() const noexcept -> ScreenSizeInfo;

        auto IsEmpty() const noexcept -> bool;

        void Fill(const Color& color) noexcept;
        void Clear() noexcept;


    protected:


    private:
        void DeepCopyFrom_(const Surface& src) noexcept;


    private:
        FATSPACE_MEMORY::unique_ptr_aligned_array<Color> m_pBuffer_;

        unsigned int m_width_{};
        unsigned int m_height_{};
        unsigned int m_align_byte_{};
        unsigned int m_pixel_pitch_{};
    };
}

module : private;