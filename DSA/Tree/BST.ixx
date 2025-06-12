module;

#include <FatMacros.hxx>

export module FatPound.DSA.Tree.BST;

import std;

export namespace fatpound::dsa::tree
{
    template <std::totally_ordered T>
    class BST
    {
    public:
        using Size_t = std::size_t;


    public:
        explicit BST(std::ostream& os = std::cout)
            :
            m_os_(&os)
        {

        }

        BST(const BST& src) noexcept
            :
            m_pRoot_(src.Clone_(src.GetRoot_())),
            m_node_count_(src.GetNodeCount()),
            m_os_(src.GetOs())
        {

        }
        BST(BST&& src) noexcept
            :
            m_pRoot_(std::exchange<>(src.m_pRoot_, nullptr)),
            m_node_count_(std::exchange<>(src.m_node_count_, 0U)),
            m_os_(std::exchange<>(src.m_os_, nullptr))
        {
            
        }

        auto operator = (const BST& src) noexcept -> BST&
        {
            if (this not_eq std::addressof<>(src))
            {
                if (src.GetRoot_() not_eq nullptr)
                {
                    ClearTree();

                    m_pRoot_      = src.Clone_(src.GetRoot_());
                    m_node_count_ = src.GetNodeCount();
                }

                m_os_ = src.GetOs();
            }

            return *this;
        }
        auto operator = (BST&& src) noexcept -> BST&
        {
            if (this not_eq std::addressof<>(src))
            {
                if (src.GetRoot_() not_eq nullptr)
                {
                    ClearTree();

                    m_pRoot_      = std::exchange<>(src.m_pRoot_, nullptr);
                    m_node_count_ = std::exchange<>(src.m_node_count_, 0U);
                }

                m_os_ = std::exchange<>(src.m_os_, nullptr);
            }


            return *this;
        }
        virtual ~BST() noexcept
        {
            Clear();
        }


    public:
        // NOLINTBEGIN(clang-analyzer-cplusplus.NewDeleteLeaks)
        virtual void Insert(const T& new_item)
        {
            [[maybe_unused]] Node_* new_node = Insert_(nullptr, GetRoot_(), new_item);

            if (GetRoot_() == nullptr)
            {
                m_pRoot_ = new_node;
            }

            ++m_node_count_;
        }
        // NOLINTEND(clang-analyzer-cplusplus.NewDeleteLeaks)

        virtual void Delete(const T& old_item) noexcept
        {
            if (auto* node = Find_(GetRoot_(), old_item); node not_eq nullptr)
            {
                static_cast<void>(Delete_(node));
            }
        }


    public:
        [[nodiscard]] FAT_FORCEINLINE auto GetOs        () const noexcept -> std::ostream&
        {
            return *m_os_;
        }
        [[nodiscard]] FAT_FORCEINLINE auto GetNodeCount () const -> Size_t
        {
            return m_node_count_;
        }

        [[nodiscard]] auto Contains(const T& item) const noexcept -> bool
        {
            return Find_(GetRoot_(), item) not_eq nullptr;
        }

        void ListPreorder         () const
        {
            ListPreorder_(GetRoot_());

            GetOs() << '\n';
        }
        void ListPreorderReverse  () const
        {
            ListPreorderReverse_(GetRoot_());

            GetOs() << '\n';
        }
        void ListInorder          () const
        {
            ListInorder_(GetRoot_());

            GetOs() << '\n';
        }
        void ListInorderReverse   () const
        {
            ListInorderReverse_(GetRoot_());

            GetOs() << '\n';
        }
        void ListPostorder        () const
        {
            ListPostorder_(GetRoot_());

            GetOs() << '\n';
        }
        void ListPostorderReverse () const
        {
            ListPostorderReverse_(GetRoot_());

            GetOs() << '\n';
        }
        void ListLeaves           () const
        {
            ListLeaves_(GetRoot_());

            GetOs() << '\n';
        }
        void ListLeavesReverse    () const
        {
            ListLeavesReverse_(GetRoot_());

            GetOs() << '\n';
        }
        void ListLevelorder       () const
        {
            const auto height = GetDepth_(GetRoot_(), 0);

            for (Size_t i = 1U; i <= height; ++i)
            {
                GetOs() << "Level " << i << " : ";

                ListLevelorder_(GetRoot_(), i);

                GetOs() << '\n';
            }

            GetOs() << '\n';
        }

        void SetOstream(std::ostream& os) noexcept
        {
            m_os_ = &os;
        }
        void Mirror()
        {
            Mirror_(GetRoot_());
        }
        void ClearTree()
        {
            DeleteSubTree_(GetRoot_());

            m_pRoot_      = nullptr;
            m_node_count_ = 0U;
        }
        void Clear()
        {
            ClearTree();

            m_os_ = nullptr;
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

            Node_* left{};
            Node_* right{};
            Node_* parent{};

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
        FAT_FORCEINLINE auto GetRoot_() const noexcept -> Node_*
        {
            return m_pRoot_;
        }

        auto Clone_                 (const Node_* const node                    ) const -> Node_*
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
        auto Find_                  (      Node_* const node, const T& item     ) const noexcept -> Node_*
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
        auto Delete_                (      Node_*       node                    ) noexcept -> Node_*
        {
            if (node == nullptr)
            {
                return nullptr;
            }

            Node_* latest{};

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
        auto GetMin_                (      Node_*       node                    ) noexcept -> Node_*
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
        auto GetMax_                (      Node_*       node                    ) noexcept -> Node_*
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
        auto GetDepth_              (const Node_* const node, const Size_t depth) const noexcept -> Size_t
        {
            if (node == nullptr)
            {
                return depth;
            }

            const auto&  left_val = GetDepth_(node->left,  depth + 1);
            const auto& right_val = GetDepth_(node->right, depth + 1);

            return std::max(left_val, right_val);
        }
        auto GetDepthLeft_          (const Node_* const node, const Size_t depth) const noexcept -> Size_t
        {
            return node
                ? GetDepthLeft_(node->left, depth + 1)
                : depth
                ;
        }
        auto GetDepthRight_         (const Node_* const node, const Size_t depth) const noexcept -> Size_t
        {
            return node
                ? GetDepthLeft_(node->right, depth + 1)
                : depth
                ;
        }
        auto GetNodeCountOfSubtree_ (const Node_* const node                    ) const noexcept -> Size_t
        {
            if (node == nullptr)
            {
                return 0;
            }

            const auto&  left_val = GetNodeCountOfSubtree_(node->left);
            const auto& right_val = GetNodeCountOfSubtree_(node->right);

            return 1 + left_val + right_val;
        }
        auto GetInorderSuccessor_   (      Node_*       node                    ) noexcept -> Node_*
        {
            if (node == nullptr)
            {
                return nullptr;
            }

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

        void ListPreorder_          (const Node_* const node                    ) const
        {
            if (node not_eq nullptr)
            {
                GetOs() << node->item << ' ';

                ListPreorder_(node->left);
                ListPreorder_(node->right);
            }
        }
        void ListPreorderReverse_   (const Node_* const node                    ) const
        {
            if (node not_eq nullptr)
            {
                GetOs() << node->item << ' ';

                ListPreorderReverse_(node->right);
                ListPreorderReverse_(node->left);
            }
        }
        void ListInorder_           (const Node_* const node                    ) const
        {
            if (node not_eq nullptr)
            {
                ListInorder_(node->left);

                GetOs() << node->item << ' ';

                ListInorder_(node->right);
            }
        }
        void ListInorderReverse_    (const Node_* const node                    ) const
        {
            if (node not_eq nullptr)
            {
                ListInorderReverse_(node->right);

                GetOs() << node->item << ' ';

                ListInorderReverse_(node->left);
            }
        }
        void ListPostorder_         (const Node_* const node                    ) const
        {
            if (node not_eq nullptr)
            {
                ListPostorder_(node->left);
                ListPostorder_(node->right);

                GetOs() << node->item << ' ';
            }
        }
        void ListPostorderReverse_  (const Node_* const node                    ) const
        {
            if (node not_eq nullptr)
            {
                ListPostorderReverse_(node->right);
                ListPostorderReverse_(node->left);

                GetOs() << node->item << ' ';
            }
        }
        void ListLeaves_            (const Node_* const node                    ) const
        {
            if (node not_eq nullptr)
            {
                if ((node->left == nullptr) and (node->right == nullptr))
                {
                    GetOs() << node->item << ' ';

                    return;
                }

                ListLeaves_(GetRoot_()->left);
                ListLeaves_(GetRoot_()->right);
            }
        }
        void ListLeavesReverse_     (const Node_* const node                    ) const
        {
            if (node not_eq nullptr)
            {
                if ((node->left == nullptr) and (node->right == nullptr))
                {
                    GetOs() << node->item << ' ';

                    return;
                }

                ListLeavesReverse_(GetRoot_()->right);
                ListLeavesReverse_(GetRoot_()->left);
            }
        }
        void ListLevelorder_        (const Node_* const node, const Size_t level) const
        {
            if (node not_eq nullptr)
            {
                if (level == 1)
                {
                    GetOs() << node->item << ' ';
                }
                else if (level > 1)
                {
                    ListLevelorder_(node->left,  level - 1);
                    ListLevelorder_(node->right, level - 1);
                }
            }
            else if (level == 1)
            {
                GetOs() << "x ";
            }
        }

        void Mirror_                (      Node_* const node)
        {
            if (node not_eq nullptr)
            {
                std::swap<>(node->left, node->right);

                Mirror_(node->left);
                Mirror_(node->right);
            }
        }


    protected:
        Node_* m_pRoot_{};

        Size_t m_node_count_{};

        std::ostream* m_os_{};


    private:
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
