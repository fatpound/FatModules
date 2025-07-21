module;

export module FatPound.Win32.D3D11.Pipeline.VertexCBuffer;

#ifdef FATLIB_BUILDING_WITH_MSVC

import <d3d11_4.h>;

import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Pipeline.CBuffer;

export namespace fatpound::win32::d3d11::pipeline
{
    template <typename T>
    class VertexCBuffer : public CBuffer<T>
    {
        using CBuffer<T>::CBuffer;

    public:
        explicit VertexCBuffer()                         = delete;
        explicit VertexCBuffer(const VertexCBuffer&)     = delete;
        explicit VertexCBuffer(VertexCBuffer&&) noexcept = delete;

        auto operator = (const VertexCBuffer&)     -> VertexCBuffer& = delete;
        auto operator = (VertexCBuffer&&) noexcept -> VertexCBuffer& = delete;
        virtual ~VertexCBuffer() noexcept override                   = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            pImmediateContext->VSSetConstantBuffers(0U, 1U, this->m_pConstantBuffer_.GetAddressOf());
        }


    protected:


    private:
    };
}

#endif

// module : private;
