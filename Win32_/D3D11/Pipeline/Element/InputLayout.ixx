module;

#if FAT_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <FatWin32.hpp>
        #include <d3d11.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.Element.InputLayout;

#if FAT_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11.h>;
    import FatPound.Win32.WRL.Common;
#endif

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

#ifdef __INTELLISENSE__
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::win32::d3d11::pipeline::element
{
    class InputLayout final : public Bindable
    {
    public:
        explicit InputLayout(ID3D11Device* const pDevice, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* const pVertexShaderBytecode)
        {
            if (const auto& hr = pDevice->CreateInputLayout(
                layout.data(),
                static_cast<UINT>(layout.size()),
                pVertexShaderBytecode->GetBufferPointer(),
                pVertexShaderBytecode->GetBufferSize(),
                &m_pInputLayout_); FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D InputLayout in function: " __FUNCSIG__);
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
        wrl::ComPtr<ID3D11InputLayout> m_pInputLayout_;


    private:
    };
}

#endif

module : private;
