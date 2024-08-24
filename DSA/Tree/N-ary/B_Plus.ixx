module;

export module FatPound.DSA.Tree.N_ary.B_Plus;

import std;

namespace rn = std::ranges;

export namespace fatpound::dsa::tree::n_ary
{
    template <std::totally_ordered T, std::size_t I, std::size_t S>
    class B_Plus final
    {
        using SizeType = std::size_t;
    public:
        B_Plus() = default;
        B_Plus(const B_Plus& src) = delete;
        B_Plus& operator = (const B_Plus& src) = delete;

        B_Plus(B_Plus&& src) = delete;
        B_Plus& operator = (B_Plus&& src) = delete;
        ~B_Plus() noexcept
        {
            Clear_();
        }


    public:
        bool Contains(const T& item)
        {
            if (root_ not_eq nullptr)
            {
                Node_* node = root_;

                while (node->lesser not_eq nullptr)
                {
                    std::size_t i = 0u;

                    for (; i < node->items.size(); ++i)
                    {
                        if (node->items[i]->first >= item)
                        {
                            break;
                        }
                    }

                    if (i not_eq 0u)
                    {
                        --i;
                    }

                    if (i == 0u)
                    {
                        if ((node->items[i]->first > item) or (node->items[i]->second not_eq nullptr))
                        {
                            node = node->lesser;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        node = node->items[node->items[i]->first > item ? (i - 1u) : i]->second;
                    }
                }

                for (std::size_t i = 0u; i < node->items.size(); ++i)
                {
                    if (node->items[i]->first > item)
                    {
                        break;
                    }

                    if (node->items[i]->first == item)
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        void Insert(const T& new_item)
        {
            if (Contains(new_item))
            {
                return;
            }

            if (root_ == nullptr)
            {
                root_ = new Node_(new_item, nullptr, nullptr);
                root_->lesser = new Node_(new_item, nullptr, root_);

                return;
            }

            Insert_(root_, new_item);

            item_count_++;
        }
        void ListLevelorder() const
        {
            if (root_ == nullptr)
            {
                return;
            }

            const SizeType height = GetDepth_(root_);

            for (SizeType i = 1u; i <= height; ++i)
            {
                std::cout << "Level " << i << " : ";

                ListLevelorder_(root_, i);

                std::cout << '\n';
            }

            std::cout << '\n';
        }


    protected:


    private:
        struct Node_ final
        {
            std::vector<std::pair<T, Node_*>*> items;

            Node_* lesser = nullptr;
            Node_* parent = nullptr;

            Node_() = default;

            Node_(std::vector<std::pair<T, Node_*>*>& new_items, Node_* new_lesser, Node_* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent),
                items(std::move(new_items))
            {

            }
            Node_(std::pair<T, Node_*>* new_pair, Node_* new_lesser, Node_* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent)
            {
                items.push_back(new_pair);
            }
            Node_(const T& new_item, Node_* new_lesser, Node_* new_parent)
                :
                lesser(new_lesser),
                parent(new_parent)
            {
                items.push_back(new std::pair<T, Node_*>(new_item, nullptr));
            }
        };


    private:
        auto GetDepth_(Node_* node, std::size_t depth = 0u) const -> std::size_t
        {
            if (node == nullptr)
            {
                return depth;
            }

            return GetDepth_(node->lesser, depth + 1);
        }

        void Insert_(Node_* node, T new_item)
        {
            Insert_(node, new std::pair<T, Node_*>(new_item, nullptr), nullptr, false);
        }
        void Insert_(Node_* node, std::pair<T, Node_*>* new_pair, Node_* extend_node, bool extend, bool create = true)
        {
            if (node == nullptr)
            {
                return;
            }

            if (extend)
            {
                goto extension;
            }

            std::size_t index;


        control:


            if (node->lesser == nullptr)
            {
                goto sequence;
            }

            if (new_pair->first <= node->items[0]->first)
            {
                node = node->lesser;
                goto control;
            }

            index = 0u;

            for (std::size_t i = 0u; i < node->items.size(); ++i)
            {
                if (new_pair->first > node->items[i]->first)
                {
                    index = i;
                }
            }

            if (node->items[index]->second == nullptr)
            {
                node->items[index]->second = new Node_(new_pair, nullptr, node);
                return;
            }
            else
            {
                node = node->items[index]->second;
                goto control;
            }


        sequence:


            if (node->items.size() == S * 2u)
            {
                Overflow_(node, new_pair, nullptr, false);
            }
            else
            {
                node->items.push_back(new_pair);

                if (node->items.size() > 1u)
                {
                    rn::sort(node->items, [](const auto& p1, const auto& p2) -> bool { return p1->first < p2->first; });
                }
            }

            return;


        extension:


            if (node->items.size() == I * 2u)
            {
                if (create)
                {
                    Overflow_(node, new std::pair<T, Node_*>(new_pair->first, nullptr), extend_node, true);
                }
                else
                {
                    Overflow_(node, new_pair, extend_node, true);
                }
            }
            else
            {
                if (create)
                {
                    node->items.push_back(new std::pair<T, Node_*>(new_pair->first, extend_node));
                }
                else
                {
                    node->items.push_back(new_pair);
                    extend_node->lesser = new_pair->second;
                    new_pair->second = extend_node;
                }

                if (node->items.size() > 1u)
                {
                    rn::sort(node->items, [](std::pair<T, Node_*>* p1, std::pair<T, Node_*>* p2) -> bool { return p1->first < p2->first; });
                }
            }
        }
        void Overflow_(Node_* node, std::pair<T, Node_*>* new_pair, Node_* extend_node, bool extend)
        {
            const std::size_t a = (node->lesser == nullptr ? S : I);

            node->items.push_back(new_pair);
            new_pair->second = extend_node;

            rn::sort(node->items, [](const auto& p1, const auto& p2) -> bool { return p1->first < p2->first; });

            const std::size_t center = (a * 2u + 1u) / 2u;

            Node_* new_node = new Node_();

            new_node->items.reserve(a * 2u);

            for (std::size_t i = center + 1u; i <= a * 2u; ++i)
            {
                new_node->items.push_back(node->items[i]);
            }

            if (extend)
            {
                if (node == root_)
                {
                    Node_* new_parent = new Node_();

                    new_parent->lesser = root_;
                    root_->parent = new_parent;
                    root_ = new_parent;

                    root_->items.push_back(node->items[center]);
                    new_node->lesser = node->items[center]->second;
                    node->items[center]->second = new_node;
                }
                else
                {
                    new_pair->second = extend_node;
                    new_node->lesser = node->items[center]->second;
                    node->items[center]->second->parent = new_node;

                    Insert_(node->parent, node->items[center], new_node, true, false);
                }

                extend_node->parent = new_node;
                //new_pair->second = extend_node;
                new_node->parent = node->parent;

                for (std::size_t i = 0u; i < new_node->items.size(); ++i)
                {
                    if (new_node->items[i]->second not_eq nullptr)
                    {
                        new_node->items[i]->second->parent = new_node;
                    }
                }

                node->items.resize(center);
            }
            else
            {
                new_node->parent = node->parent;
                node->items.resize(center + 1u);

                Insert_(node->parent, node->items[center], new_node, true);
            }
        }
        void ListLevelorder_(const Node_* const node, std::size_t level) const
        {
            if (node not_eq nullptr)
            {
                if (level == 1u)
                {
                    for (std::size_t i = 0u; i < node->items.size(); ++i)
                    {
                        std::cout << node->items[i]->first << ' ';
                    }
                }
                else if (level > 1u)
                {
                    ListLevelorder_(node->lesser, level - 1u);

                    for (std::size_t i = 0u; i < node->items.size(); ++i)
                    {
                        ListLevelorder_(node->items[i]->second, level - 1u);

                        std::cout << '\t';
                    }
                }
            }
            else if (level == 1u)
            {
                std::cout << "x ";
            }

            std::cout << '\t';
        }

        void Clear_()
        {
            if (root_ == nullptr)
            {
                return;
            }

            std::queue<Node_*> Q;

            Q.push(root_);

            while (Q.size() > 0u)
            {
                Node_* u = Q.front();
                Q.pop();

                if (u->lesser not_eq nullptr)
                {
                    Q.push(u->lesser);
                }

                for (std::size_t i = 0u; i < u->items.size(); ++i)
                {
                    if (u->items[i]->second not_eq nullptr)
                    {
                        Q.push(u->items[i]->second);
                    }

                    delete u->items[i];
                }

                delete u;
            }

            root_ = nullptr;
        }


    private:
        Node_* root_ = nullptr;

        std::size_t item_count_ = 0u;
    };
}