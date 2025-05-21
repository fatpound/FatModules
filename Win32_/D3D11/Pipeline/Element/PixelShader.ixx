module;

#if FAT_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <FatWin32.hpp>
        #include <d3d11.h>
        #include <d3dcompiler.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.Element.PixelShader;

#if FAT_BUILDING_WITH_MSVC

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

export namespace fatpound::win32::d3d11::pipeline::element
{
    class PixelShader final : public Bindable
    {
    public:
        explicit PixelShader(ID3D11Device* const pDevice, const std::wstring& path)
        {
            wrl::ComPtr<ID3DBlob> pBlob;

            ::D3DReadFileToBlob(path.c_str(), &pBlob);

            if (const auto& hr = pDevice->CreatePixelShader(
                pBlob->GetBufferPointer(),
                pBlob->GetBufferSize(),
                nullptr,
                &m_pPixelShader_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D PixelShader in function: " __FUNCSIG__);
            }
        }

        explicit PixelShader()                       = delete;
        explicit PixelShader(const PixelShader&)     = delete;
        explicit PixelShader(PixelShader&&) noexcept = delete;

        auto operator = (const PixelShader&)     -> PixelShader& = delete;
        auto operator = (PixelShader&&) noexcept -> PixelShader& = delete;
        virtual ~PixelShader() noexcept override final           = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->PSSetShader(m_pPixelShader_.Get(), nullptr, 0U);
        }


    protected:
        wrl::ComPtr<ID3D11PixelShader> m_pPixelShader_;


    private:
    };
}

#endif

module : private;
