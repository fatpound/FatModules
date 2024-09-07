module;

#include <FatWin32_.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.System:Sampler;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::pipeline::system
{
	void Sampler::SetDefault(const GraphicsResourcePack& gfxResPack)
	{
        SetDefault(gfxResPack.m_pDevice.Get(), gfxResPack.m_pImmediateContext.Get());
	}

    void Sampler::SetDefault(
            ID3D11Device* const pDevice,
            ID3D11DeviceContext* const pImmediateContext
        )
    {
        ::wrl::ComPtr<ID3D11SamplerState> pSamplerState_{};

        const auto& sampDesc = factory::SamplerState::CreateDESC();

        factory::SamplerState::Create(pDevice, sampDesc, pSamplerState_);

        pImmediateContext->PSSetSamplers(0u, 1u, pSamplerState_.GetAddressOf());
    }
}