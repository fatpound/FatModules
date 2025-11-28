module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Shader.Sampler;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import <wrl.h>;
#endif

import FatPound.Win32.D3D11.Bindable;
import std;

export namespace fatpound::win32::d3d11::shader
{
    class Sampler : public Bindable
    {
    public:
        explicit Sampler(ID3D11Device* const pDevice, const D3D11_SAMPLER_DESC& sDesc, const UINT& startSlot = 0U)
            :
            m_start_slot_(startSlot)
        {
            if (FAILED(pDevice->CreateSamplerState(&sDesc, &m_pSamplerState_)))
            {
                throw std::runtime_error("Could NOT create SamplerState!");
            }
        }

        explicit Sampler()                   = delete;
        explicit Sampler(const Sampler&)     = delete;
        explicit Sampler(Sampler&&) noexcept = default;

        auto operator = (const Sampler&)     -> Sampler& = delete;
        auto operator = (Sampler&&) noexcept -> Sampler& = default;
        virtual ~Sampler() noexcept override             = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->PSSetSamplers(m_start_slot_, 1U, m_pSamplerState_.GetAddressOf());
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11SamplerState>   m_pSamplerState_;
        UINT                                         m_start_slot_{};


    private:
    };
}

#endif

// module : private;
