module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Utility.Gfx.ResourcePack;

#ifdef FATLIB_BUILDING_WITH_MSVC

import FatPound.Utility.Gfx.SizePack;
import FatPound.Utility.Surface;
import FatPound.Win32.D3D11.Pipeline.RenderTarget;
import FatPound.Win32.D3D11.Pipeline.DepthStencil;

#ifndef __INTELLISENSE__
    import <d3d11.h>;
    import FatPound.Win32.WRL.Common;
#else
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::utility::gfx
{
    struct ResourcePack
    {
        explicit ResourcePack() noexcept               = default;
        explicit ResourcePack(const ResourcePack&)     = delete;
        explicit ResourcePack(ResourcePack&&) noexcept = delete;

        auto operator = (const ResourcePack&)     -> ResourcePack& = delete;
        auto operator = (ResourcePack&&) noexcept -> ResourcePack& = delete;
        ~ResourcePack() noexcept                                   = default;

        wrl::ComPtr<IDXGISwapChain>            m_pSwapChain;
        wrl::ComPtr<ID3D11Device>              m_pDevice;
        wrl::ComPtr<ID3D11DeviceContext>       m_pImmediateContext;
        win32::d3d11::pipeline::RenderTarget   m_render_target;
        win32::d3d11::pipeline::DepthStencil   m_depth_stencil;
    };

    struct FrameworkResourcePack final : public ResourcePack
    {
        win32::d3d11::pipeline::Texture2D      m_sysbufferTex2d;
        D3D11_MAPPED_SUBRESOURCE               m_mappedSysbufferTex2d{};
        Surface                                m_surface;

        explicit FrameworkResourcePack(const SizePack& dimensions)
            :
            m_surface(dimensions)
        {

        }

        explicit FrameworkResourcePack() noexcept                        = default;
        explicit FrameworkResourcePack(const FrameworkResourcePack&)     = delete;
        explicit FrameworkResourcePack(FrameworkResourcePack&&) noexcept = delete;

        auto operator = (const FrameworkResourcePack&)     -> FrameworkResourcePack& = delete;
        auto operator = (FrameworkResourcePack&&) noexcept -> FrameworkResourcePack& = delete;
        ~FrameworkResourcePack() noexcept                                            = default;
    };
}

#endif

module : private;
