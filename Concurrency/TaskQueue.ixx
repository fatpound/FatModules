module;

export module FatPound.Concurrency.TaskQueue;

import std;

export namespace fatpound::concurrency
{
    class TaskQueue final
    {
        using WrappedTask = std::move_only_function<void()>;

    public:
        explicit TaskQueue()                     = default;
        explicit TaskQueue(const TaskQueue&)     = delete;
        explicit TaskQueue(TaskQueue&&) noexcept = delete;

        auto operator = (const TaskQueue&)     -> TaskQueue& = delete;
        auto operator = (TaskQueue&&) noexcept -> TaskQueue& = delete;
        ~TaskQueue() noexcept                                = default;


    public:
        void ExecuteFirstAndPopOff();


    public:
        template <typename F, typename... Args>
        requires std::invocable<F, Args...>
        auto Push(F&& function, Args&&... args) -> auto
        {
            using T = std::invoke_result_t<F, Args...>;

            auto pkgTask = std::packaged_task<T(Args...)>{ std::bind(std::forward<F>(function), std::forward<Args>(args)...) };
            auto future  = pkgTask.get_future();

            Push_([&, task = std::move(pkgTask)]() mutable -> void { static_cast<void>(task(args...)); });

            return future;
        }


    protected:


    private:
        void Push_(WrappedTask wtask);


    private:
        std::deque<WrappedTask> m_tasks_;

        std::mutex m_mtx_;
    };
}

module : private;