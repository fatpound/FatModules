module;

#ifdef FATX_WITH_ZEROMQ
#include "FatZmq.hxx"
#endif

export module FatX.ZeroMQ.Publisher;

#ifdef FATX_WITH_ZEROMQ

import std;

export namespace fatx::zeromq
{
    class Publisher final
    {
    public:
        Publisher(const std::string& address)
            :
            m_context_(1),
            m_publisher_(m_context_, zmq::socket_type::pub)
        {
            m_publisher_.bind(address);
        }

        Publisher()                     = delete;
        Publisher(const Publisher&)     = delete;
        Publisher(Publisher&&) noexcept = delete;

        auto operator = (const Publisher&)     -> Publisher& = delete;
        auto operator = (Publisher&&) noexcept -> Publisher& = delete;
        ~Publisher() noexcept                                = default;


    public:
        auto Publish(const std::string& msg) -> zmq::send_result_t
        {
            return m_publisher_.send(zmq::message_t(msg.begin(), msg.end()), zmq::send_flags::none);
        }


    protected:


    private:
        zmq::context_t  m_context_;
        zmq::socket_t   m_publisher_;
    };
}

#endif

// module : private;
