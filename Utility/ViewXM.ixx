module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <DirectXMath.h>
#endif

export module FatPound.Utility.ViewXM;

#ifdef FATLIB_BUILDING_WITH_MSVC

export namespace fatpound::utility
{
    /// @brief A non-copyable, non-movable class that manages camera and projection matrices using DirectX's XMMATRIX type
    ///
    class [[nodiscard]] ViewXM
    {
    public:
        explicit ViewXM()              = default;
        explicit ViewXM(const ViewXM&) = delete;
        explicit ViewXM(ViewXM&&)      = delete;

        auto operator = (const ViewXM&) -> ViewXM& = delete;
        auto operator = (ViewXM&&)      -> ViewXM& = delete;
        ~ViewXM() noexcept                         = default;


    public:
        [[nodiscard]] auto GetCameraXM     () const noexcept -> DirectX::XMMATRIX
        {
            return m_camera_;
        }
        [[nodiscard]] auto GetProjectionXM () const noexcept -> DirectX::XMMATRIX
        {
            return m_projection_;
        }

        void SetCameraXM     (const DirectX::XMMATRIX& camera)     noexcept
        {
            m_camera_ = camera;
        }
        void SetProjectionXM (const DirectX::XMMATRIX& projection) noexcept
        {
            m_projection_ = projection;
        }


    protected:


    private:
        DirectX::XMMATRIX   m_camera_{};
        DirectX::XMMATRIX   m_projection_{};
    };
}

#endif

// module : private;
