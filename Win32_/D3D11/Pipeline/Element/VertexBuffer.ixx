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
    class VertexBuffer : public Bindable
    {
    public:
        explicit VertexBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const void* const pVerticesData)
            :
            m_stride_(bufDesc.StructureByteStride) // same as sizeof(T)
        {
            const D3D11_SUBRESOURCE_DATA sd
            {
                .pSysMem          = pVerticesData,
                .SysMemPitch      = {},
                .SysMemSlicePitch = {}
            };

            if (FAILED(pDevice->CreateBuffer(&bufDesc, &sd, &m_pVertexBuffer_)))
            {
                throw std::runtime_error("Could NOT create VertexBuffer!");
            }
        }

        template <typename T, std::size_t N>
        explicit VertexBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const std::array<T, N>& vertices)
            :
            VertexBuffer(pDevice, bufDesc, vertices.data())
        {

        }

        template <typename T>
        explicit VertexBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const std::vector<T>& vertices)
            :
            VertexBuffer(pDevice, bufDesc, vertices.data())
        {

        }

        explicit VertexBuffer()                        = delete;
        explicit VertexBuffer(const VertexBuffer&)     = delete;
        explicit VertexBuffer(VertexBuffer&&) noexcept = delete;

        auto operator = (const VertexBuffer&)     -> VertexBuffer& = delete;
        auto operator = (VertexBuffer&&) noexcept -> VertexBuffer& = delete;
        virtual ~VertexBuffer() noexcept override                  = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            constexpr UINT offset{};

            pImmediateContext->IASetVertexBuffers(0U, 1U, m_pVertexBuffer_.GetAddressOf(), &m_stride_, &offset);
        }


    protected:
        wrl::ComPtr<ID3D11Buffer>   m_pVertexBuffer_;
        UINT                        m_stride_;


    private:
    };
}

#endif

module : private;
