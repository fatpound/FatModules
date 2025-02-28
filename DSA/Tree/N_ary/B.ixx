module;

export module FatPound.DSA.Tree.N_ary.B;

import std;

export namespace fatpound::dsa::tree::n_ary
{
    template <std::totally_ordered T, std::size_t C>
    class B final
    {
    public:
        explicit B()             = default;
        explicit B(const B&)     = delete;
        explicit B(B&&) noexcept = delete;

        auto operator = (const B&)     -> B& = delete;
        auto operator = (B&&) noexcept -> B& = delete;
        ~B() noexcept
        {
            Clear_();
        }


    public:
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
        void ListLevelorder() const
        {
            if (m_root_ == nullptr)
            {
                return;
            }

            std::queue<Node_*> queue;

            queue.push(m_root_);

            while (queue.size() > 0u)
            {
                Node_* node = queue.front();
                queue.pop();

                if (node->lesser not_eq nullptr)
                {
                    queue.push(node->lesser);
                }

                for (std::size_t i = 0u; i < node->items.size(); ++i)
                {
                    std::cout << node->items[i]->first << ' ';

                    if (node->items[i]->second not_eq nullptr)
                    {
                        queue.push(node->items[i]->second);
                    }
                }

                std::cout << '\n';
            }

            std::cout << '\n';
        }


    protected:


    private:
        struct Node_ final
        {
            explicit Node_(std::pair<T, Node_*>* new_item, Node_* new_parent = nullptr)
                :
                parent(new_parent)
            {
                if (new_item not_eq nullptr)
                {
                    items.push_back(new_item);
                }
            }
            explicit Node_(Node_* new_lesser)
                :
                lesser(new_lesser)
            {

            }

            explicit Node_() = default;

            std::vector<std::pair<T, Node_*>*> items;

            Node_* lesser = nullptr;
            Node_* parent = nullptr;
        };


    private:
        void Insert_(Node_* node, std::pair<T, Node_*>* pair, const bool add_first_time)
        {
            if (node == nullptr)
            {
                return;
            }

        label:

            if (node->items.size() == C * 2u)
            {
                if (add_first_time)
                {
                    std::size_t idx = 0u;
                    bool flag = false;

                    for (std::size_t i = 0u; i < node->items.size(); ++i)
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
                if ((node->items.size() not_eq 0u) and add_first_time)
                {
                    if ((pair->first < node->items[0u]->first) and (node->lesser not_eq nullptr))
                    {
                        node = node->lesser;
                        goto label;
                    }

                    std::size_t index = 0u;

                    for (std::size_t i = 0u; i < node->items.size(); ++i)
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

                if (node->items.size() > 1u)
                {
                    std::ranges::sort(node->items, [](const auto& pair1, const auto& pair2) -> bool { return pair1->first < pair2->first; });
                }
            }
        }
        void Overflow_(Node_* node, std::pair<T, Node_*>* pair)
        {
            std::vector<std::pair<T, Node_*>*> temp_vec;

            temp_vec.push_back(pair);

            for (std::size_t i = 0u; i < C * 2u; ++i)
            {
                temp_vec.push_back(node->items[i]);
            }

            std::ranges::sort(temp_vec, [](const auto& pair1, const auto& pair2) -> bool { return pair1->first < pair2->first; });

            std::size_t center = (C * 2u + 1u) / 2u;

            std::vector<std::pair<T, Node_*>*> temp_vec_less;
            std::vector<std::pair<T, Node_*>*> temp_vec_more;

            for (std::size_t i = 0u; i < center; ++i)
            {
                temp_vec_less.push_back(temp_vec[i]);
            }

            for (std::size_t i = center + 1u; i <= C * 2u; ++i)
            {
                temp_vec_more.push_back(temp_vec[i]);
            }

            node->items.clear();

            for (std::size_t i = 0u; i < temp_vec_less.size(); ++i)
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

            for (std::size_t i = 0u; i < temp_vec_more.size(); ++i)
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

            while (queue.size() > 0u)
            {
                Node_* node = queue.front();
                queue.pop();

                if (node->lesser not_eq nullptr)
                {
                    queue.push(node->lesser);
                }

                for (std::size_t i = 0u; i < node->items.size(); ++i)
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
        Node_* m_root_ = nullptr;

        std::size_t m_depth_ = 0u;
    };
}

module : private;
