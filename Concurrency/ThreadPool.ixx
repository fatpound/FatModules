module;

export module FatPound.Concurrency.ThreadPool;

import FatPound.Concurrency.TaskQueue;
import std;

export namespace fatpound::concurrency
{
    /// @brief A thread pool for managing and executing tasks concurrently
    ///
    class ThreadPool final
    {
    public:
        explicit ThreadPool(const std::size_t threadCount = std::thread::hardware_concurrency())
        {
            m_workers_.reserve(threadCount);

            for (std::size_t i{0U}; i < threadCount; ++i)
            {
                m_workers_.emplace_back(
                    [this]() -> void
                    {
                        WorkerLoop_();
                    }
                );
            }
        }

        explicit ThreadPool(const ThreadPool&)     = delete;
        explicit ThreadPool(ThreadPool&&) noexcept = delete;
        auto operator = (const ThreadPool&)     -> ThreadPool& = delete;
        auto operator = (ThreadPool&&) noexcept -> ThreadPool& = delete;
        ~ThreadPool() noexcept
        {
            {
                const std::lock_guard<std::mutex> sl{ m_mtx_ };

                m_stop_ = true;
            }

            m_cv_.notify_all();
        }


    public:
        template <typename F, typename... Args>
        requires std::invocable<F, Args...>
        auto Submit(F&& func, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>
        {
            auto future = m_tasks_.Push(std::forward<F>(func), std::forward<Args>(args)...);

            {
                const std::lock_guard<std::mutex> sl{ m_mtx_ };
            }

            m_cv_.notify_one();

            return future;
        }


    protected:


    private:
        void WorkerLoop_()
        {
            while (true)
            {
                {
                    std::unique_lock<std::mutex> ulock{ m_mtx_ };

                    m_cv_.wait(
                        ulock,
                        [this]() -> bool
                        {
                            return m_stop_ or not m_tasks_.Empty();
                        }
                    );

                    if (m_stop_ and m_tasks_.Empty())
                    {
                        return;
                    }
                }

                try
                {
                    m_tasks_.PopAndExecute();
                }
                catch (...)
                {
#if __cplusplus >= 202302L
                    std::println<>("Thread {} failed while running task!", std::this_thread::get_id());
#else
                    std::cout << "Thread " << std::this_thread::get_id() << " failed while running task!";
#endif
                }
            }
        }


    private:
        TaskQueue                   m_tasks_;
        std::vector<std::jthread>   m_workers_;

        std::mutex                  m_mtx_;
        std::condition_variable     m_cv_;
        bool                        m_stop_{};
    };
}

// module : private;
