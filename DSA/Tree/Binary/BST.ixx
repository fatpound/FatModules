module;

export module FatPound.DSA.Tree.Binary.BST;

import std;

export namespace fatpound::dsa::tree::binary
{
    template <std::totally_ordered T>
    class BST
    {
    public:
        using SizeType = std::size_t;


    public:
        explicit BST() = default;
        BST(const BST& src) noexcept
        {
            if (src.m_root_ not_eq nullptr)
            {
                m_root_ = src.Clone_(src.m_root_);
                m_node_count_ = src.m_node_count_;
            }
        }
        BST(BST&& src) noexcept
        {
            if (src.m_root_ not_eq nullptr)
            {
                m_root_ = std::exchange(src.m_root_, nullptr);
                m_node_count_ = std::exchange(src.m_node_count_, 0u);
            }
        }

        auto operator = (const BST& src) noexcept -> BST&
        {
            if ((this not_eq std::addressof(src)) and (src.m_root_ not_eq nullptr))
            {
                if (m_root_ not_eq nullptr)
                {
                    Clear_();
                }

                m_root_ = src.Clone_(src.m_root_);
                m_node_count_ = src.m_node_count_;
            }

            return *this;
        }
        auto operator = (BST&& src) noexcept -> BST&
        {
            if ((this not_eq std::addressof(src)) and (src.m_root_ not_eq nullptr))
            {
                if (m_root_ not_eq nullptr)
                {
                    Clear_();
                }

                m_root_ = std::exchange(src.m_root_, nullptr);
                m_node_count_ = std::exchange(src.m_node_count_, 0u);
            }

            return *this;
        }
        virtual ~BST() noexcept
        {
            Clear_();
        }


    public:
        [[nodiscard]]
        virtual auto GetTotalNodeCount() const -> SizeType final
        {
            return m_node_count_;
        }

        virtual auto Contains(const T item) const -> bool final
        {
            return Find_(m_root_, item) not_eq nullptr;
        }

        virtual void ListPreorder()         const final
        {
            ListPreorder_(m_root_);

            std::cout << '\n';
        }
        virtual void ListPreorderReverse()  const final
        {
            ListPreorderReverse_(m_root_);

            std::cout << '\n';
        }
        virtual void ListInorder()          const final
        {
            ListInorder_(m_root_);

            std::cout << '\n';
        }
        virtual void ListInorderReverse()   const final
        {
            ListInorderReverse_(m_root_);

            std::cout << '\n';
        }
        virtual void ListPostorder()        const final
        {
            ListPostorder_(m_root_);

            std::cout << '\n';
        }
        virtual void ListPostorderReverse() const final
        {
            ListPostorderReverse_(m_root_);

            std::cout << '\n';
        }
        virtual void ListLeaves()           const final
        {
            ListLeaves_(m_root_);

            std::cout << '\n';
        }
        virtual void ListLeavesReverse()    const final
        {
            ListLeavesReverse_(m_root_);

            std::cout << '\n';
        }
        virtual void ListLevelorder()       const final
        {
            const auto height = GetDepth_(m_root_, 0);

            for (SizeType i = 1u; i <= height; ++i)
            {
                std::cout << "Level " << i << " : ";

                ListLevelorder_(m_root_, i);

                std::cout << '\n';
            }

            std::cout << '\n';
        }

        virtual void Mirror() final
        {
            Mirror_(m_root_);
        }

        virtual void Insert(const T new_item)
        {
            [[maybe_unused]] Node_* new_node = Insert_(nullptr, m_root_, new_item);

            if (m_root_ == nullptr) [[unlikely]]
            {
                m_root_ = new_node;
            }

            ++m_node_count_;
        }
        virtual void Delete(const T old_item)
        {
            Node_* node = Find_(m_root_, old_item);

            if (node not_eq nullptr)
            {
                static_cast<void>(Delete_(node));
            }
        }


    protected:
        struct Node_ final
        {
            Node_(T new_item, Node_* new_parent)
                :
                parent(new_parent),
                item(new_item)
            {

            }

            Node_* left   = nullptr;
            Node_* right  = nullptr;
            Node_* parent = nullptr;

            T item;
        };


    protected:
        virtual auto Insert_(Node_* __restrict parent, Node_* __restrict node, const T& new_item) -> Node_*
        {
            if (node == nullptr)
            {
                return new Node_(new_item, parent);
            }

            if (new_item < node->item)
            {
                node->left = Insert_(node, node->left, new_item);
            }
            else if (new_item > node->item)
            {
                node->right = Insert_(node, node->right, new_item);
            }

            return node;
        }
        virtual auto Clone_(Node_* node) const -> Node_* final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            auto* const new_node = new Node_(node->item, node->parent);

            new_node->left  = Clone_(node->left);
            new_node->right = Clone_(node->right);

            return new_node;
        }
        virtual auto Find_(Node_* node, const T& item) const -> Node_* final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            if (node->item == item)
            {
                return node;
            }

            Node_* left_address = Find_(node->left, item);

            if (left_address not_eq nullptr)
            {
                return left_address;
            }

            Node_* right_address = Find_(node->right, item);

            if (right_address not_eq nullptr)
            {
                return right_address;
            }

            return nullptr;
        }
        virtual auto Delete_(Node_* node) -> Node_* final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            Node_* latest = nullptr;

            if (node->parent not_eq nullptr)
            {
                if (node->right not_eq nullptr)
                {
                    Node_* leftmost = GetMin_(node->right);

                    if (leftmost not_eq nullptr)
                    {
                        leftmost->left = node->left;

                        if (node->left not_eq nullptr)
                        {
                            node->left->parent = leftmost;
                        }
                    }
                    else
                    {
                        node->right->left = node->left;

                        if (node->left not_eq nullptr)
                        {
                            node->left->parent = node->right;
                        }
                    }

                    node->right->parent = node->parent;
                    latest = node->right;
                }
                else
                {
                    if (node->left not_eq nullptr)
                    {
                        node->left->parent = node->parent;
                        latest = node->left;
                    }
                    else
                    {
                        latest = node->parent;
                    }
                }

                if (node->parent->item < node->item)
                {
                    node->parent->right = node->right;
                }
                else
                {
                    node->parent->left = node->right;
                }
            }
            else
            {
                m_root_ = node->right;
            }

            delete node;

            return latest;
        }

        virtual auto GetMin_(Node_* node) -> Node_* final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            while (node->left not_eq nullptr)
            {
                node = node->left;
            }

            return node;
        }
        virtual auto GetMax_(Node_* node) -> Node_* final
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            while (node->right not_eq nullptr)
            {
                node = node->right;
            }

            return node;
        }
        virtual auto GetInorderSuccessor_(Node_* node) -> Node_* final
        {
            if (node->right not_eq nullptr)
            {
                return GetMin_(node->right);
            }

            // parent_of_node
            Node_* prnt = node->parent;

            while ((prnt not_eq nullptr) and (prnt->right == node))
            {
                node = prnt;
                prnt = prnt->parent;
            }

            return prnt;
        }

        virtual auto GetDepth_      (Node_* node, SizeType depth) const -> SizeType final
        {
            if (node == nullptr)
            {
                return depth;
            }

            const auto&  left_val = GetDepth_(node->left,  depth + 1);
            const auto& right_val = GetDepth_(node->right, depth + 1);

            return std::max(left_val, right_val);
        }
        virtual auto GetDepthLeft_  (Node_* node, SizeType depth) const -> SizeType final
        {
            return node
                ? GetDepthLeft_(node->left, depth + 1)
                : depth
                ;
        }
        virtual auto GetDepthRight_ (Node_* node, SizeType depth) const -> SizeType final
        {
            return node
                ? GetDepthLeft_(node->right, depth + 1)
                : depth
                ;
        }
        virtual auto GetNodeCount_  (Node_* node) const -> SizeType final
        {
            if (node == nullptr)
            {
                return 0;
            }

            const auto&  left_val = GetNodeCount_(node->left);
            const auto& right_val = GetNodeCount_(node->right);

            return 1 + left_val + right_val;
        }

        virtual void Mirror_(Node_* node) final
        {
            if (node not_eq nullptr)
            {
                std::swap(node->left, node->right);

                Mirror_(node->left);
                Mirror_(node->right);
            }
        }

        virtual void ListPreorder_         (const Node_* const node) const noexcept final
        {
            if (node not_eq nullptr)
            {
                std::cout << node->item << ' ';

                ListPreorder_(node->left);
                ListPreorder_(node->right);
            }
        }
        virtual void ListPreorderReverse_  (const Node_* const node) const noexcept final
        {
            if (node not_eq nullptr)
            {
                std::cout << node->item << ' ';

                ListPreorderReverse_(node->right);
                ListPreorderReverse_(node->left);
            }
        }
        virtual void ListInorder_          (const Node_* const node) const noexcept final
        {
            if (node not_eq nullptr)
            {
                ListInorder_(node->left);

                std::cout << node->item << ' ';

                ListInorder_(node->right);
            }
        }
        virtual void ListInorderReverse_   (const Node_* const node) const noexcept final
        {
            if (node not_eq nullptr)
            {
                ListInorderReverse_(node->right);

                std::cout << node->item << ' ';

                ListInorderReverse_(node->left);
            }
        }
        virtual void ListPostorder_        (const Node_* const node) const noexcept final
        {
            if (node not_eq nullptr)
            {
                ListPostorder_(node->left);
                ListPostorder_(node->right);

                std::cout << node->item << ' ';
            }
        }
        virtual void ListPostorderReverse_ (const Node_* const node) const noexcept final
        {
            if (node not_eq nullptr)
            {
                ListPostorderReverse_(node->right);
                ListPostorderReverse_(node->left);

                std::cout << node->item << ' ';
            }
        }
        virtual void ListLeaves_           (const Node_* const node) const noexcept final
        {
            if (node not_eq nullptr)
            {
                if ((node->left == nullptr) and (node->right == nullptr))
                {
                    std::cout << node->item << ' ';

                    return;
                }

                ListLeaves_(m_root_->left);
                ListLeaves_(m_root_->right);
            }
        }
        virtual void ListLeavesReverse_    (const Node_* const node) const noexcept final
        {
            if (node not_eq nullptr)
            {
                if ((node->left == nullptr) and (node->right == nullptr))
                {
                    std::cout << node->item << ' ';

                    return;
                }

                ListLeavesReverse_(m_root_->right);
                ListLeavesReverse_(m_root_->left);
            }
        }
        virtual void ListLevelorder_       (const Node_* const node, SizeType level) const noexcept final
        {
            if (node not_eq nullptr)
            {
                if (level == 1)
                {
                    std::cout << node->item << ' ';
                }
                else if (level > 1)
                {
                    ListLevelorder_(node->left,  level - 1);
                    ListLevelorder_(node->right, level - 1);
                }
            }
            else if (level == 1)
            {
                std::cout << "x ";
            }
        }


    protected:
        Node_* m_root_ = nullptr;

        SizeType m_node_count_ = 0u;


    private:
        virtual void Clear_() noexcept final
        {
            DeleteSubTree_(m_root_);

            m_root_ = nullptr;
            m_node_count_ = 0u;
        }
        virtual void DeleteSubTree_(Node_* root) noexcept final
        {
            if (root not_eq nullptr)
            {
                DeleteSubTree_(root->left);
                DeleteSubTree_(root->right);

                delete root;
            }
        }
    };
}

module : private;