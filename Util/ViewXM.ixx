module;

#include <DirectXMath.h>

export module FatPound.Util.ViewXM;

import std;

export namespace fatpound::util
{
    class ViewXM final
    {
    public:
        explicit ViewXM()              = default;
        explicit ViewXM(const ViewXM&) = delete;
        explicit ViewXM(ViewXM&&)      = delete;

        auto operator = (const ViewXM&) -> ViewXM& = delete;
        auto operator = (ViewXM&&)      -> ViewXM& = delete;
        ~ViewXM() noexcept = default;


    public:
        auto GetCameraXM()     const noexcept -> ::DirectX::XMMATRIX;
        auto GetProjectionXM() const noexcept -> ::DirectX::XMMATRIX;

        void SetCameraXM(const ::DirectX::XMMATRIX& camera) noexcept;
        void SetProjectionXM(const ::DirectX::XMMATRIX& projection) noexcept;


    protected:


    private:
        ::DirectX::XMMATRIX m_camera_{};
        ::DirectX::XMMATRIX m_projection_{};
    };
}

module : private;