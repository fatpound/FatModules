module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Factory:SamplerState;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::factory
{
    void SamplerState::Create(
            const GraphicsResourcePack& gfxResPack,
            D3D11_SAMPLER_DESC desc,
            ::wrl::ComPtr<ID3D11SamplerState>& pSamplerState
        )
    {
        Create(gfxResPack.m_pDevice.Get(), desc, pSamplerState);
    }

    void SamplerState::Create(
            ID3D11Device* const pDevice,
            D3D11_SAMPLER_DESC desc,
            ::wrl::ComPtr<ID3D11SamplerState>& pSamplerState
        )
    {
        const auto& hr = pDevice->CreateSamplerState(&desc, &pSamplerState);

        if (FAILED(hr)) [[unlikely]]
        {
            throw std::runtime_error("Could NOT create SamplerState");
        }
    }
}