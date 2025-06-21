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

import <d3d11.h>;

import FatPound.Utility.Gfx.SizePack;
import FatPound.Utility.Surface;

#ifndef __INTELLISENSE__
    import FatPound.Win32.WRL.Common;
#else
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::utility::gfx
{
    struct ResourcePack
    {
        wrl::ComPtr<IDXGISwapChain>         m_pSwapChain;
        wrl::ComPtr<ID3D11Device>           m_pDevice;
        wrl::ComPtr<ID3D11DeviceContext>    m_pImmediateContext;
        wrl::ComPtr<ID3D11RenderTargetView> m_pRTV;
        wrl::ComPtr<ID3D11DepthStencilView> m_pDSV;
    };

    struct FrameworkResourcePack final : public ResourcePack
    {
        wrl::ComPtr<::ID3D11Texture2D>      m_pSysbufferTex2d;
        D3D11_MAPPED_SUBRESOURCE            m_mappedSysbufferTex2d{};
        Surface                             m_surface;

        FrameworkResourcePack(const SizePack& dimensions)
            :
            m_surface(dimensions)
        {

        }
    };
}

#endif

module : private;
