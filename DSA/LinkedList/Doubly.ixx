module;

#include <_macros/Compiler.hxx>

export module FatPound.DSA.LinkedList.Doubly;

import std;

export namespace fatpound::dsa::linkedlist
{
    template <std::totally_ordered T>
    class Doubly
    {
    public:
        explicit Doubly(std::ostream& os = std::cout)
            :
            m_os_(&os)
        {

        }

        explicit Doubly(const Doubly&) = delete;
        Doubly(Doubly&& src) noexcept
            :
            m_start_(std::exchange<>(src.m_start_, nullptr)),
            m_end_(std::exchange<>(src.m_end_, nullptr)),
            m_item_count_(std::exchange<>(src.m_item_count_, 0U)),
            m_os_(std::exchange<>(src.m_os_, nullptr))
        {

        }

        auto operator = (const Doubly&) -> Doubly& = delete;
        auto operator = (Doubly&& src) noexcept -> Doubly&
        {
            if (this not_eq std::addressof<>(src) and typeid(src) == typeid(*this))
            {
                if (src.IsNotEmpty())
                {
                    ClearList();

                    m_start_      = std::exchange<>(src.m_start_, nullptr);
                    m_end_        = std::exchange<>(src.m_end_,   nullptr);
                    m_item_count_ = std::exchange<>(src.m_item_count_, 0U);
                }

                m_os_ = std::exchange<>(src.m_os_, nullptr);
            }

            return *this;
        }
        virtual ~Doubly() noexcept
        {
            if (not m_cleared_from_derived_dtor_)
            {
                Clear();
            }
        }


    public:
        [[nodiscard]] virtual auto Contains(const T& item) const noexcept -> bool final
        {
            return Find_(item) not_eq nullptr;
        }

        virtual void Insert(const T& new_item)
        {
            auto* const new_part = new Node_(new_item);

            if (IsEmpty())
            {
                m_start_ = new_part;
                m_end_   = new_part;

                return;
            }

            GetEndNode_()->next = new_part;
            new_part->prev      = GetEndNode_();
            m_end_              = new_part;

            ++m_item_count_;
        }
        virtual void InsertAtFirst_GreaterEq(const T& new_item)
        {
            auto* const new_part = new Node_(new_item);

            if (IsEmpty())
            {
                m_start_ = new_part;

                return;
            }

            if (new_item < GetStartNode_()->item)
            {
                new_part->next        = GetStartNode_();
                GetStartNode_()->prev = new_part;
                m_start_              = new_part;

                return;
            }

            Node_* temp = GetStartNode_();

            while (temp->next not_eq nullptr)
            {
                if (temp->item <= new_item && new_item <= temp->next->item)
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

            ++m_item_count_;
        }
        virtual void Reverse() noexcept
        {
            if (GetItemCount() < 2U)
            {
                return;
            }

            Node_* temp = GetStartNode_();

            while (temp->next not_eq nullptr)
            {
                std::swap<>(temp->prev, temp->next);
                temp = temp->prev;
            }

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 26822)
#endif
            std::swap<>(temp->prev, temp->next);

#ifdef _MSC_VER
#pragma warning (pop)
#endif

            m_start_ = temp;
        }
        virtual void Print() const
        {
            for (Node_* temp = GetStartNode_(); temp not_eq nullptr; temp = temp->next)
            {
                GetOs() << temp->prev << '\t' << temp << '\t' << temp->item << '\t' << temp->next << '\n';
            }

            GetOs() << '\n';
        }


    public:
        [[nodiscard]] FATLIB_FORCEINLINE auto GetOs        () const noexcept -> std::ostream&
        {
            return *m_os_;
        }
        [[nodiscard]] FATLIB_FORCEINLINE auto GetItemCount () const noexcept -> std::size_t
        {
            return m_item_count_;
        }
        [[nodiscard]] FATLIB_FORCEINLINE auto IsEmpty      () const noexcept -> bool
        {
            return m_item_count_ == 0U;
        }
        [[nodiscard]] FATLIB_FORCEINLINE auto IsNotEmpty   () const noexcept -> bool
        {
            return not IsEmpty();
        }

        void SetOstream(std::ostream& os) noexcept
        {
            m_os_ = &os;
        }
        void ClearList() noexcept
        {
            if (IsEmpty())
            {
                return;
            }

            Node_* exes = GetStartNode_();
            Node_* temp{};

            do
            {
                temp = exes->next;

                delete exes;

                exes = temp;
            }
            while (exes not_eq nullptr);

            m_start_      = nullptr;
            m_end_        = nullptr;
            m_item_count_ = 0U;
        }
        void Clear() noexcept
        {
            ClearList();

            m_os_ = nullptr;
        }


    protected:
        struct alignas(32) Node_ final
        {
            explicit Node_(const T& new_item) noexcept
                :
                item{ new_item }
            {

            }

            Node_*   prev{};
            Node_*   next{};
            T        item;
        };


    protected:
        [[nodiscard]] virtual auto Find_(const T& item) const noexcept -> Node_* final
        {
            if (IsEmpty())
            {
                return nullptr;
            }

            Node_* temp = GetStartNode_();

            for (std::size_t i{}; i < GetItemCount(); ++i)
            {
                if (temp->item == item)
                {
                    return temp;
                }

                temp = temp->next;
            }

            return nullptr; // same as temp
        }


    protected:
        [[nodiscard]] FATLIB_FORCEINLINE auto GetStartNode_ () const noexcept -> Node_*
        {
            return m_start_;
        }
        [[nodiscard]] FATLIB_FORCEINLINE auto GetEndNode_   () const noexcept -> Node_*
        {
            return m_end_;
        }


    protected:
        Node_*          m_start_{};
        Node_*          m_end_{};
        std::size_t     m_item_count_{};

        std::ostream*   m_os_{};

        bool            m_cleared_from_derived_dtor_{};


    private:
    };
}

// module : private;
