module;

#if FAT_BUILDING_WITH_MSVC
#include <FatWin32.hpp>
#include <wrl.h>
#endif

export module FatPound.Win32.D3D11.Pipeline.Resource.Sampler;

#if FAT_BUILDING_WITH_MSVC

import <d3d11.h>;

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

namespace wrl = Microsoft::WRL;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    class Sampler final : public Bindable
    {
    public:
        explicit Sampler(ID3D11Device* const pDevice, const D3D11_SAMPLER_DESC& sDesc)
        {
            if (const auto& hr = pDevice->CreateSamplerState(&sDesc, &m_pSamplerState_); FAILED(hr))
            {
                throw std::runtime_error("Could NOT create SamplerState");
            }
        }

        explicit Sampler()                   = delete;
        explicit Sampler(const Sampler&)     = delete;
        explicit Sampler(Sampler&&) noexcept = delete;

        auto operator = (const Sampler&)     -> Sampler& = delete;
        auto operator = (Sampler&&) noexcept -> Sampler& = delete;
        virtual ~Sampler() noexcept override final       = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->PSSetSamplers(0, 1, m_pSamplerState_.GetAddressOf());
        }


    protected:


    private:
        wrl::ComPtr<ID3D11SamplerState> m_pSamplerState_;
    };
}

#endif

module : private;
