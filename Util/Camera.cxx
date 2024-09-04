module;

#include <FatWin32_Namespaces.hpp>

#include <DirectXMath.h>

module FatPound.Util.Camera;

namespace dx = DirectX;

namespace fatpound::util
{
    // Camera

    Camera::Camera(const float min_depth, const float max_depth, NAMESPACE_IO::Mouse& mouse, const NAMESPACE_IO::Keyboard& keyboard) noexcept
        :
        min_depth_(min_depth),
        max_depth_(max_depth)
    {
        m_pController_ = std::make_unique<Controller_>(*this, mouse, keyboard);
    }

    auto Camera::GetMatrix() const noexcept -> ::dx::XMMATRIX
    {
        const auto& look =
            ::dx::XMMatrixTranslation(x_, y_, z_) *
            ::dx::XMMatrixLookAtLH(
                ::dx::XMVectorSet(0.0f, 0.0f, -r_, 0.0f),        // position to go n look from
                ::dx::XMVectorSet(0.0f, 0.0f, max_depth_, 0.0f), // position to go n look at
                ::dx::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)        // y should be pointing towards up
        );

        return look;
    }

    float Camera::GetR() const noexcept
    {
        return r_;
    }
    float Camera::GetX() const noexcept
    {
        return x_;
    }
    float Camera::GetY() const noexcept
    {
        return y_;
    }
    float Camera::GetZ() const noexcept
    {
        return z_;
    }

    void Camera::SetR(float r) noexcept
    {
        r_ = r;
    }
    void Camera::SetX(float x) noexcept
    {
        x_ = x;
    }
    void Camera::SetY(float y) noexcept
    {
        y_ = y;
    }
    void Camera::SetZ(float z) noexcept
    {
        z_ = z;
    }

    void Camera::Update() noexcept
    {
        m_pController_->Update();
    }
    void Camera::Reset() noexcept
    {
        static constexpr auto axis_reset_val = 0.0f;

        r_ = 0.1f;

        x_ = axis_reset_val;
        y_ = axis_reset_val;
        z_ = axis_reset_val;
    }


    // Camera::Controller_

    Camera::Controller_::Controller_(Camera& camera, NAMESPACE_IO::Mouse& mouse, const NAMESPACE_IO::Keyboard& keyboard) noexcept
        :
        camera_(camera),
        mouse_(mouse),
        keyboard_(keyboard)
    {

    }

    void Camera::Controller_::Update() noexcept
    {
        if (keyboard_.KeyIsPressed('R'))
        {
            camera_.Reset();
        }

        while (not mouse_.EventBufferIsEmpty())
        {
            const auto& mouse_event = mouse_.ReadFromBuffer();

            switch (mouse_event.GetType())
            {
            case NAMESPACE_IO::Mouse::Event::Type::LPress:
            {
                engaged_ = true;

                const auto& pos = mouse_event.GetPos();

                last_position_ = ::DirectX::XMFLOAT2{ static_cast<float>(pos.first), static_cast<float>(pos.second) };
            }
            break;

            case NAMESPACE_IO::Mouse::Event::Type::LRelease:
                engaged_ = false;
                break;

            case NAMESPACE_IO::Mouse::Event::Type::WheelUp:
                camera_.SetR(camera_.GetR() - s_zoomIncrement_ * 5.0f);
                break;

            case NAMESPACE_IO::Mouse::Event::Type::WheelDown:
                camera_.SetR(camera_.GetR() + s_zoomIncrement_ * 5.0f);
                break;

            default:
                break;
            }
        }

        if (engaged_)
        {
            const auto& pos = mouse_.GetPos();

            const auto& lastPositionVec = ::dx::XMLoadFloat2(&last_position_);
            const auto& currentPosition = ::dx::XMFLOAT2{ static_cast<float>(pos.first), static_cast<float>(pos.second) };

            const auto& currentPositionVec = ::dx::XMLoadFloat2(&currentPosition);
            auto deltaPositionVec = ::dx::XMVectorSubtract(currentPositionVec, lastPositionVec);

            deltaPositionVec = ::dx::XMVectorSetX(deltaPositionVec, -::dx::XMVectorGetX(deltaPositionVec));

            camera_.SetX(camera_.GetX() + -::dx::XMVectorGetX(deltaPositionVec) * s_zoomIncrement_);
            camera_.SetY(camera_.GetY() + -::dx::XMVectorGetY(deltaPositionVec) * s_zoomIncrement_);

            last_position_ = currentPosition;
        }
    }
}