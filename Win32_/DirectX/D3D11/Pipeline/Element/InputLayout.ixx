module;

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Element.InputLayout;

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class InputLayout final : public Bindable
    {
    public:
        explicit InputLayout(ID3D11Device* const pDevice, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, ID3DBlob* const pVertexShaderBytecode);

        explicit InputLayout() = delete;
        explicit InputLayout(const InputLayout& src) = delete;
        explicit InputLayout(InputLayout&& src) = delete;

        auto operator = (const InputLayout& src) -> InputLayout& = delete;
        auto operator = (InputLayout&& src)      -> InputLayout& = delete;
        virtual ~InputLayout() noexcept final = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final;


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout_;


    private:
    };
}