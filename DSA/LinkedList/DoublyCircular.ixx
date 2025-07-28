module;

export module FatPound.DSA.LinkedList.DoublyCircular;

import FatPound.DSA.LinkedList.Doubly;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class DoublyCircular final : public Doubly<T>
    {
        using typename Doubly<T>::Node_;

    public:
        explicit DoublyCircular(std::ostream& os = std::cout)
            :
            Doubly<T>(os)
        {

        }

        explicit DoublyCircular(const DoublyCircular&) = delete;
        DoublyCircular(DoublyCircular&& src) noexcept
            :
            Doubly<T>(std::move<>(src))
        {

        }

        auto operator = (const DoublyCircular&) -> DoublyCircular& = delete;
        auto operator = (DoublyCircular&& src) noexcept -> DoublyCircular&
        {
            if (this not_eq std::addressof<>(src) and typeid(src) == typeid(*this))
            {
                if (src.IsNotEmpty())
                {
                    ClearList();

                    this->m_start_      = std::exchange<>(src.m_start_, nullptr);
                    this->m_end_        = std::exchange<>(src.m_end_,   nullptr);
                    this->m_item_count_ = std::exchange<>(src.m_item_count_, 0U);
                }

                this->m_os_ = std::exchange<>(src.m_os_, nullptr);
            }

            return *this;
        }
        virtual ~DoublyCircular() noexcept override final
        {
            Clear();

            this->m_cleared_from_derived_dtor_ = true;
        }


    public:
        virtual void Insert(const T& new_item) override final
        {
            auto* const new_part = new Node_(new_item);

            if (this->IsEmpty())
            {
                new_part->next = new_part;
                new_part->prev = new_part;
                this->m_start_ = new_part;
                this->m_end_   = new_part;

                return;
            }

            this->GetEndNode_()->next   = new_part;
            new_part->prev              = this->GetEndNode_();
            new_part->next              = this->GetStartNode_();
            this->GetStartNode_()->prev = new_part;
            this->m_end_                = new_part;

            ++this->m_item_count_;
        }
        virtual void InsertAtFirst_GreaterEq(const T& new_item) override final
        {
            auto* const new_part = new Node_(new_item);

            if (this->GetStartNode_() == nullptr)
            {
                new_part->prev = new_part;
                new_part->next = new_part;
                this->m_start_ = new_part;

                return;
            }

            if (new_item < this->GetStartNode_()->item)
            {
                new_part->next              = this->GetStartNode_();
                this->GetStartNode_()->prev = new_part;
                this->m_start_              = new_part;
                this->GetEndNode_()->next   = this->GetStartNode_();
                this->GetStartNode_()->prev = this->GetEndNode_();

                return;
            }

            Node_* const start = this->GetStartNode_();
            Node_*       temp  = this->GetStartNode_(); // -V656

            while (temp->next not_eq start)
            {
                if ((temp->item <= new_item) and (new_item <= temp->next->item))
                {
                    new_part->next   = temp->next;
                    new_part->prev   = temp;
                    temp->next->prev = new_part;
                    temp->next       = new_part;

                    return;
                }

                temp = temp->next;
            }

            temp->next     = new_part;
            new_part->prev = temp;
            new_part->next = start;
            start->prev    = new_part;

            ++this->m_item_count_;
        }
        virtual void Reverse() noexcept override final
        {
            if (this->GetItemCount() < 2U)
            {
                return;
            }

            const Node_* const start = this->GetStartNode_();
                  Node_*        temp = this->GetStartNode_(); // -V656

            while (temp->next not_eq start)
            {
                std::swap<>(temp->prev, temp->next);

                temp = temp->prev;
            }

            std::swap<>(temp->prev, temp->next);

            this->m_start_ = temp;
        }
        virtual void Print() const override final
        {
            if (this->IsEmpty())
            {
                return;
            }

            Node_* const start = this->GetStartNode_();
            Node_*       temp  = this->GetStartNode_(); // -V656

            do
            {
                this->GetOs() << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';

                temp = temp->next;
            }
            while (temp not_eq start);

            this->GetOs() << '\n';
        }


    public:
        void ClearList() noexcept
        {
            if (this->IsEmpty())
            {
                return;
            }

            const Node_* const start = this->GetStartNode_();
                  Node_*        exes = this->GetStartNode_(); // -V656
                  Node_*        temp{};

            do
            {
                temp = exes->next;

                delete exes;

                exes = temp;
            }
            while (exes not_eq start);

            this->m_start_      = nullptr;
            this->m_end_        = nullptr;
            this->m_item_count_ = 0U;
        }
        void Clear() noexcept
        {
            ClearList();

            this->m_os_ = nullptr;
        }


    protected:


    private:
    };
}

// module : private;
