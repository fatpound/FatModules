module;

export module FatPound.DSA.LinkedList.Doubly;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class Doubly
    {
    public:
        explicit Doubly()              = default;
        explicit Doubly(const Doubly&) = delete;
        Doubly(Doubly&& src) noexcept
            :
            m_list_(std::exchange<>(src.m_list_, nullptr)),
            m_end_(std::exchange<>(src.m_end_, nullptr)),
            m_item_count_(std::exchange<>(src.m_item_count_, 0U))
        {

        }

        auto operator = (const Doubly&) -> Doubly& = delete;
        auto operator = (Doubly&& src) noexcept -> Doubly&
        {
            if ((this not_eq std::addressof<>(src)) and (typeid(src) == typeid(*this)) and (src.m_list_ not_eq nullptr))
            {
                Delete_();

                m_list_ = std::exchange<>(src.m_list_, nullptr);
                m_end_  = std::exchange<>(src.m_end_,  nullptr);

                m_item_count_ = std::exchange<>(src.m_item_count_, 0U);
            }

            return *this;
        }
        virtual ~Doubly() noexcept
        {
            if (not m_cleared_from_derived_dtor_)
            {
                Delete_();
            }
        }


    public:
        [[nodiscard]]
        virtual auto Contains(const T& item) const -> bool final
        {
            return Find_(item) not_eq nullptr;
        }

        virtual void Add(const T& new_item)
        {
            auto* const new_part = new Node_(new_item);

            ++m_item_count_;

            if (m_list_ == nullptr)
            {
                m_list_ = new_part;
                m_end_  = new_part;

                return;
            }

            m_end_->next = new_part;
            new_part->prev = m_end_;
            m_end_ = new_part;
        }
        virtual void AddOrdered(const T& new_item)
        {
            auto* const new_part = new Node_(new_item);

            ++m_item_count_;

            if (m_list_ == nullptr)
            {
                m_list_ = new_part;
                return;
            }

            if (new_item < m_list_->item)
            {
                new_part->next = m_list_;
                m_list_->prev = new_part;
                m_list_ = new_part;

                return;
            }

            Node_* temp = m_list_;

            while (temp->next not_eq nullptr)
            {
                if (temp->item <= new_item && new_item <= temp->next->item)
                {
                    new_part->next = temp->next;
                    new_part->prev = temp;
                    temp->next->prev = new_part;
                    temp->next = new_part;

                    return;
                }

                temp = temp->next;
            }

            temp->next = new_part;
            new_part->prev = temp;
        }
        virtual void Reverse()
        {
            if (m_list_ == nullptr)
            {
                return;
            }

            if (this->m_item_count_ < 2U)
            {
                return;
            }

            Node_* temp = m_list_;

            while (temp->next not_eq nullptr)
            {
                std::swap<>(temp->prev, temp->next);
                temp = temp->prev;
            }

            std::swap(temp->prev, temp->next);

            m_list_ = temp;
        }
        virtual void Print() const
        {
            if (m_list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty Doubly!");
            }

            Node_* temp = m_list_;

            do
            {
                std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';

                temp = temp->next;
            }
            while (temp not_eq nullptr);

            std::cout << '\n';
        }


    protected:
        struct alignas(32) Node_ final
        {
            explicit Node_(T new_item)
                :
                item{ new_item }
            {

            }

            Node_* prev{};
            Node_* next{};

            T item;
        };


    protected:
        [[nodiscard]]
        virtual auto Find_(const T& item) const -> Node_* final
        {
            if (m_item_count_ == 0U)
            {
                return nullptr;
            }

            if (m_item_count_ == 1U)
            {
                return m_list_->item == item
                    ? m_list_
                    : nullptr
                    ;
            }

            Node_* temp = m_list_;

            for (std::size_t i{}; i < m_item_count_; ++i)
            {
                if (temp->item == item)
                {
                    return temp;
                }

                temp = temp->next;
            }

            return nullptr;
        }


    protected:
        void Delete_()
        {
            if (m_list_ == nullptr)
            {
                return;
            }

            Node_* exes = m_list_;
            Node_* temp{};

            do
            {
                temp = exes->next;

                delete exes;

                exes = temp;
            }
            while (exes not_eq nullptr);

            m_list_ = nullptr;
            m_end_  = nullptr;

            m_item_count_ = 0U;
        }


    protected:
        Node_* m_list_{};
        Node_* m_end_{};

        std::size_t m_item_count_{};

        bool m_cleared_from_derived_dtor_{};


    private:
    };
}

module : private;
