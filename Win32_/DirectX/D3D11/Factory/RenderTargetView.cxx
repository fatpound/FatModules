module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:RenderTargetView;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void RenderTargetView::Create(GraphicsResourcePack& gfxResPack)
    {
        Create(
            gfxResPack.m_pSwapChain.Get(),
            gfxResPack.m_pDevice.Get(),
            gfxResPack.m_pRTV
        );
    }

    void RenderTargetView::Create(
            IDXGISwapChain* const pSwapChain,
            ID3D11Device* const pDevice,
            ::wrl::ComPtr<ID3D11RenderTargetView>& pRenderTargetView)
    {
        ::wrl::ComPtr<ID3D11Texture2D> pBackBufferTexture{};

        HRESULT hr;

        hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &pBackBufferTexture);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT get the buffer from SwapChain!");
        }

        hr = pDevice->CreateRenderTargetView(pBackBufferTexture.Get(), nullptr, &pRenderTargetView);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create RenderTargetView!");
        }
    }
}