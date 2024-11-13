module;

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

module FatPound.Win32.D3D11.Pipeline.System:Sampler;

namespace wrl = Microsoft::WRL;

namespace fatpound::win32::d3d11::pipeline::system
{
    void Sampler::SetState_FatDefault(
            ID3D11Device* const pDevice,
            ID3D11DeviceContext* const pImmediateContext)
    {
        ::wrl::ComPtr<ID3D11SamplerState> pSamplerState{};

        {
            const auto& sampDesc = factory::SamplerState::CreateDESC();
            factory::SamplerState::Create(pDevice, sampDesc, pSamplerState);
        }

        pImmediateContext->PSSetSamplers(0u, 1u, pSamplerState.GetAddressOf());
    }
}