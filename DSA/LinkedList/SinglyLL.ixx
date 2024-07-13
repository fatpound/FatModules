module;

export module FatPound.DSA.LinkedList.SinglyLL;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class SinglyLL
    {
    public:
        SinglyLL() = default;
        SinglyLL(const SinglyLL& src) = delete;
        SinglyLL& operator = (const SinglyLL& src) = delete;

        SinglyLL(SinglyLL&& src) noexcept
            :
            list_(std::exchange(src.list_, nullptr)),
            end_(std::exchange(src.end_, nullptr)),
            item_count_(std::exchange(src.item_count_, 0u))
        {

        }
        SinglyLL& operator = (SinglyLL&& src) noexcept
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
        virtual ~SinglyLL() noexcept
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
            }
            else
            {
                end_->next = new_part;
            }

            end_ = new_part;
        }
        virtual void AddOrdered(const T& new_item)
        {
            Node_* new_part = new Node_(new_item);

            ++item_count_;

            if (list_ == nullptr)
            {
                list_ = new_part;
                end_ = new_part;

                return;
            }

            if (new_item < list_->item)
            {
                new_part->next = list_;
                list_ = new_part;

                return;
            }

            Node_* temp = list_;

            while (temp->next != nullptr)
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
            end_ = new_part;
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

            Node_* start_backup = list_;

            Node_* t;
            Node_* a = nullptr;
            Node_* x;

            Node_* temp = list_;

            while (true)
            {
                t = temp->next;
                temp->next = a;
                a = t;
                x = temp;

                temp = t->next;
                t->next = x;

                if (temp == nullptr)
                {
                    list_ = t;
                    return;
                }

                if (temp->next == nullptr)
                {
                    temp->next = t;
                    list_ = temp;

                    return;
                }
            }

            end_ = start_backup;
        }
        virtual void Print() const
        {
            if (list_ == nullptr)
            {
                throw std::runtime_error("Tried to Print an empty SinglyLL!");
            }

            Node_* temp = list_;

            do
            {
                std::cout << temp << '\t' << temp->item << '\t' << temp->next << '\n';
                temp = temp->next;
            }
            while (temp != nullptr);

            std::cout << '\n';
        }


    protected:
        struct Node_ final
        {
            Node_* next = nullptr;

            T item;

            Node_(T new_item)
                :
                item(new_item)
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

            for (std::size_t i = static_cast<std::size_t>(0); i < item_count_; ++i)
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