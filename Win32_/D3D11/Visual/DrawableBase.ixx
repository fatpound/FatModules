module;

#if FAT_BUILDING_WITH_MSVC

#include <FatNamespaces.hpp>

#include <cassert>

#endif

export module FatPound.Win32.D3D11.Visual.DrawableBase;

#if FAT_BUILDING_WITH_MSVC

import FatPound.Win32.D3D11.Visual.Drawable;
import FatPound.Win32.D3D11.Pipeline;

import std;

export namespace fatpound::win32::d3d11::visual
{
    template <typename T>
    class DrawableBase : public Drawable
    {
    public:
        explicit DrawableBase()                        = default;
        explicit DrawableBase(const DrawableBase&)     = delete;
        explicit DrawableBase(DrawableBase&&) noexcept = delete;

        auto operator = (const DrawableBase&)     -> DrawableBase& = delete;
        auto operator = (DrawableBase&&) noexcept -> DrawableBase& = delete;
        virtual ~DrawableBase() noexcept                           = default;


    protected:
        virtual void AddStaticIndexBuffer_(std::unique_ptr<FATSPACE_PIPELINE_ELEMENT::IndexBuffer> idxbuf) noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" && m_pCIndexBuffer_ == nullptr);

            m_pCIndexBuffer_ = idxbuf.get();

            tl_bindable_vec_.push_back(std::move<>(idxbuf));
        }
        virtual void SetIndexFromStatic_() noexcept(IN_RELEASE) final
        {
            assert("Attempting to add index buffer a second time" && m_pCIndexBuffer_ == nullptr);

            for (const auto& b : GetStaticBinds_())
            {
                const auto ptr = dynamic_cast<FATSPACE_PIPELINE_ELEMENT::IndexBuffer*>(b.get());

                if (ptr not_eq nullptr)
                {
                    m_pCIndexBuffer_ = ptr;

                    return;
                }
            }

            assert("Failed to find index buffer in static binds" && m_pCIndexBuffer_ not_eq nullptr);
        }


    private:
        virtual auto GetStaticBinds_() const noexcept(IN_RELEASE) -> const BindableVec_t& override
        {
            return tl_bindable_vec_;
        }


    private:
        inline static thread_local std::vector<BindablePtr_t> tl_bindable_vec_;
    };
}

#endif

module : private;
