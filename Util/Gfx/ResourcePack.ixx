module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Util.Gfx.ResourcePack;

import FatPound.Util.Color;
import FatPound.Util.ScreenSizeInfo;
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
        ::Microsoft::WRL::ComPtr<::ID3D11Texture2D> m_pSysBufferTexture;

        ::D3D11_MAPPED_SUBRESOURCE m_mappedSysBufferTexture{};

        FATSPACE_UTIL::Surface m_surface;

        FrameworkResourcePack(const FATSPACE_UTIL::ScreenSizeInfo& dimensions)
            :
            m_surface(dimensions)
        {

        }
    };
}