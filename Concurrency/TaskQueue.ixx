module;

// for lock_guards without CTAD, see: https://clang.llvm.org/docs/DiagnosticsReference.html#wctad-maybe-unsupported

export module FatPound.Concurrency.TaskQueue;

import std;

export namespace fatpound::concurrency
{
    /// @brief A thread-safe queue for managing and executing tasks in FIFO order
    ///
    class TaskQueue final
    {
#if __cplusplus >= 202302L
        using WrappedTask = std::move_only_function<void()>;
#else
        using WrappedTask = std::function<void()>;
#endif

    public:
        explicit TaskQueue()                     = default;
        explicit TaskQueue(const TaskQueue&)     = delete;
        explicit TaskQueue(TaskQueue&&) noexcept = delete;

        auto operator = (const TaskQueue&)     -> TaskQueue& = delete;
        auto operator = (TaskQueue&&) noexcept -> TaskQueue& = delete;
        ~TaskQueue() noexcept                                = default;


    public:
        template <typename F, typename... Args>
        requires std::invocable<F, Args...>
        auto Push(F&& func, Args&&... args) -> auto
        {
            using T = std::invoke_result_t<F, Args...>;

#if __cplusplus >= 202302L and defined(FATLIB_BUILDING_WITH_MSVC)

            auto pkgTask = std::packaged_task<T(Args...)>{ std::bind<>(std::forward<F>(func), std::forward<Args>(args)...) };
            auto future  = pkgTask.get_future();
            
            Push_([&args..., task = std::move<>(pkgTask)]() mutable -> void { static_cast<void>(task(args...)); });

#else

            auto task_sptr = std::make_shared<std::packaged_task<T(Args...)>>(
                std::bind<>(std::forward<F>(func), std::forward<Args>(args)...)
            );

            auto future = task_sptr->get_future();

            Push_(
                [task = std::move<>(task_sptr)]() -> void
                {
                    static_cast<void>((*task)());
                }
            );
#endif

            return future;
        }


    public:
        void ExecuteFirstAndPopOff()
        {
            WrappedTask wtask{};

            {
                const std::lock_guard<std::mutex> lck{ m_mtx_ };

                if (m_tasks_.empty())
                {
                    return;
                }

                wtask = std::move<>(m_tasks_.front());

                m_tasks_.pop_front();
            }

            wtask();
        }


    protected:


    private:
        void Push_(WrappedTask wtask)
        {
            const std::lock_guard<std::mutex> lck{ m_mtx_ };

            m_tasks_.push_back(std::move<>(wtask));
        }


    private:
        std::deque<WrappedTask>   m_tasks_;
        std::mutex                m_mtx_;
    };
}

module : private;
