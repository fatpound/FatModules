module;

#ifdef FATLIB_BUILDING_WITH_MSVC
    #include <_macros/STL.hxx>
    #include <DirectXMath.h>
#endif

export module FatPound.Geometry.Shape.Triangle;

#ifdef FATLIB_BUILDING_WITH_MSVC

import FatPound.Geometry.Common;
import FatPound.Geometry.Shape.Circle;
import FatPound.Math.Multiplicative;
import FatPound.Traits.Bitwise;

import std;

export namespace fatpound::geometry::shape
{
    class alignas(32) Triangle
    {
        static constexpr auto scx_Default_Z_ = 1.0F;
        static constexpr auto scx_Default_W_ = 1.0F;

    public:
        explicit Triangle(const DirectX::XMVECTOR& va, const DirectX::XMVECTOR& vb, const DirectX::XMVECTOR& vc)
            :
            m_va_(va),
            m_vb_(vb),
            m_vc_(vc)
        {
            if (not S_IsValid<>(GetSideLengthA(), GetSideLengthB(), GetSideLengthC()))
            {
                throw std::invalid_argument("The provided vertices do not form a valid triangle.");
            }
        }

        explicit Triangle() noexcept  = delete;
        Triangle(const Triangle&)     = default;
        Triangle(Triangle&&) noexcept = default;

        auto operator = (const Triangle&)     -> Triangle& = default;
        auto operator = (Triangle&&) noexcept -> Triangle& = default;
        ~Triangle() noexcept                               = default;
            

    public:
        template <traits::UIntegralOrFloating T> static constexpr auto S_IsValid   (const T& a, const T& b, const T& c) noexcept -> bool
        {
            return     ((std::abs(b - c) < a) and (a < (b + c)))
                   and ((std::abs(a - c) < b) and (b < (a + c)))
                   and ((std::abs(a - b) < c) and (c < (a + b)));
        }
        template <traits::UIntegralOrFloating T> static constexpr auto S_Perimeter (const T& a, const T& b, const T& c) noexcept -> T
        {
            return a + b + c;
        }
        template <traits::UIntegralOrFloating T> static CX_MATH26 auto S_Area      (const T& a, const T& b, const T& c) noexcept -> T
        {
            const auto s = S_Perimeter<>(a, b, c) / static_cast<T>(2);

            return std::sqrt(s * (s - a) * (s - b) * (s - c));
        }
        template <traits::UIntegralOrFloating T> static constexpr auto S_Area      (const T& height, const T& base) noexcept -> T
        {
            return (base * height) / static_cast<T>(2.0);
        }


    public:
        auto GetVertexA            () const noexcept -> DirectX::XMVECTOR
        {
            return m_va_;
        }
        auto GetVertexB            () const noexcept -> DirectX::XMVECTOR
        {
            return m_vb_;
        }
        auto GetVertexC            () const noexcept -> DirectX::XMVECTOR
        {
            return m_vc_;
        }
        
        auto GetCentroid           () const noexcept -> DirectX::XMVECTOR
        {
            return (m_va_ + m_vb_ + m_vc_) / 3.0F;
        }
        
        auto GetSideLengthA        () const noexcept -> float
        {
            return Distance4(m_vb_, m_vc_);
        }
        auto GetSideLengthB        () const noexcept -> float
        {
            return Distance4(m_va_, m_vc_);
        }
        auto GetSideLengthC        () const noexcept -> float
        {
            return Distance4(m_va_, m_vb_);
        }

        auto GetArea               () const noexcept -> float
        {
            return S_Area<>(GetSideLengthA(), GetSideLengthB(), GetSideLengthC());
        }
        auto GetPerimeter          () const noexcept -> float
        {
            return S_Perimeter<>(GetSideLengthA(), GetSideLengthB(), GetSideLengthC());
        }
        auto GetIncircleRadius     () const noexcept -> float
        {
            return GetArea() / (GetPerimeter() * 0.5F);
        }
        auto GetCircumcircleRadius () const noexcept -> float
        {
            return (GetSideLengthA() * GetSideLengthB() * GetSideLengthC()) / (4.0F * GetArea());
        }

        auto GetIncircle           () const noexcept -> Circle
        {
            const auto& a         = GetSideLengthA();
            const auto& b         = GetSideLengthB();
            const auto& c         = GetSideLengthC();
            const auto& perimeter = S_Perimeter<>(a, b, c);

            const auto&  incenter = ((m_va_ * a) + (m_vb_ * b) + (m_vc_ * c)) / perimeter;
            const auto&    radius = GetArea() / (perimeter * 0.5F);

            return Circle(incenter, radius);
        }
        auto GetCircumcircle       () const noexcept -> Circle
        {
            const auto& a = GetSideLengthA();
            const auto& b = GetSideLengthB();
            const auto& c = GetSideLengthC();

            const auto& aSq = math::Square<>(a);
            const auto& bSq = math::Square<>(b);
            const auto& cSq = math::Square<>(c);

            const auto& alpha     = aSq * (bSq + cSq - aSq);
            const auto& beta      = bSq * (aSq + cSq - bSq);
            const auto& gamma     = cSq * (aSq + bSq - cSq);

            const auto& center = ((m_va_ * alpha) + (m_vb_ * beta) + (m_vc_ * gamma)) / (alpha + beta + gamma);

            const auto& area   = GetArea();
            const auto& radius = (a * b * c) / (4.0F * area);

            return Circle(center, radius);
        }
        
        auto IsEquilateral         (const float& epsilon = 0.001F) const noexcept -> bool
        {
            const auto& a = GetSideLengthA();
            const auto& b = GetSideLengthB();
            const auto& c = GetSideLengthC();

            return (std::abs(a - b) <= epsilon) and (std::abs(b - c) <= epsilon);
        }
        auto IsIsosceles           (const float& epsilon = 0.001F) const noexcept -> bool
        {
            const auto& a = GetSideLengthA();
            const auto& b = GetSideLengthB();
            const auto& c = GetSideLengthC();

            return (std::abs(a - b) <= epsilon) or (std::abs(b - c) <= epsilon) or (std::abs(a - c) <= epsilon);
        }
        auto IsScalene             (const float& epsilon = 0.001F) const noexcept -> bool
        {
            return not IsIsosceles(epsilon);
        }
        auto IsRightAngle          (const float& epsilon = 0.001F) const noexcept -> bool
        {
            std::array sides = { GetSideLengthA(), GetSideLengthB(), GetSideLengthC() };

            std::ranges::sort(sides);

            const auto& aSq_plus_bSq = math::Square<>(sides[0]) + math::Square<>(sides[1]);
            const auto& cSq          = math::Square<>(sides[2]);

            return std::abs(aSq_plus_bSq - cSq) <= epsilon;
        }
        
        void TranslateBy           (const DirectX::XMVECTOR& v) noexcept
        {
            m_va_ += v;
            m_vb_ += v;
            m_vc_ += v;
        }

        auto Distance_CentroidToCentroid                 (const Triangle& other) const noexcept -> float
        {
            return Distance4(GetCentroid(), other.GetCentroid());
        }
        auto Distance_CentroidToCircumcircleEdge         (const Triangle& other) const noexcept -> float
        {
            return Distance_CentroidToCentroid(other) - other.GetCircumcircleRadius();
        }
        auto Distance_CentroidToIncircleEdge             (const Triangle& other) const noexcept -> float
        {
            return Distance_CentroidToCentroid(other) - other.GetIncircleRadius();
        }
        auto Distance_CircumcircleEdgeToCentroid         (const Triangle& other) const noexcept -> float
        {
            return Distance_CentroidToCentroid(other) - GetCircumcircleRadius();
        }
        auto Distance_CircumcircleEdgeToCircumcircleEdge (const Triangle& other) const noexcept -> float
        {
            return Distance_CentroidToCentroid(other) - (GetCircumcircleRadius() + other.GetCircumcircleRadius());
        }
        auto Distance_CircumcircleEdgeToIncircleEdge     (const Triangle& other) const noexcept -> float
        {
            return Distance_CentroidToCentroid(other) - (GetCircumcircleRadius() + other.GetIncircleRadius());
        }
        auto Distance_IncircleEdgeToCentroid             (const Triangle& other) const noexcept -> float
        {
            return Distance_CentroidToCentroid(other) - GetIncircleRadius();
        }
        auto Distance_IncircleEdgeToIncircleEdge         (const Triangle& other) const noexcept -> float
        {
            return Distance_CentroidToCentroid(other) - (GetIncircleRadius() + other.GetIncircleRadius());
        }
        auto Distance_IncircleEdgeToCircumcircleEdge     (const Triangle& other) const noexcept -> float
        {
            return Distance_CentroidToCentroid(other) - (GetIncircleRadius() + other.GetCircumcircleRadius());
        }

        auto Distance_CentroidToCenter                   (const Circle&  circle) const noexcept -> float
        {
            return Distance4(GetCentroid(), circle.GetCenter());
        }
        auto Distance_CentroidToEdge                     (const Circle&  circle) const noexcept -> float
        {
            return Distance_CentroidToCenter(circle) - circle.GetRadius();
        }
        auto Distance_CircumcircleEdgeToCenter           (const Circle&  circle) const noexcept -> float
        {
            return Distance_CentroidToCenter(circle) - GetCircumcircleRadius();
        }
        auto Distance_CircumcircleEdgeToEdge             (const Circle&  circle) const noexcept -> float
        {
            return Distance_CentroidToCenter(circle) - (GetCircumcircleRadius() + circle.GetRadius());
        }
        auto Distance_IncircleEdgeToCenter               (const Circle&  circle) const noexcept -> float
        {
            return Distance_CentroidToCenter(circle) - GetIncircleRadius();
        }
        auto Distance_IncircleEdgeToEdge                 (const Circle&  circle) const noexcept -> float
        {
            return Distance_CentroidToCenter(circle) - (GetIncircleRadius() + circle.GetRadius());
        }


    protected:


    private:
        DirectX::XMVECTOR   m_va_;
        DirectX::XMVECTOR   m_vb_;
        DirectX::XMVECTOR   m_vc_;
    };
}

#endif

// module : private;
