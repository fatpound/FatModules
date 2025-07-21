module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.Rasterizer;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import FatPound.Win32.WRL.Common;
#endif

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

#ifdef __INTELLISENSE__
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::win32::d3d11::pipeline
{
    class Rasterizer : public Bindable
    {
    public:
        explicit Rasterizer(ID3D11Device* const pDevice, const D3D11_RASTERIZER_DESC& rDesc)
        {
            if (FAILED(pDevice->CreateRasterizerState(&rDesc, &m_pRasterizerState_)))
            {
                throw std::runtime_error("Could NOT create RasterizerState!");
            }
        }

        explicit Rasterizer()                      = delete;
        explicit Rasterizer(const Rasterizer&)     = delete;
        explicit Rasterizer(Rasterizer&&) noexcept = delete;

        auto operator = (const Rasterizer&)     -> Rasterizer& = delete;
        auto operator = (Rasterizer&&) noexcept -> Rasterizer& = delete;
        virtual ~Rasterizer() noexcept override                = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->RSSetState(m_pRasterizerState_.Get());
        }


    protected:
        wrl::ComPtr<ID3D11RasterizerState>  m_pRasterizerState_;


    private:
    };
}

#endif

// module : private;
