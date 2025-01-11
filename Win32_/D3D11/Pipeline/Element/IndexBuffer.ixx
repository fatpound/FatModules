module;

#include <FatWin32.hpp>

#include <d3d11.h>

#include <wrl.h>

export module FatPound.Win32.D3D11.Pipeline.Element.IndexBuffer;

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
            D3D11_BUFFER_DESC bd{};
            bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.CPUAccessFlags = 0u;
            bd.MiscFlags = 0u;
            bd.ByteWidth = m_count_ * sizeof(unsigned short int);
            bd.StructureByteStride = sizeof(unsigned short int);

            D3D11_SUBRESOURCE_DATA sd{};
            sd.pSysMem = indices.data();

            const auto& hr = pDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer_);

            if (FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D IndexBuffer in function: " __FUNCSIG__);
            }
        }

        explicit IndexBuffer() = delete;
        explicit IndexBuffer(const IndexBuffer& src) = delete;
        explicit IndexBuffer(IndexBuffer&& src) = delete;

        auto operator = (const IndexBuffer& src) -> IndexBuffer& = delete;
        auto operator = (IndexBuffer&& src)      -> IndexBuffer& = delete;
        virtual ~IndexBuffer() noexcept final = default;


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

module : private;