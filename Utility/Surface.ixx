module;

#include <_macros/Compiler.hxx>
#include <_macros/Namespaces.hxx>

#include <cassert>

export module FatPound.Utility.Surface;

#ifdef FATLIB_BUILDING_WITH_MSVC
    import <Win32_/WinAPI.hxx>;
    import FatPound.Win32.GDI_Plus.Manager;
#endif

import FatPound.Colors.ARGB;
import FatPound.Memory;
import FatPound.Traits.Bitwise;
import FatPound.Utility.Common;
import FatPound.Utility.SizePack;

import std;

export namespace fatpound::utility
{
    /// @brief Represents a 2D pixel surface with aligned memory storage, supporting pixel access, modification
    ///
    class Surface
    {
    public:
        using Color_t    = colors::argb::Color;
        using ColorArr_t = Color_t[];
        using Size_t     = std::size_t;


    public:
        static constexpr Size_t scx_DefaultAlignment = 16U;


    public:
#ifdef FATLIB_BUILDING_WITH_MSVC
        explicit Surface(const std::filesystem::path& path,         const Size_t& alignBytes = scx_DefaultAlignment)
            :
            Surface(path.wstring(), alignBytes)
        {

        }
        explicit Surface(const std::string& filename,               const Size_t& alignBytes = scx_DefaultAlignment)
            :
            Surface(To_WString(filename), alignBytes)
        {

        }
        explicit Surface(const std::wstring& filename,              const Size_t& alignBytes = scx_DefaultAlignment)
            :
            m_pBuffer_(nullptr, nullptr)
        {
            FATSPACE_WIN32::gdi_plus::Manager gdiplusmgr;

            Gdiplus::Bitmap bitmap(filename.c_str());

            if (bitmap.GetLastStatus() not_eq Gdiplus::Ok)
            {
                throw std::runtime_error("GDI+ Bitmap error in Surface ctor!");
            }

            const auto& width  = bitmap.GetWidth();
            const auto& height = bitmap.GetHeight();

            Surface surf(width, height, alignBytes);

            for (auto y = 0U; y < height; ++y)
            {
                for (auto x = 0U; x < width; ++x)
                {
                    Gdiplus::Color c;

                    bitmap.GetPixel(static_cast<INT>(x), static_cast<INT>(y), &c);
                    surf.PutPixel<>(x, y, Color_t{ c.GetValue() });
                }
            }

            *this = std::move(surf);
        }
#endif
        explicit Surface(const SizePack& dimensions,                const Size_t& alignBytes = scx_DefaultAlignment)
            :
            m_pBuffer_(memory::MakeAlignedUniquePtr<ColorArr_t>(alignBytes, dimensions.m_width * dimensions.m_height)),
            m_size_pack_(dimensions),
            m_align_byte_(alignBytes),
            m_pixel_pitch_(CalculatePixelPitch(GetWidth<>(), GetAlignment<>()))
        {

        }
        explicit Surface(const Size_t& width, const Size_t& height, const Size_t& alignBytes = scx_DefaultAlignment)
            :
            Surface(SizePack{ .m_width = width, .m_height = height }, alignBytes)
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
            if (this not_eq std::addressof(src))
            {
                Reset();

                m_pBuffer_     = memory::MakeAlignedUniquePtr<ColorArr_t>(src.GetAlignment(), static_cast<std::size_t>(src.GetWidth<>() * src.GetHeight<>()));

                m_size_pack_   = src.GetSizePack();
                m_align_byte_  = src.GetAlignment<>();
                m_pixel_pitch_ = src.GetPixelPitch<>();

                DeepCopyFrom_(src);
            }

            return *this;
        }
        auto operator = (Surface&& src) noexcept -> Surface&
        {
            if (this not_eq std::addressof<>(src))
            {
                Reset();

                m_pBuffer_     = std::move<>(src.m_pBuffer_);

                m_size_pack_   = src.GetSizePack();
                m_align_byte_  = src.GetAlignment<>();
                m_pixel_pitch_ = src.GetPixelPitch<>();

                src.Reset();
            }

            return *this;
        }
        ~Surface() noexcept = default;


    public:
        // NOLINTBEGIN(google-explicit-constructor, hicpp-explicit-conversions)
        operator const Color_t*() const& noexcept
        {
            return m_pBuffer_.get();
        }
        operator       Color_t* ()       & noexcept
        {
            return m_pBuffer_.get();
        }
        // NOLINTEND(google-explicit-constructor, hicpp-explicit-conversions)

        explicit operator bool () const noexcept
        {
            return IsEmpty();
        }

        
    public:
        static auto CalculatePixelPitch(const Size_t& width, const Size_t& alignBytes) noexcept -> Size_t
        {
            assert(alignBytes % 4 == 0);
            assert(alignBytes >= sizeof(Color_t));
            assert(alignBytes <= width);

            const auto& pixelsPerAlign = alignBytes / static_cast<Size_t>(sizeof(Color_t));
            const auto& overrunCount   = width % pixelsPerAlign;

            return width + ((pixelsPerAlign - overrunCount) % pixelsPerAlign);
        }


    public:
        template <traits::IntegralOrFloating T = Size_t> [[nodiscard]] FATLIB_FORCEINLINE auto GetWidth      () const noexcept -> T
        {
            return static_cast<T>(m_size_pack_.m_width);
        }
        template <traits::IntegralOrFloating T = Size_t> [[nodiscard]] FATLIB_FORCEINLINE auto GetHeight     () const noexcept -> T
        {
            return static_cast<T>(m_size_pack_.m_height);
        }
        template <traits::IntegralOrFloating T = Size_t> [[nodiscard]] FATLIB_FORCEINLINE auto GetAlignment  () const noexcept -> T
        {
            return static_cast<T>(m_align_byte_);
        }
        template <traits::IntegralOrFloating T = Size_t> [[nodiscard]] FATLIB_FORCEINLINE auto GetPixelPitch () const noexcept -> T
        {
            return static_cast<T>(m_pixel_pitch_);
        }
        template <traits::IntegralOrFloating T = Size_t> [[nodiscard]] FATLIB_FORCEINLINE auto GetPitch      () const noexcept -> T
        {
            return static_cast<T>(m_pixel_pitch_ * sizeof(Color_t));
        }

        template <std::unsigned_integral T> [[nodiscard]] FATLIB_FORCEINLINE auto GetPixel(const T& x, const T& y) const -> Color_t
        {
            assert(x < GetWidth<T>());
            assert(y < GetHeight<T>());

            return m_pBuffer_[(y * m_pixel_pitch_) + x];
        }
        template <std::unsigned_integral T>               FATLIB_FORCEINLINE void PutPixel(const T& x, const T& y, const Color_t& color) noexcept
        {
            assert(x < GetWidth<T>());
            assert(y < GetHeight<T>());

            m_pBuffer_[(static_cast<std::size_t>(y) * m_pixel_pitch_) + static_cast<std::size_t>(x)] = color;
        }

        template <std::signed_integral T>   [[nodiscard]] FATLIB_FORCEINLINE auto GetPixel(const T& x, const T& y) const -> Color_t
        {
            assert(x >= 0);
            assert(y >= 0);

            return GetPixel<>(
                static_cast<std::make_unsigned_t<T>>(x),
                static_cast<std::make_unsigned_t<T>>(y)
            );
        }
        template <std::signed_integral T>                 FATLIB_FORCEINLINE void PutPixel(const T& x, const T& y, const Color_t& color) noexcept
        {
            assert(x >= 0);
            assert(y >= 0);

            PutPixel<>(
                static_cast<std::make_unsigned_t<T>>(x),
                static_cast<std::make_unsigned_t<T>>(y),
                color
            );
        }


    public:
        auto ReleaseAndReset() noexcept -> Color_t*
        {
            auto* const ptr = m_pBuffer_.release();
            
            Reset();

            return ptr;
        }

        [[nodiscard]] auto GetSizePack() const noexcept -> SizePack
        {
            return m_size_pack_;
        }

        [[nodiscard]] auto IsEmpty() const noexcept -> bool
        {
            return m_pBuffer_ == nullptr;
        }
        [[nodiscard]] auto IsNotEmpty() const noexcept -> bool
        {
            return not IsEmpty();
        }

        void Fill(const Color_t& color) noexcept
        {
#ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
            std::memset(
                *this,
                static_cast<int>(color),
                GetWidth<std::size_t>() * GetHeight<std::size_t>() * sizeof(Color_t)
            );
#ifdef __clang__
    #pragma clang diagnostic pop
#endif
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
#ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif
                  Color_t* const pDest = *this;
            const Color_t* const pSrc  = src;

            const auto srcPitch = src.GetPitch<>();

            for (auto y = 0U; y < src.GetHeight<>(); ++y)
            {
                // NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                std::memcpy(
                    &pDest[y * GetPixelPitch<std::size_t>()],
                    &pSrc[y * src.GetPixelPitch<std::size_t>()],
                    srcPitch
                );
                // NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            }
#ifdef __clang__
    #pragma clang diagnostic pop
#endif
        }


    private:
        memory::AlignedUniquePtr<ColorArr_t>   m_pBuffer_;

        SizePack                               m_size_pack_;

        Size_t                                 m_align_byte_{};
        Size_t                                 m_pixel_pitch_{};
    };
}

// module : private;
