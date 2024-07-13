module;

export module FatPound.DSA.LinkedList.SinglyCircularLL;

import FatPound.DSA.LinkedList.SinglyLL;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class SinglyCircularLL final : public SinglyLL<T>
    {
        using typename SinglyLL<T>::Node_;

        using SinglyLL<T>::SinglyLL;

    public:
        SinglyCircularLL() = default;
        SinglyCircularLL(const SinglyCircularLL& src) = delete;
        SinglyCircularLL& operator = (const SinglyCircularLL& src) = delete;

        SinglyCircularLL(SinglyCircularLL&& src) noexcept
            :
            SinglyLL(std::move(src))
        {

        }
        SinglyCircularLL& operator = (SinglyCircularLL&& src) noexcept
        {
            if (this != std::addressof(src) && typeid(src) == typeid(*this) && src.list_ != nullptr)
            {
                Delete_();

                this->list_ = std::exchange(src.list_, nullptr);
                this->end_ = std::exchange(src.end_, nullptr);

                this->item_count_ = std::exchange(src.item_count_, 0u);
            }

            return *this;
        }
        virtual ~SinglyCircularLL() noexcept
        {
            Delete_();
        }


    public:
        virtual void Add(const T& new_item) override final
        {
            Node_* new_part = new Node_(new_item);

            ++this->item_count_;

            if (this->list_ == nullptr)
            {
                this->list_ = new_part;
                this->end_ = new_part;
                this->list_->next = this->list_;

                return;
            }

            this->end_->next = new_part;
            new_part->next = this->list_;

            this->end_ = new_part;
        }
        virtual void AddOrdered(const T& new_item) override final
        {
            Node_* new_part = new Node_(new_item);

            ++this->item_count_;

            if (this->list_ == nullptr)
            {
                this->list_ = new_part;
                new_part->next = this->list_;

                return;
            }

            if (new_item < this->list_->item)
            {
                new_part->next = this->list_;
                this->list_ = new_part;

                this->end_->next = new_part;

                return;
            }

            Node_* temp = this->list_;
            Node_* start = temp;

            while (temp->next != start)
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
        virtual void Reverse() override final
        {
            if (this->list_ == nullptr)
            {
                return;
            }

            if (this->item_count_ < 2u)
            {
                return;
            }

            Node_* start_backup = this->list_;

            Node_* t;
            Node_* a = nullptr;
            Node_* x;

            Node_* temp = this->list_;
            Node_* start = temp;

            while (true)
            {
                t = temp->next;
                temp->next = a;
                a = t;
                x = temp;

                if (t->next) // C6011, I think its gone
                {
                    temp = t->next;
                    t->next = x;
                }

                if (temp == start)
                {
                    start->next = t;

                    this->list_ = t;

                    return;
                }

                if (temp->next == start)
                {
                    start->next = temp;

                    temp->next = t;
                    this->list_ = temp;

                    return;
                }
            }

            start->next = temp;

            this->end_ = start_backup;
        }
        virtual void Print() const override final
        {
            if (this->list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty SinglyCircularLL!");
            }

            Node_* temp = this->list_;
            Node_* start = temp;

            do
            {
                std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            }
            while (temp != start);

            std::cout << '\n';
        }


    protected:
        virtual void Delete_() override final
        {
            if (this->list_ == nullptr)
            {
                return;
            }

            Node_* start = this->list_;
            Node_* ex = this->list_;
            Node_* temp;

            do
            {
                temp = ex->next;
                delete ex;

                ex = temp;
            }
            while (ex != start);

            this->list_ = nullptr;
            this->end_  = nullptr;

            this->item_count_ = 0u;
        }


    private:
    };
}