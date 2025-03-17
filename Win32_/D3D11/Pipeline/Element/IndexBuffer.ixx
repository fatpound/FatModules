module;

#if FAT_BUILD_ONLY_WITH_MSVC
#include <FatWin32.hpp>
#include <d3d11.h>
#include <wrl.h>
#endif

export module FatPound.Win32.D3D11.Pipeline.Element.IndexBuffer;

#if FAT_BUILD_ONLY_WITH_MSVC

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

export namespace fatpound::win32::d3d11::pipeline::element
{
    class IndexBuffer final : public Bindable
    {
    public:
        explicit IndexBuffer(ID3D11Device* const pDevice, const std::vector<unsigned short int>& indices)
            :
            m_count_(static_cast<UINT>(indices.size()))
        {
            const D3D11_BUFFER_DESC bd{
                .ByteWidth           = m_count_ * sizeof(unsigned short int),
                .Usage               = D3D11_USAGE_DEFAULT,
                .BindFlags           = D3D11_BIND_INDEX_BUFFER,
                .CPUAccessFlags      = 0u,
                .MiscFlags           = 0u,
                .StructureByteStride = sizeof(unsigned short int)
            };

            const D3D11_SUBRESOURCE_DATA sd{ .pSysMem = indices.data() };

            const auto& hr = pDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer_);

            if (FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D IndexBuffer in function: " __FUNCSIG__);
            }
        }

        explicit IndexBuffer()                       = delete;
        explicit IndexBuffer(const IndexBuffer&)     = delete;
        explicit IndexBuffer(IndexBuffer&&) noexcept = delete;

        auto operator = (const IndexBuffer&)     -> IndexBuffer& = delete;
        auto operator = (IndexBuffer&&) noexcept -> IndexBuffer& = delete;
        virtual ~IndexBuffer() noexcept final                    = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->IASetIndexBuffer(m_pIndexBuffer_.Get(), DXGI_FORMAT_R16_UINT, 0u);
        }


    public:
        auto GetCount() const noexcept -> UINT
        {
            return m_count_;
        }


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer_;

        UINT m_count_;


    private:
    };
}

#endif

module : private;
