module;

#include <FatNamespaces.hpp>

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory.RenderTargetView;

import FatPound.Util.Gfx;

import std;

export namespace fatpound::win32::d3d11::factory
{
    void Create_RenderTargetView(FATSPACE_UTIL_GFX::ResourcePack& gfxResPack);

    void Create_RenderTargetView(
        IDXGISwapChain* const pSwapChain,
        ID3D11Device* const pDevice,
        ::Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& pRenderTargetView);
}