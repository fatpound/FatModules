module;

#include <FatNamespaces.hxx>

export module FatPound.Random.URand;

import std;

export namespace fatpound::random
{
    class URand final
    {
    public:
        URand(const std::size_t& limit)
            :
            m_vec_(limit == 0 ? 1ULL : limit),
            m_rng_(std::random_device{}()),
            m_current_(0ULL)
        {
            std::ranges::iota(m_vec_, 0ULL);
        }

        URand()                 = delete;
        URand(const URand&)     = delete;
        URand(URand&&) noexcept = delete;

        auto operator = (const URand&)     -> URand& = delete;
        auto operator = (URand&&) noexcept -> URand& = delete;
        ~URand() noexcept                            = default;


    public:
        auto operator () () -> std::ptrdiff_t
        {
            if (m_current_ >= m_vec_.size())
            {
                return -1;
            }

            {
                std::uniform_int_distribution<std::size_t> idxDist(m_current_, m_vec_.size() - 1ULL);

                std::swap<>(m_vec_[m_current_], m_vec_[idxDist(m_rng_)]);
            }

            const auto val = m_vec_[m_current_];

            ++m_current_;

            return static_cast<std::ptrdiff_t>(val);
        }


    protected:


    private:
        std::vector<std::size_t>  m_vec_;
        std::minstd_rand          m_rng_;
        std::size_t               m_current_;
    };

    using UniqueRand = URand;
}

module : private;
