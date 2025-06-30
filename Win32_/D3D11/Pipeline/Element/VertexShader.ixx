module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <d3dcompiler.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.VertexShader;

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
    class VertexShader : public Bindable
    {
    public:
        explicit VertexShader(ID3D11Device* const pDevice, const std::wstring& path)
        {
            wrl::ComPtr<ID3DBlob> pBlob;

            if (FAILED(::D3DReadFileToBlob(path.c_str(), &pBlob)))
            {
                throw std::runtime_error("CANNOT read Vertex Shader to D3D Blob!");
            }

            if (const auto& hr = pDevice->CreateVertexShader(
                pBlob->GetBufferPointer(),
                pBlob->GetBufferSize(),
                nullptr,
                &m_pVertexShader_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create VertexShader!");
            }
        }
        explicit VertexShader(ID3D11Device* const pDevice, const wrl::ComPtr<ID3DBlob>& pBlob)
        {
            if (const auto& hr = pDevice->CreateVertexShader(
                pBlob->GetBufferPointer(),
                pBlob->GetBufferSize(),
                nullptr,
                &m_pVertexShader_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create VertexShader!");
            }
        }

        explicit VertexShader()                        = delete;
        explicit VertexShader(const VertexShader&)     = delete;
        explicit VertexShader(VertexShader&&) noexcept = delete;

        auto operator = (const VertexShader&)     -> VertexShader& = delete;
        auto operator = (VertexShader&&) noexcept -> VertexShader& = delete;
        virtual ~VertexShader() noexcept override final            = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->VSSetShader(m_pVertexShader_.Get(), nullptr, 0U);
        }


    protected:
        wrl::ComPtr<ID3D11VertexShader> m_pVertexShader_;


    private:
    };
}

#endif

module : private;
