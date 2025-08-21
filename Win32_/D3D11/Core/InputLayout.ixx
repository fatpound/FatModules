module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Core.InputLayout;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import <wrl.h>;
#endif

import FatPound.Win32.D3D11.Bindable;

import std;

export namespace fatpound::win32::d3d11::core
{
    class InputLayout : public Bindable
    {
    public:
        explicit InputLayout(ID3D11Device* const pDevice, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, const Microsoft::WRL::ComPtr<ID3DBlob>& pVertexShaderBytecode)
        {
            if (FAILED(pDevice->CreateInputLayout(
                layout.data(),
                static_cast<UINT>(layout.size()),
                pVertexShaderBytecode->GetBufferPointer(),
                pVertexShaderBytecode->GetBufferSize(),
                &m_pInputLayout_)))
            {
                throw std::runtime_error("Could NOT create InputLayout!");
            }
        }

        explicit InputLayout()                       = delete;
        explicit InputLayout(const InputLayout&)     = delete;
        explicit InputLayout(InputLayout&&) noexcept = default;

        auto operator = (const InputLayout&)     -> InputLayout& = delete;
        auto operator = (InputLayout&&) noexcept -> InputLayout& = default;
        virtual ~InputLayout() noexcept override                 = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->IASetInputLayout(m_pInputLayout_.Get());
        }


    protected:
        Microsoft::WRL::ComPtr<ID3D11InputLayout>  m_pInputLayout_;


    private:
    };
}

#endif

// module : private;
