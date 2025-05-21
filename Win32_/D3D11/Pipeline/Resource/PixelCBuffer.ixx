module;

#if FAT_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <FatWin32.hpp>
        #include <d3d11.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.Resource.PixelCBuffer;

#if FAT_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11.h>;
#endif

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Pipeline.Resource.CBuffer;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class PixelCBuffer final : public CBuffer<T>
    {
        using CBuffer<T>::CBuffer;

    public:
        explicit PixelCBuffer()                        = delete;
        explicit PixelCBuffer(const PixelCBuffer&)     = delete;
        explicit PixelCBuffer(PixelCBuffer&&) noexcept = delete;

        auto operator = (const PixelCBuffer&)     -> PixelCBuffer& = delete;
        auto operator = (PixelCBuffer&&) noexcept -> PixelCBuffer& = delete;
        virtual ~PixelCBuffer() noexcept override final            = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->PSSetConstantBuffers(0U, 1U, this->m_pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}

#endif

module : private;
