module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.ResourcePack;

#ifdef FATLIB_BUILDING_WITH_MSVC

import FatPound.Utility.SizePack;
import FatPound.Utility.Surface;
import FatPound.Win32.D3D11.Core.DepthStencil;
import FatPound.Win32.D3D11.Core.RenderTarget;
import FatPound.Win32.D3D11.Resource.Texture2D;

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import <wrl.h>;
#endif

namespace fatpound::win32::d3d11
{
    struct ResourcePackBase
    {
        explicit ResourcePackBase() noexcept                   = default;
        explicit ResourcePackBase(const ResourcePackBase&)     = delete;
        explicit ResourcePackBase(ResourcePackBase&&) noexcept = default;

        auto operator = (const ResourcePackBase&)     -> ResourcePackBase& = delete;
        auto operator = (ResourcePackBase&&) noexcept -> ResourcePackBase& = default;
        ~ResourcePackBase() noexcept                                       = default;

        Microsoft::WRL::ComPtr<IDXGISwapChain>        m_pSwapChain;
        Microsoft::WRL::ComPtr<ID3D11Device>          m_pDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>   m_pImmediateContext;
        win32::d3d11::core::RenderTarget              m_render_target;
    };
}

export namespace fatpound::win32::d3d11
{
    struct ResourcePack : ResourcePackBase
    {
        explicit ResourcePack() noexcept               = default;
        explicit ResourcePack(const ResourcePack&)     = delete;
        explicit ResourcePack(ResourcePack&&) noexcept = default;

        auto operator = (const ResourcePack&)     -> ResourcePack& = delete;
        auto operator = (ResourcePack&&) noexcept -> ResourcePack& = default;
        ~ResourcePack() noexcept                                   = default;
    };

    struct FrameworkResourcePack : ResourcePackBase
    {
        explicit FrameworkResourcePack(const utility::SizePack& dimensions)
            :
            m_surface(dimensions)
        {

        }

        explicit FrameworkResourcePack() noexcept                        = default;
        explicit FrameworkResourcePack(const FrameworkResourcePack&)     = delete;
        explicit FrameworkResourcePack(FrameworkResourcePack&&) noexcept = default;

        auto operator = (const FrameworkResourcePack&)     -> FrameworkResourcePack& = delete;
        auto operator = (FrameworkResourcePack&&) noexcept -> FrameworkResourcePack& = default;
        ~FrameworkResourcePack() noexcept                                            = default;

        win32::d3d11::resource::Texture2D   m_sysbufferTex2d;
        D3D11_MAPPED_SUBRESOURCE            m_mappedSysbufferTex2d{};
        utility::Surface                    m_surface;
    };
}

#endif

// module : private;
