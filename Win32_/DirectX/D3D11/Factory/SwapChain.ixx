module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory.SwapChain;

import FatPound.Util.Gfx;

import FatPound.Win32.DXGI;

import FatPound.Util;

import std;

export namespace fatpound::win32::d3d11::factory
{
    template <
        bool ForFramework = false,
        bool Fullscreen = false
    >
    auto Create_SwapChain_DESC(
        const HWND hWnd,
        const FATSPACE_UTIL::ScreenSizeInfo gfxDimensions,
        [[maybe_unused]] const UINT msaaCount,
        [[maybe_unused]] const UINT msaaQuality) noexcept -> DXGI_SWAP_CHAIN_DESC
    {
        DXGI_SWAP_CHAIN_DESC desc{};
        desc.BufferDesc.Width = gfxDimensions.m_width;
        desc.BufferDesc.Height = gfxDimensions.m_height;
        desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        desc.BufferDesc.RefreshRate.Numerator = 0u;
        desc.BufferDesc.RefreshRate.Denominator = 0u;
        desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = 1u;
        desc.OutputWindow = hWnd;
        desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        desc.Flags = 0u;

        if constexpr (ForFramework)
        {
            desc.SampleDesc.Count = 1u;
            desc.SampleDesc.Quality = 0u;
        }
        else
        {
            desc.SampleDesc.Count = msaaCount;
            desc.SampleDesc.Quality = msaaQuality - 1u;
        }

        if constexpr (Fullscreen and not ForFramework)
        {
            desc.Windowed = false;
        }
        else
        {
            desc.Windowed = true;
        }

        return desc;
    }

    void Create_SwapChain(FATSPACE_UTIL_GFX::ResourcePack& gfxResPack, DXGI_SWAP_CHAIN_DESC& desc);

    void Create_SwapChain(
        ID3D11Device* const pDevice,
        DXGI_SWAP_CHAIN_DESC& desc,
        ::Microsoft::WRL::ComPtr<IDXGISwapChain>& pSwapChain);
}