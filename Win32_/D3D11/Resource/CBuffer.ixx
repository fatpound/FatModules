module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #ifdef __INTELLISENSE__
        #include <Win32_/Win32.hpp>
        #include <d3d11_4.h>
        #include <wrl.h>
    #endif
#endif

export module FatPound.Win32.D3D11.Resource.CBuffer;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
    import <wrl.h>;
#endif

import FatPound.Win32.D3D11.Bindable;

import std;

export namespace fatpound::win32::d3d11::resource
{
    template <typename T>
    class CBuffer : public Bindable
    {
    public:
        explicit CBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const T& consts)
        {
            const D3D11_SUBRESOURCE_DATA sd
            {
                .pSysMem          = &consts,
                .SysMemPitch      = {},
                .SysMemSlicePitch = {}
            };

            if (FAILED(pDevice->CreateBuffer(&bufDesc, &sd, &m_pConstantBuffer_)))
            {
                throw std::runtime_error("Could NOT create CBuffer!");
            }
        }
        explicit CBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc)
        {
            if (FAILED(pDevice->CreateBuffer(&bufDesc, nullptr, &m_pConstantBuffer_)))
            {
                throw std::runtime_error("Could NOT create CBuffer!");
            }
        }

        explicit CBuffer()                   = delete;
        explicit CBuffer(const CBuffer&)     = delete;
        explicit CBuffer(CBuffer&&) noexcept = default;

        auto operator = (const CBuffer&)     -> CBuffer& = delete;
        auto operator = (CBuffer&&) noexcept -> CBuffer& = default;
        virtual ~CBuffer() noexcept override             = default;


    public:
        virtual void Update(ID3D11DeviceContext* const pImmediateContext, const T& consts)
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
        Microsoft::WRL::ComPtr<ID3D11Buffer>  m_pConstantBuffer_;


    private:
    };
}

#endif

// module : private;
