module;

#include <FatNamespaces.hpp>

#include <DirectXMath.h>

#include <d3d11.h>

export module FatPound.Win32.D3D11.Visual.Drawable;

import FatPound.Win32.D3D11.Pipeline;

import std;

export namespace fatpound::win32::d3d11::visual
{
    class Drawable
    {
    public:
        using bind_vec_t = std::vector<std::unique_ptr<FATSPACE_PIPELINE::Bindable>>;


    public:
        explicit Drawable() = default;
        explicit Drawable(const Drawable& src) = delete;
        explicit Drawable(Drawable&& src) = delete;

        auto operator = (const Drawable& src) -> Drawable& = delete;
        auto operator = (Drawable&& src)      -> Drawable& = delete;
        virtual ~Drawable() noexcept = default;


    public:
        virtual auto GetTransformXM() const noexcept -> ::DirectX::XMMATRIX = 0;

        virtual void Update(const float delta_time) noexcept = 0;

        virtual void Draw(ID3D11DeviceContext* const pImmediateContext) const final;

        
    protected:
        virtual void AddBind_(std::unique_ptr<FATSPACE_PIPELINE::Bindable> bind) noexcept(IN_RELEASE) final;
        virtual void AddIndexBuffer_(std::unique_ptr<FATSPACE_PIPELINE_ELEMENT::IndexBuffer> idxbuf) noexcept(IN_RELEASE) final;


    protected:
        const FATSPACE_PIPELINE_ELEMENT::IndexBuffer* m_pCIndexBuffer_{};


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const bind_vec_t& = 0;


    private:
        bind_vec_t m_binds_;
    };
}