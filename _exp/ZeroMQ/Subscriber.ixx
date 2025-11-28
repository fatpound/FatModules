module;

#ifdef FATX_WITH_ZEROMQ
#include "FatZmq.hxx"
#endif

export module FatX.ZeroMQ.Subscriber;

#ifdef FATX_WITH_ZEROMQ

import std;

export namespace fatx::zeromq
{
    class Subscriber final
    {
    public:
        Subscriber(const std::string& address)
            :
            m_context_(1),
            m_subscriber_(m_context_, zmq::socket_type::sub)
        {
            m_subscriber_.connect(address);
            m_subscriber_.set(zmq::sockopt::subscribe, "");
        }

        Subscriber()                      = delete;
        Subscriber(const Subscriber&)     = delete;
        Subscriber(Subscriber&&) noexcept = delete;

        auto operator = (const Subscriber&)     -> Subscriber& = delete;
        auto operator = (Subscriber&&) noexcept -> Subscriber& = delete;
        ~Subscriber() noexcept                                 = default;


    public:
        auto Receive() -> std::string
        {
            zmq::message_t message;

            static_cast<void>(m_subscriber_.recv(message, zmq::recv_flags::none));

            return message.to_string();
        }

        void SetReceiveTimeout(const int milliseconds)
        {
            m_subscriber_.set(zmq::sockopt::rcvtimeo, milliseconds);
        }


    protected:


    private:
        zmq::context_t  m_context_;
        zmq::socket_t   m_subscriber_;
    };
}

#endif

// module : private;
