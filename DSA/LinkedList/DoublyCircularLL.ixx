module;

export module FatPound.DSA.LinkedList.DoublyCircularLL;

import FatPound.DSA.LinkedList.DoublyLL;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class DoublyCircularLL final : public DoublyLL<T>
    {
        using typename DoublyLL<T>::Node_;

        using DoublyLL<T>::DoublyLL;

    public:
        DoublyCircularLL() = default;
        DoublyCircularLL(const DoublyCircularLL& src) = delete;
        DoublyCircularLL& operator = (const DoublyCircularLL& src) = delete;

        DoublyCircularLL(DoublyCircularLL&& src) noexcept
            :
            DoublyLL(std::move(src))
        {

        }
        DoublyCircularLL& operator = (DoublyCircularLL&& src) noexcept
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
        virtual ~DoublyCircularLL() noexcept
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
                new_part->next = new_part;
                new_part->prev = new_part;

                this->list_ = new_part;
                this->end_ = new_part;

                return;
            }

            this->end_->next = new_part;
            new_part->prev = this->end_;
            new_part->next = this->list_;
            this->list_->prev = new_part;

            this->end_ = new_part;
        }
        virtual void AddOrdered(const T& new_item) override final
        {
            Node_* new_part = new Node_(new_item);

            ++this->item_count_;

            if (this->list_ == nullptr)
            {
                new_part->prev = new_part;
                new_part->next = new_part;
                this->list_ = new_part;

                return;
            }

            if (new_item < this->list_->item)
            {
                new_part->next = this->list_;
                this->list_->prev = new_part;
                this->list_ = new_part;

                this->end_->next = this->list_;
                this->list_->prev = this->end_;

                return;
            }

            Node_* temp = this->list_;
            Node_* start = temp;

            while (temp->next != start)
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

            new_part->next = start;
            start->prev = new_part;
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

            Node_* temp = this->list_;
            Node_* start = this->list_;

            while (temp->next != start)
            {
                std::swap(temp->prev, temp->next);
                temp = temp->prev;
            }

            std::swap(temp->prev, temp->next);
            this->list_ = temp;
        }
        virtual void Print() const override final
        {
            if (this->list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty DoublyCircularLL!");
            }

            Node_* temp = this->list_;
            Node_* start = temp;

            do
            {
                std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
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