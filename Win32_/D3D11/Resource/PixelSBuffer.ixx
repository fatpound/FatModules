module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/FatWin.hpp>
        #include <d3d11_4.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Resource.PixelSBuffer;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
#endif

import FatPound.Win32.D3D11.Bindable;
import FatPound.Win32.D3D11.Resource.SBuffer;

export namespace fatpound::win32::d3d11::resource
{
    template <typename T>
    class PixelSBuffer : public SBuffer<T>
    {
        using SBuffer<T>::SBuffer;

    public:
        explicit PixelSBuffer()                        = delete;
        explicit PixelSBuffer(const PixelSBuffer&)     = delete;
        explicit PixelSBuffer(PixelSBuffer&&) noexcept = default;

        auto operator = (const PixelSBuffer&)     -> PixelSBuffer& = delete;
        auto operator = (PixelSBuffer&&) noexcept -> PixelSBuffer& = default;
        virtual ~PixelSBuffer() noexcept override                  = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->PSSetShaderResources(0U, 1U, this->m_pShaderResourceView_.GetAddressOf());
        }


    protected:


    private:
    };
}

#endif

// module : private;
