module;

#include <cassert>

export module FatPound.Random.URand;

import std;

export namespace fatpound::random
{
    /// @brief URand is a functor that generates a random permutation of unique indices in the range [0, count).
    ///        Each call to operator() returns the next unique random index, or -1 if all indices have been used
    /// 
    class URand final
    {
    public:
        explicit URand(const std::size_t& count)
            :
            m_vec_((assert(count > 0), count)),
            m_rng_(std::random_device{}()),
            m_dist_(0ULL, count - 1ULL),
            m_current_(0ULL)
        {
#if __cplusplus >= 202302L
            std::ranges::iota(m_vec_, 0ULL);
#else
            std::iota<>(m_vec_.begin(), m_vec_.end(), 0ULL);
#endif
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

            m_dist_.param(decltype(m_dist_)::param_type{ m_current_, m_vec_.size() - 1ULL });

            std::swap<>(m_vec_[m_current_], m_vec_[m_dist_(m_rng_)]);

            const auto val = m_vec_[m_current_];

            ++m_current_;

            return static_cast<std::ptrdiff_t>(val);
        }


    protected:


    private:
        std::vector<std::size_t>                     m_vec_;
        std::minstd_rand                             m_rng_;
        std::uniform_int_distribution<std::size_t>   m_dist_;

        std::size_t                                  m_current_;
    };

    using UniqueRand = URand;
}

module : private;
