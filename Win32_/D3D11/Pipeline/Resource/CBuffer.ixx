module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Pipeline.CBuffer;

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
    template <typename T>
    class CBuffer : public Bindable
    {
    public:
        explicit CBuffer(ID3D11Device* const pDevice, const T& consts)
        {
            const D3D11_BUFFER_DESC bd
            {
                .ByteWidth           = sizeof(T),
                .Usage               = D3D11_USAGE_DYNAMIC,
                .BindFlags           = D3D11_BIND_CONSTANT_BUFFER,
                .CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE,
                .MiscFlags           = 0U,
                .StructureByteStride = 0U
            };

            const D3D11_SUBRESOURCE_DATA sd
            {
                .pSysMem          = &consts,
                .SysMemPitch      = {},
                .SysMemSlicePitch = {}
            };

            if (const auto& hr = pDevice->CreateBuffer(&bd, &sd, &m_pConstantBuffer_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create CBuffer!");
            }
        }
        explicit CBuffer(ID3D11Device* const pDevice)
        {
            const D3D11_BUFFER_DESC bd
            {
                .ByteWidth           = sizeof(T),
                .Usage               = D3D11_USAGE_DYNAMIC,
                .BindFlags           = D3D11_BIND_CONSTANT_BUFFER,
                .CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE,
                .MiscFlags           = 0U,
                .StructureByteStride = 0U
            };

            if (const auto& hr = pDevice->CreateBuffer(&bd, nullptr, &m_pConstantBuffer_);
                FAILED(hr))
            {
                throw std::runtime_error("Could NOT create CBuffer!");
            }
        }

        explicit CBuffer()                   = delete;
        explicit CBuffer(const CBuffer&)     = delete;
        explicit CBuffer(CBuffer&&) noexcept = delete;

        auto operator = (const CBuffer&)     -> CBuffer& = delete;
        auto operator = (CBuffer&&) noexcept -> CBuffer& = delete;
        virtual ~CBuffer() noexcept override             = default;


    public:
        virtual void Update(ID3D11DeviceContext* const pImmediateContext, const T& consts) final
        {
            {
                D3D11_MAPPED_SUBRESOURCE msr;

                pImmediateContext->Map(
                    m_pConstantBuffer_.Get(),
                    0U,
                    D3D11_MAP_WRITE_DISCARD,
                    0U,
                    &msr
                );

                std::memcpy(msr.pData, &consts, sizeof(consts));
            }

            pImmediateContext->Unmap(m_pConstantBuffer_.Get(), 0U);
        }


    protected:
        wrl::ComPtr<ID3D11Buffer> m_pConstantBuffer_;


    private:
    };
}

#endif

module : private;
