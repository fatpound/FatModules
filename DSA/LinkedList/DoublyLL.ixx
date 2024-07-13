module;

export module FatPound.DSA.LinkedList.DoublyLL;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class DoublyLL
    {
    public:
        DoublyLL() = default;
        DoublyLL(const DoublyLL& src) = delete;
        DoublyLL& operator = (const DoublyLL& src) = delete;

        DoublyLL(DoublyLL&& src) noexcept
            :
            list_(std::exchange(src.list_, nullptr)),
            end_(std::exchange(src.end_, nullptr)),
            item_count_(std::exchange(src.item_count_, 0u))
        {

        }
        DoublyLL& operator = (DoublyLL&& src) noexcept
        {
            if (this != std::addressof(src) && typeid(src) == typeid(*this) && src.list_ != nullptr)
            {
                Delete_();

                list_ = std::exchange(src.list_, nullptr);
                end_ = std::exchange(src.end_, nullptr);

                item_count_ = std::exchange(src.item_count_, 0u);
            }

            return *this;
        }
        virtual ~DoublyLL() noexcept
        {
            Delete_();
        }


    public:
        virtual bool Contains(const T& item) const final
        {
            return Find_(item) != nullptr;
        }

        virtual void Add(const T& new_item)
        {
            Node_* new_part = new Node_(new_item);

            ++item_count_;

            if (list_ == nullptr)
            {
                list_ = new_part;
                end_ = new_part;

                return;
            }

            end_->next = new_part;
            new_part->prev = end_;

            end_ = new_part;
        }
        virtual void AddOrdered(const T& new_item)
        {
            Node_* new_part = new Node_(new_item);

            ++item_count_;

            if (list_ == nullptr)
            {
                list_ = new_part;
                return;
            }

            if (new_item < list_->item)
            {
                new_part->next = list_;
                list_->prev = new_part;
                list_ = new_part;

                return;
            }

            Node_* temp = list_;

            while (temp->next != nullptr)
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
            if (list_ == nullptr)
            {
                return;
            }

            if (this->item_count_ < 2u)
            {
                return;
            }

            Node_* temp = list_;

            while (temp->next != nullptr)
            {
                std::swap(temp->prev, temp->next);
                temp = temp->prev;
            }

            std::swap(temp->prev, temp->next);
            list_ = temp;
        }
        virtual void Print() const
        {
            if (list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty DoublyLL!");
            }

            Node_* temp = list_;

            do
            {
                std::cout << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            }
            while (temp != nullptr);

            std::cout << '\n';
        }


    protected:
        struct Node_ final
        {
            Node_* prev = nullptr;
            Node_* next = nullptr;

            T item;

            Node_(T new_item)
                :
                item{ new_item }
            {

            }
        };


    protected:
        virtual Node_* Find_(const T& item) const final
        {
            if (item_count_ == 0u)
            {
                return nullptr;
            }

            if (item_count_ == 1u)
            {
                return list_->item == item
                    ? list_
                    : nullptr
                    ;
            }

            Node_* temp = list_;

            for (std::size_t i = 0u; i < item_count_; ++i)
            {
                if (temp->item == item)
                {
                    return temp;
                }

                temp = temp->next;
            }

            return nullptr;
        }

        virtual void Delete_()
        {
            if (list_ == nullptr)
            {
                return;
            }

            Node_* ex = list_;
            Node_* temp;

            do
            {
                temp = ex->next;
                delete ex;

                ex = temp;
            }
            while (ex != nullptr);

            list_ = nullptr;
            end_  = nullptr;

            item_count_ = 0u;
        }


    protected:
        Node_* list_ = nullptr;
        Node_* end_  = nullptr;

        std::size_t item_count_ = 0u;


    private:
    };
}