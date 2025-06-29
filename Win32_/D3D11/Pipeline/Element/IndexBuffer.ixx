module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.IndexBuffer;

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
    class IndexBuffer final : public Bindable
    {
    public:
        template <std::integral T>
        explicit IndexBuffer(ID3D11Device* const pDevice, const std::vector<T>& indices)
            :
            m_count_(static_cast<UINT>(indices.size()))
        {
            const D3D11_BUFFER_DESC bd
            {
                .ByteWidth           = m_count_ * sizeof(T),
                .Usage               = D3D11_USAGE_DEFAULT,
                .BindFlags           = D3D11_BIND_INDEX_BUFFER,
                .CPUAccessFlags      = 0U,
                .MiscFlags           = 0U,
                .StructureByteStride = sizeof(T)
            };

            const D3D11_SUBRESOURCE_DATA sd
            {
                .pSysMem          = indices.data(),
                .SysMemPitch      = {},
                .SysMemSlicePitch = {}
            };

            if (const auto& hr = pDevice->CreateBuffer(&bd, &sd, &m_pIndexBuffer_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create IndexBuffer!");
            }
        }

        explicit IndexBuffer()                       = delete;
        explicit IndexBuffer(const IndexBuffer&)     = delete;
        explicit IndexBuffer(IndexBuffer&&) noexcept = delete;

        auto operator = (const IndexBuffer&)     -> IndexBuffer& = delete;
        auto operator = (IndexBuffer&&) noexcept -> IndexBuffer& = delete;
        virtual ~IndexBuffer() noexcept override final           = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override final
        {
            pImmediateContext->IASetIndexBuffer(m_pIndexBuffer_.Get(), DXGI_FORMAT_R32_UINT, 0U);
        }


    public:
        auto GetCount() const noexcept -> UINT
        {
            return m_count_;
        }


    protected:
        wrl::ComPtr<ID3D11Buffer>   m_pIndexBuffer_;
        UINT                        m_count_;


    private:
    };
}

#endif

module : private;
