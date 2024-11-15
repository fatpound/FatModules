module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:DepthStencilView;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void DepthStencilView::Create(
            GraphicsResourcePack& gfxResPack,
            const ::wrl::ComPtr<ID3D11Texture2D>& pDepthStencil,
            const D3D11_DEPTH_STENCIL_VIEW_DESC& desc)
    {
        Create(gfxResPack.m_pDevice.Get(), pDepthStencil, desc, gfxResPack.m_pDSV);
    }

    void DepthStencilView::Create(
            ID3D11Device* const pDevice,
            const ::wrl::ComPtr<ID3D11Texture2D>& pDepthStencil,
            const D3D11_DEPTH_STENCIL_VIEW_DESC& desc,
            ::wrl::ComPtr<ID3D11DepthStencilView>& pDSV)
    {
        const auto& hr = pDevice->CreateDepthStencilView(pDepthStencil.Get(), &desc, &pDSV);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create DepthStencilView!");
        }
    }
}