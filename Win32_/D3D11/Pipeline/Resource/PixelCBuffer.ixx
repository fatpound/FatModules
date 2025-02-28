module;

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Resource.PixelCBuffer;

export import FatPound.Win32.D3D11.Pipeline.Resource.CBuffer;

import FatPound.Win32.D3D11.Pipeline.Bindable;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class PixelCBuffer final : public CBuffer<T>
    {
        using CBuffer<T>::CBuffer;

    public:
        explicit PixelCBuffer()                    = delete;
        explicit PixelCBuffer(const PixelCBuffer&) = delete;
        explicit PixelCBuffer(PixelCBuffer&&)      = delete;

        auto operator = (const PixelCBuffer&) -> PixelCBuffer& = delete;
        auto operator = (PixelCBuffer&&)      -> PixelCBuffer& = delete;
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

module : private;