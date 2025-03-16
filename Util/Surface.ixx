module;

#include <FatNamespaces.hpp>
#include <FatDefines.hpp>

#if defined(_MSC_VER)
#define FATPOUND_FULL_WIN_TARGETED
#include <FatWin32.hpp>
#include <gdiplus.h>
#undef FATPOUND_FULL_WIN_TARGETED
#pragma comment(lib, "gdiplus")
#endif

#include <cassert>

export module FatPound.Util.Surface;

import FatPound.Util.Color;
import FatPound.Util.Common;
import FatPound.Util.Gfx.SizePack;

import FatPound.Bitwise.Concepts;
import FatPound.Memory;

#if defined(_MSC_VER)
import FatPound.Win32.GDI_Plus;
#endif

import std;

export namespace fatpound::util
{
    class Surface final
    {
        using Color_t = Color[];
        using Ptr_t = memory::AlignedUniquePtr<Color_t>;

    public:
        using Size_t = ::std::uint32_t;


    public:
        static constexpr Size_t scx_DefaultAlignment = 16u;


    public:
#if defined(_MSC_VER)
        explicit Surface(const std::filesystem::path& path,         const Size_t& alignBytes = scx_DefaultAlignment)
            :
            Surface(path.wstring(), alignBytes)
        {

        }
        explicit Surface(const std::string& filename,               const Size_t& alignBytes = scx_DefaultAlignment)
            :
            Surface(ToWString(filename), alignBytes)
        {

        }
        explicit Surface(const std::wstring& filename,              const Size_t& alignBytes = scx_DefaultAlignment)
            :
            m_pBuffer_(nullptr, nullptr)
        {
            FATSPACE_WIN32::gdi_plus::Manager gdiplusmgr;

            ::Gdiplus::Bitmap bitmap(filename.c_str());

            if (bitmap.GetLastStatus() not_eq ::Gdiplus::Ok)
            {
                throw std::runtime_error("GDI+ Bitmap error in Surface ctor!");
            }

            const auto width  = bitmap.GetWidth();
            const auto height = bitmap.GetHeight();

            Surface surf(width, height, alignBytes);

            for (auto y = 0u; y < height; ++y)
            {
                for (auto x = 0u; x < width; ++x)
                {
                    ::Gdiplus::Color c;

                    bitmap.GetPixel(static_cast<INT>(x), static_cast<INT>(y), &c);
                    surf.PutPixel<>(x, y, Color{ c.GetValue() });
                }
            }

            *this = std::move(surf);
        }
#endif
        explicit Surface(const gfx::SizePack& dimensions,           const Size_t& alignBytes = scx_DefaultAlignment)
            :
            m_pBuffer_(memory::MakeAlignedUniquePtr<Color_t>(alignBytes, dimensions.m_width * dimensions.m_height)),
            m_size_pack_(dimensions),
            m_align_byte_(alignBytes),
            m_pixel_pitch_(CalculatePixelPitch(GetWidth<>(), GetAlignment<>()))
        {

        }
        explicit Surface(const Size_t& width, const Size_t& height, const Size_t& alignBytes = scx_DefaultAlignment)
            :
            Surface(gfx::SizePack{ width, height }, alignBytes)
        {

        }

        explicit Surface() noexcept
            :
            m_pBuffer_(nullptr, nullptr)
        {

        }
        Surface(const Surface& src)
            :
            Surface(src.GetSizePack(), src.GetAlignment<>())
        {
            DeepCopyFrom_(src);
        }
        Surface(Surface&& src) noexcept
            :
            m_pBuffer_(std::move<>(src.m_pBuffer_)),
            m_size_pack_(src.GetWidth<>(), src.GetHeight<>()),
            m_align_byte_(src.GetAlignment<>()),
            m_pixel_pitch_(src.GetPixelPitch<>())
        {
            src.Reset();
        }

        auto operator = (const Surface& src)     -> Surface&
        {
            if (this not_eq ::std::addressof(src))
            {
                Reset();

                m_pBuffer_     = memory::MakeAlignedUniquePtr<Color_t>(src.GetAlignment(), src.GetWidth<>() * src.GetHeight<>());

                m_size_pack_   = src.GetSizePack();
                m_align_byte_  = src.GetAlignment<>();
                m_pixel_pitch_ = src.GetPixelPitch<>();

                DeepCopyFrom_(src);
            }

            return *this;
        }
        auto operator = (Surface&& src) noexcept -> Surface&
        {
            if (this not_eq ::std::addressof<>(src))
            {
                Reset();

                m_pBuffer_     = ::std::move<>(src.m_pBuffer_);

                m_size_pack_   = src.GetSizePack();
                m_align_byte_  = src.GetAlignment<>();
                m_pixel_pitch_ = src.GetPixelPitch<>();

                src.Reset();
            }

            return *this;
        }
        ~Surface() noexcept = default;


    public:
        operator const Color* () const & noexcept
        {
            return m_pBuffer_.get();
        }
        operator       Color* ()       & noexcept
        {
            return m_pBuffer_.get();
        }

        operator bool () const noexcept
        {
            return IsEmpty();
        }

        
    public:
        static auto CalculatePixelPitch(const Size_t& width, const Size_t& alignBytes) noexcept -> Size_t
        {
            assert(alignBytes % 4 == 0);
            assert(alignBytes >= sizeof(Color));
            assert(alignBytes <= width);

            const auto pixelsPerAlign = alignBytes / static_cast<Size_t>(sizeof(Color));
            const auto overrunCount   = width % pixelsPerAlign;

            return width + (pixelsPerAlign - overrunCount) % pixelsPerAlign;
        }


    public:
        template <bitwise::Integral_Or_Floating T = Size_t> FAT_FORCEINLINE auto GetWidth      () const noexcept -> T
        {
            return static_cast<T>(m_size_pack_.m_width);
        }
        template <bitwise::Integral_Or_Floating T = Size_t> FAT_FORCEINLINE auto GetHeight     () const noexcept -> T
        {
            return static_cast<T>(m_size_pack_.m_height);
        }
        template <bitwise::Integral_Or_Floating T = Size_t> FAT_FORCEINLINE auto GetAlignment  () const noexcept -> T
        {
            return static_cast<T>(m_align_byte_);
        }
        template <bitwise::Integral_Or_Floating T = Size_t> FAT_FORCEINLINE auto GetPixelPitch () const noexcept -> T
        {
            return static_cast<T>(m_pixel_pitch_);
        }
        template <bitwise::Integral_Or_Floating T = Size_t> FAT_FORCEINLINE auto GetPitch      () const noexcept -> T
        {
            return static_cast<T>(m_pixel_pitch_ * sizeof(Color));
        }

        template <::std::integral T> FAT_FORCEINLINE auto GetPixel(const T& x, const T& y) const -> Color
        {
            if constexpr (::std::signed_integral<T>)
            {
                assert(x >= 0);
                assert(y >= 0);
            }

            assert(x < GetWidth<T>());
            assert(y < GetHeight<T>());

            return m_pBuffer_[y * m_pixel_pitch_ + x];
        }
        template <::std::integral T> FAT_FORCEINLINE void PutPixel(const T& x, const T& y, const Color& color) noexcept
        {
            if constexpr (::std::signed_integral<T>)
            {
                assert(x >= 0);
                assert(y >= 0);
            }
            
            assert(x < GetWidth<T>());
            assert(y < GetHeight<T>());

            m_pBuffer_[y * m_pixel_pitch_ + x] = color;
        }


    public:
        auto ReleaseAndReset() noexcept -> Color*
        {
            auto* const ptr = m_pBuffer_.release();
            
            Reset();

            return ptr;
        }

        auto GetSizePack() const noexcept -> gfx::SizePack
        {
            return m_size_pack_;
        }

        auto IsEmpty() const noexcept -> bool
        {
            return m_pBuffer_ == nullptr;
        }
        auto IsNotEmpty() const noexcept -> bool
        {
            return not IsEmpty();
        }

        void Fill(const Color& color) noexcept
        {
            ::std::memset(
                *this,
                static_cast<int>(color),
                GetWidth<>() * GetHeight<>() * sizeof(Color)
            );
        }
        void Reset() noexcept
        {
            if (m_pBuffer_ not_eq nullptr)
            {
                m_pBuffer_.reset();
            }

            m_size_pack_.m_width  = static_cast<Size_t>(0);
            m_size_pack_.m_height = static_cast<Size_t>(0);
            m_align_byte_         = static_cast<Size_t>(0);
            m_pixel_pitch_        = static_cast<Size_t>(0);
        }


    protected:


    private:
        void DeepCopyFrom_(const Surface& src) noexcept
        {
                  Color* const pDest = *this;
            const Color* const pSrc  = src;

            const auto srcPitch = src.GetPitch<>();

            for (auto y = 0u; y < src.GetHeight<>(); ++y)
            {
                ::std::memcpy(
                    &pDest[y * GetPixelPitch<>()],
                    &pSrc[y * src.GetPixelPitch<>()],
                    srcPitch
                );
            }
        }


    private:
        Ptr_t m_pBuffer_;

        gfx::SizePack m_size_pack_;

        Size_t m_align_byte_{};
        Size_t m_pixel_pitch_{};
    };
}

module : private;
