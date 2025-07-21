module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/Namespaces.hxx>

    #ifdef __INTELLISENSE__
        #include <Win32_/WinAPI.hpp>
        #include <d3d11_4.h>
    #endif

    #include <DirectXMath.h>
#endif

export module FatPound.Win32.D3D11.Pipeline.TransformCBuffer;

#ifdef FATLIB_BUILDING_WITH_MSVC

#ifndef __INTELLISENSE__
    import <d3d11_4.h>;
#endif

import FatPound.Utility.ViewXM;
import FatPound.Win32.D3D11.Pipeline.Bindable;
import FatPound.Win32.D3D11.Pipeline.VertexCBuffer;

namespace dx = DirectX;

export namespace fatpound::win32::d3d11::pipeline
{
    template <typename T>
    class TransformCBuffer : public Bindable
    {
    public:
        explicit TransformCBuffer(ID3D11Device* const pDevice, const D3D11_BUFFER_DESC& bufDesc, const T& parent, utility::ViewXM& viewXM)
            :
            m_vcbuf_(pDevice, bufDesc),
            m_parent_(parent),
            m_viewXM_(viewXM)
        {
            
        }

        explicit TransformCBuffer()                            = delete;
        explicit TransformCBuffer(const TransformCBuffer&)     = delete;
        explicit TransformCBuffer(TransformCBuffer&&) noexcept = delete;

        auto operator = (const TransformCBuffer&)     -> TransformCBuffer& = delete;
        auto operator = (TransformCBuffer&&) noexcept -> TransformCBuffer& = delete;
        virtual ~TransformCBuffer() noexcept override                      = default;


    public:
        virtual void Bind(ID3D11DeviceContext* const pImmediateContext) override
        {
            m_vcbuf_.Update(
                pImmediateContext,
                dx::XMMatrixTranspose(
                    m_parent_.GetTransformXM() *
                    m_viewXM_.GetCameraXM() *
                    m_viewXM_.GetProjectionXM()
                )
            );

            m_vcbuf_.Bind(pImmediateContext);
        }


    protected:


    private:
        VertexCBuffer<dx::XMMATRIX>   m_vcbuf_;

        const T&                      m_parent_;

        utility::ViewXM&              m_viewXM_;
    };
}

#endif

// module : private;
