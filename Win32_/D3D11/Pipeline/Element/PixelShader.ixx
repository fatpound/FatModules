module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <d3dcompiler.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.PixelShader;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11.h>;
    import <d3dcompiler.h>;
    import FatPound.Win32.WRL.Common;
#endif

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

#ifdef __INTELLISENSE__
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::win32::d3d11::pipeline
{
    class PixelShader : public Bindable
    {
    public:
        explicit PixelShader(ID3D11Device* const pDevice, const std::wstring& path)
        {
            wrl::ComPtr<ID3DBlob> pBlob;

            if (FAILED(::D3DReadFileToBlob(path.c_str(), &pBlob)))
            {
                throw std::runtime_error("CANNOT read Pixel Shader to D3D Blob!");
            }

            if (FAILED(pDevice->CreatePixelShader(
                pBlob->GetBufferPointer(),
                pBlob->GetBufferSize(),
                nullptr,
                &m_pPixelShader_)))
            {
                throw std::runtime_error("Could NOT create PixelShader!");
            }
        }
        explicit PixelShader(ID3D11Device* const pDevice, const wrl::ComPtr<ID3DBlob>& pBlob)
        {
            if (FAILED(pDevice->CreatePixelShader(
                pBlob->GetBufferPointer(),
                pBlob->GetBufferSize(),
                nullptr,
                &m_pPixelShader_)))
            {
                throw std::runtime_error("Could NOT create PixelShader!");
            }
        }

        explicit PixelShader()                       = delete;
        explicit PixelShader(const PixelShader&)     = delete;
        explicit PixelShader(PixelShader&&) noexcept = delete;

        auto operator = (const PixelShader&)     -> PixelShader& = delete;
        auto operator = (PixelShader&&) noexcept -> PixelShader& = delete;
        virtual ~PixelShader() noexcept override                 = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->PSSetShader(m_pPixelShader_.Get(), nullptr, 0U);
        }


    protected:
        wrl::ComPtr<ID3D11PixelShader>  m_pPixelShader_;


    private:
    };
}

#endif

module : private;
