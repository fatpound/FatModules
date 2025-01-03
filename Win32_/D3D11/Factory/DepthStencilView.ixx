module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory.DepthStencilView;

import FatPound.Util.Gfx;

import std;

export namespace fatpound::win32::d3d11::factory
{
    constexpr auto Create_DepthStencilView_DESC(const UINT msaaCount) noexcept -> D3D11_DEPTH_STENCIL_VIEW_DESC
    {
        D3D11_DEPTH_STENCIL_VIEW_DESC desc{};
        desc.Format = DXGI_FORMAT_D32_FLOAT;

        if (msaaCount == 1u)
        {
            desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
            desc.Texture2D.MipSlice = 0u;
        }
        else
        {
            desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
            desc.Texture2D.MipSlice = 1u;
        }

        return desc;
    }

    void Create_DepthStencilView(
        ID3D11Device* const pDevice,
        const ::Microsoft::WRL::ComPtr<ID3D11Texture2D>& pDepthStencil,
        const D3D11_DEPTH_STENCIL_VIEW_DESC& desc,
        ::Microsoft::WRL::ComPtr<ID3D11DepthStencilView>& pDSV)
    {
        const auto& hr = pDevice->CreateDepthStencilView(pDepthStencil.Get(), &desc, &pDSV);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilView!");
        }
    }

    void Create_DepthStencilView(
        FATSPACE_UTIL_GFX::ResourcePack& gfxResPack,
        const ::Microsoft::WRL::ComPtr<ID3D11Texture2D>& pDepthStencil,
        const D3D11_DEPTH_STENCIL_VIEW_DESC& desc)
    {
        Create_DepthStencilView(gfxResPack.m_pDevice.Get(), pDepthStencil, desc, gfxResPack.m_pDSV);
    }
}

module : private;