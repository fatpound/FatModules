module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory.DepthStencilState;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void Create_DepthStencilState(
        const GraphicsResourcePack& gfxResPack,
        const D3D11_DEPTH_STENCIL_DESC& desc,
        ::wrl::ComPtr<ID3D11DepthStencilState>& pDSState)
    {
        Create_DepthStencilState(gfxResPack.m_pDevice.Get(), desc, pDSState);
    }

    void Create_DepthStencilState(
        ID3D11Device* const pDevice,
        const D3D11_DEPTH_STENCIL_DESC& desc,
        ::wrl::ComPtr<ID3D11DepthStencilState>& pDSState)
    {
        const auto& hr = pDevice->CreateDepthStencilState(&desc, &pDSState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilState!");
        }
    }
}