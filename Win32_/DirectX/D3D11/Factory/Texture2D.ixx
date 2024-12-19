module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory.Texture2D;

import FatPound.Util.Gfx;

import FatPound.Util;

import std;

export namespace fatpound::win32::d3d11::factory
{
    template <bool ForShaderResource = false>
    constexpr auto Create_Texture2D_DESC(
        const FATSPACE_UTIL::ScreenSizeInfo gfxDimensions,
        const UINT msaaCount,
        const UINT msaaQuality) noexcept -> D3D11_TEXTURE2D_DESC
    {
        D3D11_TEXTURE2D_DESC desc{};
        desc.Width = gfxDimensions.m_width;
        desc.Height = gfxDimensions.m_height;
        desc.MipLevels = 1u;
        desc.ArraySize = 1u;

        if constexpr (ForShaderResource)
        {
            desc.SampleDesc.Count = 1;
            desc.SampleDesc.Quality = 0;
            desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
            desc.Usage = D3D11_USAGE_DYNAMIC;
            desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        }
        else
        {
            desc.SampleDesc.Count = msaaCount;
            desc.SampleDesc.Quality = msaaQuality - 1u;
            desc.Format = DXGI_FORMAT_D32_FLOAT;
            desc.Usage = D3D11_USAGE_DEFAULT;
            desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        }

        return desc;
    }

    void Create_Texture2D(FATSPACE_UTIL_GFX::FrameworkResourcePack& gfxFwkResPack, const D3D11_TEXTURE2D_DESC& desc);

    void Create_Texture2D(
        ID3D11Device* const pDevice,
        const D3D11_TEXTURE2D_DESC& desc,
        ::Microsoft::WRL::ComPtr<ID3D11Texture2D>& pTexture2D);
}