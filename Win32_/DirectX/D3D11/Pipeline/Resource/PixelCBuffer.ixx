module;

#include <FatWin32_Settings.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource:PixelCBuffer;

export import :CBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class PixelCBuffer final : public CBuffer<T>
    {
        using CBuffer<T>::CBuffer;

    public:
        explicit PixelCBuffer() = delete;
        explicit PixelCBuffer(const PixelCBuffer& src) = delete;
        explicit PixelCBuffer(PixelCBuffer&& src) = delete;

        auto operator = (const PixelCBuffer& src) -> PixelCBuffer& = delete;
        auto operator = (PixelCBuffer&& src)      -> PixelCBuffer& = delete;
        virtual ~PixelCBuffer() noexcept final = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->PSSetConstantBuffers(0u, 1u, this->m_pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}