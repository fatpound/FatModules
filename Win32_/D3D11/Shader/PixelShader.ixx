module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
        #include <d3d11_4.h>
        #include <d3dcompiler.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Shader.PixelShader;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import <d3dcompiler.h>;
    import <wrl.h>;
#endif

import FatPound.Win32.D3D11.Bindable;

import std;

export namespace fatpound::win32::d3d11::shader
{
    class PixelShader : public Bindable
    {
    public:
        explicit PixelShader(ID3D11Device* const pDevice, const std::wstring& path)
        {
            Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

            if (FAILED(D3DReadFileToBlob(path.c_str(), &pBlob)))
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
        explicit PixelShader(ID3D11Device* const pDevice, const Microsoft::WRL::ComPtr<ID3DBlob>& pBlob)
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
        explicit PixelShader(PixelShader&&) noexcept = default;

        auto operator = (const PixelShader&)     -> PixelShader& = delete;
        auto operator = (PixelShader&&) noexcept -> PixelShader& = default;
        virtual ~PixelShader() noexcept override                 = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->PSSetShader(m_pPixelShader_.Get(), nullptr, 0U);
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11PixelShader>  m_pPixelShader_;


    private:
    };
}

#endif

// module : private;
