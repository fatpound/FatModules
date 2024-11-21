module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Factory.DepthStencilState;

import FatPound.Win32.D3D11.Graphics.ResourcePack;

import std;

export namespace fatpound::win32::d3d11::factory
{
    constexpr auto Create_DepthStencilState_DESC() noexcept -> D3D11_DEPTH_STENCIL_DESC
    {
        D3D11_DEPTH_STENCIL_DESC desc{};
        desc.DepthEnable = true;
        desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        desc.DepthFunc = D3D11_COMPARISON_LESS;

        return desc;
    }

    void Create_DepthStencilState(
        const GraphicsResourcePack& gfxResPack,
        const D3D11_DEPTH_STENCIL_DESC& desc,
        ::Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& pDSState);

    void Create_DepthStencilState(
        ID3D11Device* const pDevice,
        const D3D11_DEPTH_STENCIL_DESC& desc,
        ::Microsoft::WRL::ComPtr<ID3D11DepthStencilState>& pDSState);
}