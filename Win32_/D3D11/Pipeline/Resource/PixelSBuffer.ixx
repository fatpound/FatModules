module;

export module FatPound.Win32.D3D11.Pipeline.Resource.PixelSBuffer;

#if FAT_BUILDING_WITH_MSVC

import <d3d11.h>;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Pipeline.Resource.SBuffer;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class PixelSBuffer final : public SBuffer<T>
    {
        using SBuffer<T>::SBuffer;

    public:
        explicit PixelSBuffer()                        = delete;
        explicit PixelSBuffer(const PixelSBuffer&)     = delete;
        explicit PixelSBuffer(PixelSBuffer&&) noexcept = delete;

        auto operator = (const PixelSBuffer&)     -> PixelSBuffer& = delete;
        auto operator = (PixelSBuffer&&) noexcept -> PixelSBuffer& = delete;
        virtual ~PixelSBuffer() noexcept override final            = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->PSSetShaderResources(0U, 1U, this->m_pShaderResourceView_.GetAddressOf());
        }


    protected:


    private:
    };
}

#endif

module : private;
