module;

#ifdef _MSC_VER
    #include <DirectXMath.h>
#endif

export module FatPound.Utility.ViewXM;

#ifdef _MSC_VER

namespace dx = DirectX;

export namespace fatpound::utility
{
    /// @brief A non-copyable, non-movable class that manages camera and projection matrices using DirectX's XMMATRIX type
    ///
    class [[nodiscard]] ViewXM final
    {
    public:
        explicit ViewXM()              = default;
        explicit ViewXM(const ViewXM&) = delete;
        explicit ViewXM(ViewXM&&)      = delete;

        auto operator = (const ViewXM&) -> ViewXM& = delete;
        auto operator = (ViewXM&&)      -> ViewXM& = delete;
        ~ViewXM() noexcept                         = default;


    public:
        [[nodiscard]] auto GetCameraXM     () const noexcept -> dx::XMMATRIX
        {
            return m_camera_;
        }
        [[nodiscard]] auto GetProjectionXM () const noexcept -> dx::XMMATRIX
        {
            return m_projection_;
        }

        void SetCameraXM     (const dx::XMMATRIX& camera)     noexcept
        {
            m_camera_ = camera;
        }
        void SetProjectionXM (const dx::XMMATRIX& projection) noexcept
        {
            m_projection_ = projection;
        }


    protected:


    private:
        dx::XMMATRIX m_camera_{};
        dx::XMMATRIX m_projection_{};
    };
}

#endif

module : private;
