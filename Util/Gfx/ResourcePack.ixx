module;

#if defined(_MSC_VER)
#include <FatNamespaces.hpp>

#include <FatWin32.hpp>
#include <d3d11.h>
#include <wrl.h>
#endif

export module FatPound.Util.Gfx.ResourcePack;

#if defined(_MSC_VER)

import FatPound.Util.Gfx.SizePack;

import FatPound.Util.Surface;

export namespace fatpound::util::gfx
{
    struct ResourcePack
    {
        ::Microsoft::WRL::ComPtr<::IDXGISwapChain>         m_pSwapChain;
        ::Microsoft::WRL::ComPtr<::ID3D11Device>           m_pDevice;
        ::Microsoft::WRL::ComPtr<::ID3D11DeviceContext>    m_pImmediateContext;
        ::Microsoft::WRL::ComPtr<::ID3D11RenderTargetView> m_pRTV;
        ::Microsoft::WRL::ComPtr<::ID3D11DepthStencilView> m_pDSV;
    };

    struct FrameworkResourcePack final : public ResourcePack
    {
        ::Microsoft::WRL::ComPtr<::ID3D11Texture2D> m_pSysbufferTex2d;
        ::D3D11_MAPPED_SUBRESOURCE                  m_mappedSysbufferTex2d{};
        Surface                                     m_surface;

        FrameworkResourcePack(const SizePack& dimensions)
            :
            m_surface(dimensions)
        {

        }
    };
}

#endif

module : private;
