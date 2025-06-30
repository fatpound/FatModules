module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.InputLayout;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11.h>;
    import FatPound.Win32.WRL.Common;
#endif

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

#ifdef __INTELLISENSE__
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::win32::d3d11::pipeline
{
    class InputLayout : public Bindable
    {
    public:
        explicit InputLayout(ID3D11Device* const pDevice, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, const wrl::ComPtr<ID3DBlob>& pVertexShaderBytecode)
        {
            if (const auto& hr = pDevice->CreateInputLayout(
                layout.data(),
                static_cast<UINT>(layout.size()),
                pVertexShaderBytecode->GetBufferPointer(),
                pVertexShaderBytecode->GetBufferSize(),
                &m_pInputLayout_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create InputLayout!");
            }
        }

        explicit InputLayout()                       = delete;
        explicit InputLayout(const InputLayout&)     = delete;
        explicit InputLayout(InputLayout&&) noexcept = delete;

        auto operator = (const InputLayout&)     -> InputLayout& = delete;
        auto operator = (InputLayout&&) noexcept -> InputLayout& = delete;
        virtual ~InputLayout() noexcept override final           = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->IASetInputLayout(m_pInputLayout_.Get());
        }


    protected:
        wrl::ComPtr<ID3D11InputLayout>  m_pInputLayout_;


    private:
    };
}

#endif

module : private;
