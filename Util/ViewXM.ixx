module;

#if defined(_MSC_VER)
#include <DirectXMath.h>
#endif

export module FatPound.Util.ViewXM;

#if defined(_MSC_VER)

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
        ~ViewXM() noexcept                         = default;


    public:
        auto GetCameraXM     () const noexcept -> ::DirectX::XMMATRIX
        {
            return m_camera_;
        }
        auto GetProjectionXM () const noexcept -> ::DirectX::XMMATRIX
        {
            return m_projection_;
        }

        void SetCameraXM     (const ::DirectX::XMMATRIX& camera)     noexcept
        {
            m_camera_ = camera;
        }
        void SetProjectionXM (const ::DirectX::XMMATRIX& projection) noexcept
        {
            m_projection_ = projection;
        }


    protected:


    private:
        ::DirectX::XMMATRIX m_camera_{};
        ::DirectX::XMMATRIX m_projection_{};
    };
}

#endif

module : private;
