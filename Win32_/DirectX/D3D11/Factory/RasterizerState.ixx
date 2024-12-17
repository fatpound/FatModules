module;

#include <FatWin32_Settings.hpp>
#include <FatNamespaces.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory.RasterizerState;

import FatPound.Util.Gfx;

import std;

export namespace fatpound::win32::d3d11::factory
{
    constexpr auto Create_RasterizerState_DESC() noexcept -> D3D11_RASTERIZER_DESC
    {
        D3D11_RASTERIZER_DESC desc{};
        desc.FillMode = D3D11_FILL_SOLID;
        desc.CullMode = D3D11_CULL_BACK;
        desc.FrontCounterClockwise = false;
        desc.DepthBias = 0;
        desc.DepthBiasClamp = 0.0f;
        desc.SlopeScaledDepthBias = 0.0f;
        desc.DepthClipEnable = true;
        desc.ScissorEnable = false;
        desc.MultisampleEnable = true;
        desc.AntialiasedLineEnable = true;

        return desc;
    }

    void Create_RasterizerState(
        const FATSPACE_UTIL_GFX::ResourcePack& gfxResPack,
        const D3D11_RASTERIZER_DESC& desc,
        ::Microsoft::WRL::ComPtr<ID3D11RasterizerState>& pRasterizerState);

    void Create_RasterizerState(
        ID3D11Device* const pDevice,
        const D3D11_RASTERIZER_DESC& desc,
        ::Microsoft::WRL::ComPtr<ID3D11RasterizerState>& pRasterizerState);
}