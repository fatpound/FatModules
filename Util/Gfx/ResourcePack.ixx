module;


#if FAT_BUILDING_WITH_MSVC
#include <FatNamespaces.hpp>

#include <FatWin32.hpp>
#include <wrl.h>
#endif

export module FatPound.Util.Gfx.ResourcePack;

#if FAT_BUILDING_WITH_MSVC

import <d3d11.h>;

import FatPound.Util.Gfx.SizePack;
import FatPound.Util.Surface;

namespace wrl = Microsoft::WRL;

export namespace fatpound::util::gfx
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
        wrl::ComPtr<::ID3D11Texture2D> m_pSysbufferTex2d;
        D3D11_MAPPED_SUBRESOURCE       m_mappedSysbufferTex2d{};
        Surface                        m_surface;

        FrameworkResourcePack(const SizePack& dimensions)
            :
            m_surface(dimensions)
        {

        }
    };
}

#endif

module : private;
