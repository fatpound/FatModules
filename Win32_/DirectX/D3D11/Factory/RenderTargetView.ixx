module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory.RenderTargetView;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::factory
{
    void Create_RenderTargetView(
        IDXGISwapChain* const pSwapChain,
        ID3D11Device* const pDevice,
        ::Microsoft::WRL::ComPtr<ID3D11RenderTargetView>& pRenderTargetView);

    void Create_RenderTargetView(CGfxResPack auto& gfxResPack)
    {
        Create_RenderTargetView(
            gfxResPack.m_pSwapChain.Get(),
            gfxResPack.m_pDevice.Get(),
            gfxResPack.m_pRTV
        );
    }
}