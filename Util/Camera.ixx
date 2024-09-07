module;

#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

export module FatPound.Util.Camera;

import FatPound.Win32.IO;

import std;

export namespace fatpound::util
{
    class Camera final
    {
    public:
        explicit Camera(const float min_depth, const float max_depth, NAMESPACE_IO::Mouse& mouse, const NAMESPACE_IO::Keyboard& keyboard) noexcept;

        explicit Camera() = delete;
        explicit Camera(const Camera& src) = delete;
        explicit Camera(Camera&& src) = delete;

        auto operator = (const Camera& src) -> Camera& = delete;
        auto operator = (Camera&& src)      -> Camera& = delete;
        ~Camera() noexcept = default;


    public:
        auto GetMatrix() const noexcept -> ::DirectX::XMMATRIX;

        auto GetR() const noexcept -> float;
        auto GetX() const noexcept -> float;
        auto GetY() const noexcept -> float;
        auto GetZ() const noexcept -> float;

        void SetR(float r) noexcept;
        void SetX(float x) noexcept;
        void SetY(float y) noexcept;
        void SetZ(float z) noexcept;

        void Update() noexcept;
        void Reset() noexcept;


    protected:


    private:
        class Controller_ final
        {
        public:
            explicit Controller_(Camera& camera, NAMESPACE_IO::Mouse& mouse, const NAMESPACE_IO::Keyboard& keyboard) noexcept;

            explicit Controller_() = delete;
            explicit Controller_(const Controller_& src) = delete;
            explicit Controller_(Controller_&& src) = delete;

            Controller_& operator = (const Controller_& src) = delete;
            Controller_& operator = (Controller_&& src) = delete;
            ~Controller_() noexcept = default;

        public:
            void Update() noexcept;

        protected:

        private:
            ::DirectX::XMFLOAT2 last_position_{};

            Camera& camera_;

            NAMESPACE_IO::Mouse& mouse_;
            const NAMESPACE_IO::Keyboard& keyboard_;

            bool engaged_ = false;

            static constexpr float s_zoomIncrement_ = 0.1f;
        };


    private:
        const float min_depth_;
        const float max_depth_;

        float r_  = 0.1f;
        float x_  = 0.0f;
        float y_  = 0.0f;
        float z_  = 0.0f;

        std::unique_ptr<Controller_> m_pController_;
    };
}