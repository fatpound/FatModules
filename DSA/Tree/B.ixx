module;

#include <_macros/Compiler.hxx>

export module FatPound.DSA.Tree.B;

import std;

export namespace fatpound::dsa::tree
{
    template <std::totally_ordered T, std::size_t C>
    class B final
    {
    public:
        explicit B(std::ostream& os = std::cout)
            :
            m_os_(&os)
        {

        }

        explicit B(const B&)     = delete;
        explicit B(B&&) noexcept = delete;

        auto operator = (const B&)     -> B& = delete;
        auto operator = (B&&) noexcept -> B& = delete;
        ~B() noexcept(false)
        {
            Clear_();
        }


    public:
        [[nodiscard]] FATLIB_FORCEINLINE auto GetOs() const noexcept -> std::ostream&
        {
            return *m_os_;
        }

        // NOLINTBEGIN(clang-analyzer-cplusplus.NewDeleteLeaks)
        void Insert(const T& new_item)
        {
            auto new_pair = new std::pair<T, Node_*>(new_item, nullptr);

            if (m_root_ == nullptr)
            {
                m_root_ = new Node_(new_pair);

                ++m_depth_;

                return;
            }

            Insert_(m_root_, new_pair, true);
        }
        // NOLINTEND(clang-analyzer-cplusplus.NewDeleteLeaks)

        void SetOstream(std::ostream& os)
        {
            m_os_ = &os;
        }
        void ListLevelorder() const
        {
            if (m_root_ == nullptr)
            {
                return;
            }

            std::queue<Node_*> queue;
            queue.push(m_root_);

            while (not queue.empty())
            {
                auto* node = queue.front();
                queue.pop();

                if (node->lesser not_eq nullptr)
                {
                    queue.push(node->lesser);
                }

                for (std::size_t i{}; i < node->items.size(); ++i)
                {
                    GetOs() << node->items[i]->first << ' ';

                    if (node->items[i]->second not_eq nullptr)
                    {
                        queue.push(node->items[i]->second);
                    }
                }

                GetOs() << '\n';
            }

            GetOs() << '\n';
        }


    protected:


    private:
        struct alignas(64) Node_ final
        {
            explicit Node_(std::pair<T, Node_*>* const new_item, Node_* const new_parent = nullptr)
                :
                parent(new_parent)
            {
                if (new_item not_eq nullptr)
                {
                    items.push_back(new_item);
                }
            }
            explicit Node_(Node_* new_lesser) noexcept
                :
                lesser(new_lesser)
            {

            }

            explicit Node_() = default;

            std::vector<std::pair<T, Node_*>*>   items;
            Node_*                               lesser{};
            Node_*                               parent{};
        };


    private:
        // NOLINTBEGIN(readability-function-cognitive-complexity)
        void Insert_(Node_* node, std::pair<T, Node_*>* pair, const bool add_first_time)
        {
            if (node == nullptr)
            {
                return;
            }

        label:

            if (node->items.size() == C * 2U)
            {
                if (add_first_time)
                {
                    std::size_t idx{};
                    bool flag{};

                    for (std::size_t i{}; i < node->items.size(); ++i)
                    {
                        if ((pair->first > node->items[i]->first) and (node->items[i]->second not_eq nullptr))
                        {
                            if (not flag)
                            {
                                flag = true;
                            }

                            idx = i;
                        }
                    }

                    if (flag)
                    {
                        Insert_(node->items[idx]->second, pair, true);
                    }
                    else
                    {
                        Overflow_(node, pair);
                    }
                }
                else
                {
                    Overflow_(node, pair);
                }
            }
            else
            {
                if ((node->items.size() not_eq 0U) and add_first_time)
                {
                    if ((pair->first < node->items[0U]->first) and (node->lesser not_eq nullptr))
                    {
                        node = node->lesser;
                        goto label;
                    }

                    std::size_t index{};

                    for (std::size_t i{}; i < node->items.size(); ++i)
                    {
                        if (pair->first > node->items[i]->first)
                        {
                            index = i;
                        }
                    }

                    if (node->items[index]->second not_eq nullptr)
                    {
                        node = node->items[index]->second;
                        goto label;
                    }
                }

                node->items.push_back(pair);

                if (node->items.size() > 1U)
                {
                    std::ranges::sort(node->items, [](const auto& pair1, const auto& pair2) -> bool { return pair1->first < pair2->first; });
                }
            }
        }
        // NOLINTEND(readability-function-cognitive-complexity)

        void Overflow_(Node_* node, std::pair<T, Node_*>* pair)
        {
            std::vector<std::pair<T, Node_*>*> temp_vec;

            temp_vec.push_back(pair);

            for (std::size_t i{}; i < C * 2U; ++i)
            {
                temp_vec.push_back(node->items[i]);
            }

            std::ranges::sort(temp_vec, [](const auto& pair1, const auto& pair2) -> bool { return pair1->first < pair2->first; });

            constexpr auto center = (C * 2U + 1U) / 2U;

            std::vector<std::pair<T, Node_*>*> temp_vec_less(center);
            std::vector<std::pair<T, Node_*>*> temp_vec_more((C * 2U) - center + 1U);

            for (std::size_t i{}; i < center; ++i)
            {
                temp_vec_less.push_back(temp_vec[i]);
            }

            for (std::size_t i = center + 1U; i <= C * 2U; ++i)
            {
                temp_vec_more.push_back(temp_vec[i]);
            }

            node->items.clear();

            for (std::size_t i{}; i < temp_vec_less.size(); ++i)
            {
                node->items.push_back(temp_vec_less[i]);
            }

            if (node == m_root_)
            {
                node->parent = new Node_(node);
                m_root_ = node->parent;

                ++m_depth_;
            }

            Insert_(node->parent, temp_vec[center], false);

            auto* const new_node = new Node_;
            new_node->parent = node->parent;

            for (std::size_t i{}; i < temp_vec_more.size(); ++i)
            {
                new_node->items.push_back(temp_vec_more[i]);
            }

            new_node->lesser = temp_vec[center]->second;
            temp_vec[center]->second = new_node;
        }
        void Clear_()
        {
            if (m_root_ == nullptr)
            {
                return;
            }

            std::queue<Node_*> queue;

            queue.push(m_root_);

            while (not queue.empty())
            {
                auto* node = queue.front();
                queue.pop();

                if (node->lesser not_eq nullptr)
                {
                    queue.push(node->lesser);
                }

                for (std::size_t i{}; i < node->items.size(); ++i)
                {
                    if (node->items[i]->second not_eq nullptr)
                    {
                        queue.push(node->items[i]->second);
                    }

                    delete node->items[i];
                }

                delete node;
            }

            m_root_ = nullptr;
        }


    private:
        Node_*          m_root_{};
        std::size_t     m_depth_{};

        std::ostream*   m_os_;
    };
}

module : private;
