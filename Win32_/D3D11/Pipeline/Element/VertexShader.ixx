module;

#if FAT_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <FatWin32.hpp>
        #include <d3d11.h>
        #include <d3dcompiler.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.Element.VertexShader;

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
    class VertexShader final : public Bindable
    {
    public:
        explicit VertexShader(ID3D11Device* const pDevice, const std::wstring& path)
        {
            ::D3DReadFileToBlob(path.c_str(), &m_pBytecodeBlob_);

            if (const auto& hr = pDevice->CreateVertexShader(
                m_pBytecodeBlob_->GetBufferPointer(),
                m_pBytecodeBlob_->GetBufferSize(),
                nullptr,
                &m_pVertexShader_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D VertexShader in function: " __FUNCSIG__);
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


    public:
        auto GetBytecode() const noexcept -> ID3DBlob*
        {
            return m_pBytecodeBlob_.Get();
        }


    protected:
        wrl::ComPtr<ID3DBlob>           m_pBytecodeBlob_;
        wrl::ComPtr<ID3D11VertexShader> m_pVertexShader_;


    private:
    };
}

#endif

module : private;
