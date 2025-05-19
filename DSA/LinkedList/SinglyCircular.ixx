module;

export module FatPound.DSA.LinkedList.SinglyCircular;

import FatPound.DSA.LinkedList.Singly;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class SinglyCircular final : public Singly<T>
    {
        using typename Singly<T>::Node_;

    public:
        explicit SinglyCircular()                      = default;
        explicit SinglyCircular(const SinglyCircular&) = delete;
        SinglyCircular(SinglyCircular&& src) noexcept
            :
            Singly<T>(std::move<>(src))
        {

        }

        auto operator = (const SinglyCircular&) -> SinglyCircular& = delete;
        auto operator = (SinglyCircular&& src) noexcept -> SinglyCircular&
        {
            if ((this not_eq std::addressof<>(src)) and (typeid(src) == typeid(*this)) and (src.m_list_ not_eq nullptr))
            {
                Delete_();

                this->m_list_ = std::exchange<>(src.m_list_, nullptr);
                this->m_end_  = std::exchange<>(src.m_end_,  nullptr);

                this->m_item_count_ = std::exchange<>(src.m_item_count_, 0U);
            }

            return *this;
        }
        virtual ~SinglyCircular() noexcept override final
        {
            Delete_();

            this->m_cleared_from_derived_dtor_ = true;
        }


    public:
        virtual void Add(const T& new_item) override final
        {
            auto* const new_part = new Node_(new_item);

            ++this->m_item_count_;

            if (this->m_list_ == nullptr)
            {
                this->m_list_ = new_part;
                this->m_end_  = new_part;
                this->m_list_->next = this->m_list_;

                return;
            }

            this->m_end_->next = new_part;
            new_part->next = this->m_list_;
            this->m_end_ = new_part;
        }
        virtual void AddOrdered(const T& new_item) override final
        {
            auto* const new_part = new Node_(new_item);

            ++this->m_item_count_;

            if (this->m_list_ == nullptr)
            {
                this->m_list_ = new_part;
                new_part->next = this->m_list_;

                return;
            }

            if (new_item < this->m_list_->item)
            {
                new_part->next = this->m_list_;
                this->m_list_ = new_part;

                this->m_end_->next = new_part;

                return;
            }

            Node_* temp = this->m_list_;
            Node_* start = temp;

            while (temp->next not_eq start)
            {
                if (temp->item <= new_item && new_item <= temp->next->item)
                {
                    new_part->next = temp->next;
                    temp->next = new_part;

                    return;
                }

                temp = temp->next;
            }

            temp->next = new_part;
            new_part->next = start;
        }
        virtual void Reverse() noexcept override final
        {
            if (this->m_list_ == nullptr)
            {
                return;
            }

            if (this->m_item_count_ < 2U)
            {
                return;
            }

            Node_* start_backup = this->m_list_;

            Node_* temp1{};
            Node_* temp2{};
            Node_* temp3{};

            Node_* temp = this->m_list_;
            Node_* start = temp;

            while (true)
            {
                temp1 = temp->next;

#ifdef _MSC_VER
                __assume(temp1 not_eq nullptr);
#endif

                temp->next = temp2;
                temp2 = temp1;
                temp3 = temp;

                if (temp1->next not_eq nullptr)
                {
                    temp = temp1->next;
                    temp1->next = temp3;
                }

                if (temp == start)
                {
                    start->next = temp1;

                    this->m_list_ = temp1;

                    return;
                }

                if (temp->next == start)
                {
                    start->next = temp;

                    temp->next = temp1;
                    this->m_list_ = temp;

                    return;
                }
            }

            start->next = temp;

            this->m_end_ = start_backup;
        }
        virtual void Print() const override final
        {
            if (this->m_list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty SinglyCircular!");
            }

            const Node_* const start = this->m_list_;
            const Node_*        temp = this->m_list_;

            do
            {
                std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';

                temp = temp->next;
            }
            while (temp not_eq start);

            std::cout << '\n';
        }


    protected:
        void Delete_() noexcept
        {
            if (this->m_list_ == nullptr)
            {
                return;
            }

            const Node_* const start = this->m_list_;
                  Node_*        exes = this->m_list_;
                  Node_*        temp{};

            do
            {
                temp = exes->next;

                delete exes;

                exes = temp;
            }
            while (exes not_eq start);

            this->m_list_ = nullptr;
            this->m_end_  = nullptr;

            this->m_item_count_ = 0U;
        }


    private:
    };
}

module : private;
