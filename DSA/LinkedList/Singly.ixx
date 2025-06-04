module;

export module FatPound.DSA.LinkedList.Singly;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class Singly
    {
    public:
        explicit Singly(std::ostream& os = std::cout)
            :
            m_os_(&os)
        {

        }

        explicit Singly(const Singly&) = delete;
        Singly(Singly&& src) noexcept
            :
            m_list_(std::exchange<>(src.m_list_, nullptr)),
            m_end_(std::exchange<>(src.m_end_, nullptr)),
            m_item_count_(std::exchange<>(src.m_item_count_, 0U))
        {

        }

        auto operator = (const Singly&) -> Singly& = delete;
        auto operator = (Singly&& src) noexcept -> Singly&
        {
            if ((this not_eq std::addressof<>(src)) and (typeid(src) == typeid(*this)) and (src.m_list_ not_eq nullptr))
            {
                Delete_();

                m_list_ = std::exchange<>(src.m_list_, nullptr);
                m_end_  = std::exchange<>(src.m_end_, nullptr);

                m_item_count_ = std::exchange<>(src.m_item_count_, 0U);
            }

            return *this;
        }
        virtual ~Singly() noexcept
        {
            if (not m_cleared_from_derived_dtor_)
            {
                Delete_();
            }
        }


    public:
        [[nodiscard]]
        virtual auto Contains(const T& item) const noexcept -> bool final
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
            }
            else
            {
                m_end_->next = new_part;
            }

            m_end_ = new_part;
        }
        virtual void AddOrdered(const T& new_item)
        {
            auto* const new_part = new Node_(new_item);

            ++m_item_count_;

            if (m_list_ == nullptr)
            {
                m_list_ = new_part;
                m_end_ = new_part;

                return;
            }

            if (new_item < m_list_->item)
            {
                new_part->next = m_list_;
                m_list_ = new_part;

                return;
            }

            Node_* temp = m_list_;

            while (temp->next not_eq nullptr)
            {
                if ((temp->item <= new_item) and (new_item <= temp->next->item))
                {
                    new_part->next = temp->next;
                    temp->next = new_part;

                    return;
                }

                temp = temp->next;
            }

            temp->next = new_part;

            m_end_ = new_part;
        }
        virtual void Reverse() noexcept
        {
            if (m_list_ == nullptr)
            {
                return;
            }

            if (this->m_item_count_ < 2U)
            {
                return;
            }

            Node_* start_backup = m_list_;

            Node_* temp1{};
            Node_* temp2{};
            Node_* temp3{};

            Node_* temp = m_list_;

            while (true)
            {
                temp1 = temp->next;
                temp->next = temp2;
                temp2 = temp1;
                temp3 = temp;

                temp = temp1->next;
                temp1->next = temp3;

                if (temp == nullptr)
                {
                    m_list_ = temp1;
                    return;
                }

                if (temp->next == nullptr)
                {
                    temp->next = temp1;
                    m_list_ = temp;

                    return;
                }
            }

            m_end_ = start_backup;
        }
        virtual void Print() const
        {
            if (m_list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty Singly!");
            }

            Node_* temp = m_list_;

            do
            {
                *m_os_ << temp << '\t' << temp->item << '\t' << temp->next << '\n';

                temp = temp->next;
            }
            while (temp not_eq nullptr);

            *m_os_ << '\n';
        }


    public:
        void SetOstream(std::ostream& os) noexcept
        {
            m_os_ = &os;
        }


    protected:
        struct alignas(16) Node_ final
        {
            explicit Node_(const T& new_item) noexcept
                :
                item(new_item)
            {

            }

            Node_* next{};

            T item;
        };


    protected:
        [[nodiscard]]
        virtual auto Find_(const T& item) const noexcept -> Node_* final
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
        void Delete_() noexcept
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

        std::ostream* m_os_;

        bool m_cleared_from_derived_dtor_{};


    private:
    };
}

module : private;
