module;

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)
#include <FatWin32.hpp>
#include <d3d11.h>
#include <wrl.h>
#endif

export module FatPound.Win32.D3D11.Pipeline.Element.VertexBuffer;

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class VertexBuffer final : public Bindable
    {
    public:
        template <typename T>
        explicit VertexBuffer(ID3D11Device* const pDevice, const std::vector<T>& vertices)
            :
            m_stride_(sizeof(T))
        {
            const D3D11_BUFFER_DESC bd{
                .ByteWidth           = static_cast<UINT>(m_stride_ * vertices.size()),
                .Usage               = D3D11_USAGE_DEFAULT,
                .BindFlags           = D3D11_BIND_VERTEX_BUFFER,
                .CPUAccessFlags      = 0u,
                .MiscFlags           = 0u,
                .StructureByteStride = m_stride_
            };

            const D3D11_SUBRESOURCE_DATA sd{ .pSysMem = vertices.data() };

            const auto& hr = pDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer_);

            if (FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D VertexBuffer in function: " __FUNCSIG__);
            }
        }

        explicit VertexBuffer()                        = delete;
        explicit VertexBuffer(const VertexBuffer&)     = delete;
        explicit VertexBuffer(VertexBuffer&&) noexcept = delete;

        auto operator = (const VertexBuffer&)     -> VertexBuffer& = delete;
        auto operator = (VertexBuffer&&) noexcept -> VertexBuffer& = delete;
        virtual ~VertexBuffer() noexcept final                     = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            constexpr UINT offset{};

            pImmediateContext->IASetVertexBuffers(0u, 1u, m_pVertexBuffer_.GetAddressOf(), &m_stride_, &offset);
        }


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer_;

        UINT m_stride_;


    private:
    };
}

#endif

module : private;
