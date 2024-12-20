module;

#include <FatWin32.hpp>

#include <d3d11.h>
#include <d3dcompiler.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Element.VertexShader;

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class VertexShader final : public Bindable
    {
    public:
        explicit VertexShader(ID3D11Device* const pDevice, const std::wstring& path)
        {
            ::D3DReadFileToBlob(path.c_str(), &m_pBytecodeBlob_);

            pDevice->CreateVertexShader(
                m_pBytecodeBlob_->GetBufferPointer(),
                m_pBytecodeBlob_->GetBufferSize(),
                nullptr,
                &m_pVertexShader_
            );
        }

        explicit VertexShader() = delete;
        explicit VertexShader(const VertexShader& src) = delete;
        explicit VertexShader(VertexShader&& src) = delete;

        auto operator = (const VertexShader& src) -> VertexShader& = delete;
        auto operator = (VertexShader&& src)      -> VertexShader& = delete;
        virtual ~VertexShader() noexcept final = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->VSSetShader(m_pVertexShader_.Get(), nullptr, 0u);
        }


    public:
        auto GetBytecode() const noexcept -> ID3DBlob*
        {
            return m_pBytecodeBlob_.Get();
        }


    protected:
        ::Microsoft::WRL::ComPtr<ID3DBlob>           m_pBytecodeBlob_;
        ::Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader_;


    private:
    };
}

module : private;