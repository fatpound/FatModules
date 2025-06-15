module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.VertexBuffer;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11.h>;
    import FatPound.Win32.WRL.Common;
#endif

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

#ifdef __INTELLISENSE__
    namespace wrl = Microsoft::WRL;
#endif

export namespace fatpound::win32::d3d11::pipeline
{
    class VertexBuffer final : public Bindable
    {
    public:
        template <typename T, std::size_t N>
        explicit VertexBuffer(ID3D11Device* const pDevice, const std::array<T, N>& vertices)
            :
            m_stride_(sizeof(T))
        {
            const D3D11_BUFFER_DESC bd
            {
                .ByteWidth           = static_cast<UINT>(m_stride_ * vertices.size()),
                .Usage               = D3D11_USAGE_DEFAULT,
                .BindFlags           = D3D11_BIND_VERTEX_BUFFER,
                .CPUAccessFlags      = 0U,
                .MiscFlags           = 0U,
                .StructureByteStride = m_stride_
            };

            const D3D11_SUBRESOURCE_DATA sd
            {
                .pSysMem = vertices.data()
            };

            if (const auto& hr = pDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D VertexBuffer in function: " __FUNCSIG__);
            }
        }
        template <typename T>
        explicit VertexBuffer(ID3D11Device* const pDevice, const std::vector<T>& vertices)
            :
            m_stride_(sizeof(T))
        {
            const D3D11_BUFFER_DESC bd{
                .ByteWidth           = static_cast<UINT>(m_stride_ * vertices.size()),
                .Usage               = D3D11_USAGE_DEFAULT,
                .BindFlags           = D3D11_BIND_VERTEX_BUFFER,
                .CPUAccessFlags      = 0U,
                .MiscFlags           = 0U,
                .StructureByteStride = m_stride_
            };

            const D3D11_SUBRESOURCE_DATA sd
            {
                .pSysMem = vertices.data()
            };

            if (const auto& hr = pDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D VertexBuffer in function: " __FUNCSIG__);
            }
        }

        explicit VertexBuffer()                        = delete;
        explicit VertexBuffer(const VertexBuffer&)     = delete;
        explicit VertexBuffer(VertexBuffer&&) noexcept = delete;

        auto operator = (const VertexBuffer&)     -> VertexBuffer& = delete;
        auto operator = (VertexBuffer&&) noexcept -> VertexBuffer& = delete;
        virtual ~VertexBuffer() noexcept override final            = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            constexpr UINT offset{};

            pImmediateContext->IASetVertexBuffers(0U, 1U, m_pVertexBuffer_.GetAddressOf(), &m_stride_, &offset);
        }


    protected:
        wrl::ComPtr<ID3D11Buffer> m_pVertexBuffer_;

        UINT m_stride_;


    private:
    };
}

#endif

module : private;
