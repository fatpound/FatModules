module;

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)
#include <FatWin32.hpp>
#include <d3d11.h>
#include <wrl.h>
#endif

export module FatPound.Win32.D3D11.Pipeline.Resource.CBuffer;

#if defined(_MSC_VER) and not defined(__clang__) and not defined(__GNUC__)

import FatPound.Win32.D3D11.Pipeline.Bindable;

import std;

export namespace fatpound::win32::d3d11::pipeline::resource
{
    template <typename T>
    class CBuffer : public Bindable
    {
    public:
        explicit CBuffer(ID3D11Device* const pDevice, const T& consts)
        {
            const D3D11_BUFFER_DESC cbd{
                .ByteWidth           = sizeof(T),
                .Usage               = D3D11_USAGE_DYNAMIC,
                .BindFlags           = D3D11_BIND_CONSTANT_BUFFER,
                .CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE,
                .MiscFlags           = 0u,
                .StructureByteStride = 0u
            };

            const D3D11_SUBRESOURCE_DATA csd{ .pSysMem = &consts };

            const auto& hr = pDevice->CreateBuffer(&cbd, &csd, &m_pConstantBuffer_);

            if (FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D CBuffer in function: " __FUNCSIG__);
            }
        }
        explicit CBuffer(ID3D11Device* const pDevice)
        {
            const D3D11_BUFFER_DESC cbd{
                .ByteWidth           = sizeof(T),
                .Usage               = D3D11_USAGE_DYNAMIC,
                .BindFlags           = D3D11_BIND_CONSTANT_BUFFER,
                .CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE,
                .MiscFlags           = 0u,
                .StructureByteStride = 0u
            };

            const auto& hr = pDevice->CreateBuffer(&cbd, nullptr, &m_pConstantBuffer_);

            if (FAILED(hr))
            {
                throw std::runtime_error("Could NOT Create Direct3D CBuffer in function: " __FUNCSIG__);
            }
        }

        explicit CBuffer()                   = delete;
        explicit CBuffer(const CBuffer&)     = delete;
        explicit CBuffer(CBuffer&&) noexcept = delete;

        auto operator = (const CBuffer&)     -> CBuffer& = delete;
        auto operator = (CBuffer&&) noexcept -> CBuffer& = delete;
        virtual ~CBuffer() noexcept                      = default;


    public:
        virtual void Update(ID3D11DeviceContext* const pImmediateContext, const T& consts) final
        {
            D3D11_MAPPED_SUBRESOURCE msr;

            pImmediateContext->Map(
                m_pConstantBuffer_.Get(),
                0u,
                D3D11_MAP_WRITE_DISCARD,
                0u,
                &msr
            );

            ::std::memcpy(msr.pData, &consts, sizeof(consts));

            pImmediateContext->Unmap(m_pConstantBuffer_.Get(), 0u);
        }


    protected:
        ::Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer_;


    private:
    };
}

#endif

module : private;
