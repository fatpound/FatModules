module;

export module FatPound.DSA.Tree.Binary.BST;

import std;

export namespace fatpound::dsa::tree::binary
{
    template <std::totally_ordered T>
    class BST
    {
    public:
        using Size_t = std::size_t;


    public:
        explicit BST() = default;
        BST(const BST& src) noexcept
        {
            if (src.m_pRoot_ not_eq nullptr)
            {
                m_pRoot_ = src.Clone_(src.m_pRoot_);
                m_node_count_ = src.m_node_count_;
            }
        }
        BST(BST&& src) noexcept
        {
            if (src.m_pRoot_ not_eq nullptr)
            {
                m_pRoot_ = std::exchange(src.m_pRoot_, nullptr);
                m_node_count_ = std::exchange(src.m_node_count_, 0U);
            }
        }

        auto operator = (const BST& src) noexcept -> BST&
        {
            if ((this not_eq std::addressof(src)) and (src.m_pRoot_ not_eq nullptr))
            {
                if (m_pRoot_ not_eq nullptr)
                {
                    Clear_();
                }

                m_pRoot_ = src.Clone_(src.m_pRoot_);
                m_node_count_ = src.m_node_count_;
            }

            return *this;
        }
        auto operator = (BST&& src) noexcept -> BST&
        {
            if ((this not_eq std::addressof(src)) and (src.m_pRoot_ not_eq nullptr))
            {
                if (m_pRoot_ not_eq nullptr)
                {
                    Clear_();
                }

                m_pRoot_ = std::exchange(src.m_pRoot_, nullptr);
                m_node_count_ = std::exchange(src.m_node_count_, 0U);
            }

            return *this;
        }
        virtual ~BST() noexcept
        {
            Clear_();
        }


    public:
        // NOLINTBEGIN(clang-analyzer-cplusplus.NewDeleteLeaks)
        virtual void Insert(const T& new_item)
        {
            [[maybe_unused]] Node_* new_node = Insert_(nullptr, m_pRoot_, new_item);

            if (m_pRoot_ == nullptr) [[unlikely]]
            {
                m_pRoot_ = new_node;
            }

            ++m_node_count_;
        }
        // NOLINTEND(clang-analyzer-cplusplus.NewDeleteLeaks)

        virtual void Delete(const T& old_item) noexcept
        {
            Node_* node = Find_(m_pRoot_, old_item);

            if (node not_eq nullptr)
            {
                static_cast<void>(Delete_(node));
            }
        }


    public:
        [[nodiscard]]
        auto GetTotalNodeCount() const -> Size_t
        {
            return m_node_count_;
        }

        [[nodiscard]]
        auto Contains(const T& item) const -> bool
        {
            return Find_(m_pRoot_, item) not_eq nullptr;
        }

        void ListPreorder         () const
        {
            ListPreorder_(m_pRoot_);

            std::cout << '\n';
        }
        void ListPreorderReverse  () const
        {
            ListPreorderReverse_(m_pRoot_);

            std::cout << '\n';
        }
        void ListInorder          () const
        {
            ListInorder_(m_pRoot_);

            std::cout << '\n';
        }
        void ListInorderReverse   () const
        {
            ListInorderReverse_(m_pRoot_);

            std::cout << '\n';
        }
        void ListPostorder        () const
        {
            ListPostorder_(m_pRoot_);

            std::cout << '\n';
        }
        void ListPostorderReverse () const
        {
            ListPostorderReverse_(m_pRoot_);

            std::cout << '\n';
        }
        void ListLeaves           () const
        {
            ListLeaves_(m_pRoot_);

            std::cout << '\n';
        }
        void ListLeavesReverse    () const
        {
            ListLeavesReverse_(m_pRoot_);

            std::cout << '\n';
        }
        void ListLevelorder       () const
        {
            const auto height = GetDepth_(m_pRoot_, 0);

            for (Size_t i = 1U; i <= height; ++i)
            {
                std::cout << "Level " << i << " : ";

                ListLevelorder_(m_pRoot_, i);

                std::cout << '\n';
            }

            std::cout << '\n';
        }

        void Mirror()
        {
            Mirror_(m_pRoot_);
        }


    protected:
        struct alignas(32) Node_ final
        {
            Node_(const T new_item, Node_* const new_parent) noexcept
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
        virtual auto Insert_(Node_* const __restrict parent, Node_* const __restrict node, const T& new_item) -> Node_*
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


    protected:
        auto Clone_ (const Node_* const node)          const -> Node_*
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
        auto Find_  (Node_* const node, const T& item) const noexcept -> Node_*
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
        auto Delete_(Node_* node) noexcept -> Node_*
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
                m_pRoot_ = node->right;
            }

            delete node;

            return latest;
        }
        auto GetMin_(Node_* node) noexcept -> Node_*
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
        auto GetMax_(Node_* node) noexcept -> Node_*
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
        auto GetDepth_     (const Node_* const node, const Size_t depth) const noexcept -> Size_t
        {
            if (node == nullptr)
            {
                return depth;
            }

            const auto&  left_val = GetDepth_(node->left,  depth + 1);
            const auto& right_val = GetDepth_(node->right, depth + 1);

            return std::max(left_val, right_val);
        }
        auto GetDepthLeft_ (const Node_* const node, const Size_t depth) const noexcept -> Size_t
        {
            return node
                ? GetDepthLeft_(node->left, depth + 1)
                : depth
                ;
        }
        auto GetDepthRight_(const Node_* const node, const Size_t depth) const noexcept -> Size_t
        {
            return node
                ? GetDepthLeft_(node->right, depth + 1)
                : depth
                ;
        }
        auto GetNodeCount_ (const Node_* const node) const noexcept -> Size_t
        {
            if (node == nullptr)
            {
                return 0;
            }

            const auto&  left_val = GetNodeCount_(node->left);
            const auto& right_val = GetNodeCount_(node->right);

            return 1 + left_val + right_val;
        }
        auto GetInorderSuccessor_(Node_* node) noexcept -> Node_*
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

        void Mirror_(Node_* const node)
        {
            if (node not_eq nullptr)
            {
                std::swap<>(node->left, node->right);

                Mirror_(node->left);
                Mirror_(node->right);
            }
        }

        void ListPreorder_         (const Node_* const node)                 const
        {
            if (node not_eq nullptr)
            {
                std::cout << node->item << ' ';

                ListPreorder_(node->left);
                ListPreorder_(node->right);
            }
        }
        void ListPreorderReverse_  (const Node_* const node)                 const
        {
            if (node not_eq nullptr)
            {
                std::cout << node->item << ' ';

                ListPreorderReverse_(node->right);
                ListPreorderReverse_(node->left);
            }
        }
        void ListInorder_          (const Node_* const node)                 const
        {
            if (node not_eq nullptr)
            {
                ListInorder_(node->left);

                std::cout << node->item << ' ';

                ListInorder_(node->right);
            }
        }
        void ListInorderReverse_   (const Node_* const node)                 const
        {
            if (node not_eq nullptr)
            {
                ListInorderReverse_(node->right);

                std::cout << node->item << ' ';

                ListInorderReverse_(node->left);
            }
        }
        void ListPostorder_        (const Node_* const node)                 const
        {
            if (node not_eq nullptr)
            {
                ListPostorder_(node->left);
                ListPostorder_(node->right);

                std::cout << node->item << ' ';
            }
        }
        void ListPostorderReverse_ (const Node_* const node)                 const
        {
            if (node not_eq nullptr)
            {
                ListPostorderReverse_(node->right);
                ListPostorderReverse_(node->left);

                std::cout << node->item << ' ';
            }
        }
        void ListLeaves_           (const Node_* const node)                 const
        {
            if (node not_eq nullptr)
            {
                if ((node->left == nullptr) and (node->right == nullptr))
                {
                    std::cout << node->item << ' ';

                    return;
                }

                ListLeaves_(m_pRoot_->left);
                ListLeaves_(m_pRoot_->right);
            }
        }
        void ListLeavesReverse_    (const Node_* const node)                 const
        {
            if (node not_eq nullptr)
            {
                if ((node->left == nullptr) and (node->right == nullptr))
                {
                    std::cout << node->item << ' ';

                    return;
                }

                ListLeavesReverse_(m_pRoot_->right);
                ListLeavesReverse_(m_pRoot_->left);
            }
        }
        void ListLevelorder_       (const Node_* const node, Size_t level) const
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
        Node_* m_pRoot_{};

        Size_t m_node_count_{};


    private:
        void Clear_() noexcept
        {
            DeleteSubTree_(m_pRoot_);

            m_pRoot_ = nullptr;
            m_node_count_ = 0U;
        }
        void DeleteSubTree_(Node_* const root) noexcept
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
