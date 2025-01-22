module;

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource.Sampler;

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <bool ForFramework>
    class Sampler final : public Bindable
    {
    public:
        Sampler(ID3D11Device* const pDevice)
        {
            D3D11_SAMPLER_DESC sDesc{};

            if constexpr (ForFramework)
            {
                sDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
                sDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
                sDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
                sDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
                sDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
            }
            else
            {
                sDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
                sDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
                sDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
                sDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
            }

            sDesc.MinLOD = 0.0f;
            sDesc.MaxLOD = D3D11_FLOAT32_MAX;

            const auto& hr = pDevice->CreateSamplerState(&sDesc, &m_pSamplerState_);

            if (FAILED(hr)) [[unlikely]]
            {
                throw std::runtime_error("Could NOT create SamplerState");
            }
        }


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->PSSetSamplers(0, 1, m_pSamplerState_.GetAddressOf());
        }


    protected:


    private:
        ::Microsoft::WRL::ComPtr<ID3D11SamplerState> m_pSamplerState_;
    };
}

module : private;